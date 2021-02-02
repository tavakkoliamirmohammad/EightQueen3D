#include "ChessGame.h"
#include <glm/glm.hpp>
#include <random>
#include <iostream>

using namespace std;

ChessGame::ChessGame() {}

ChessGame::ChessGame(float side, glm::vec3 start, int &name) {
    this->side = side;
    this->start = start;
    chessBoard = ChessBoard(side, start, name);
    for (int i = 0; i < 8; ++i) {
        std::pair<int, int> location;
        do {
            location = getRandomPosition();
        } while (!isPositionAvailable(location));
        storePosition(location);
        queens.emplace_back(Queen(getQueenLocation(location), name));
    }
    checkAllQueensThreat();
}

bool ChessGame::isPositionAvailable(std::pair<int, int> location) {
    return queenPositions.find(location) == queenPositions.end();
}

void ChessGame::storePosition(std::pair<int, int> location) {
    queenPositions.insert(location);
}

void ChessGame::deletePosition(std::pair<int, int> location) {
    queenPositions.erase(location);
}

int randU(int nMin, int nMax) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(nMin, nMax);
    return dist6(rng);
}

std::pair<int, int> ChessGame::getRandomPosition() {
    return make_pair(randU(0, 7), randU(0, 7));
}

void ChessGame::render() {
    chessBoard.render();
    if (isBoardNeedUpdating) {
        checkAllQueensThreat();
        isBoardNeedUpdating = false;
    }
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(start.x, start.y, start.z);
    for (auto queen: queens) {
        glPushMatrix();
        queen.render();
        glPopMatrix();
    }
    glPopMatrix();
}

Selectable *ChessGame::processSelect(GLuint name) {
    Selectable *selectable = nullptr;
    Selectable *temp;
    ChessTile *chessTile;

    temp = chessBoard.processSelect(name);
    if (temp != nullptr) {
        selectable = temp;
        chessTile = dynamic_cast<ChessTile *>(selectable);
        if (selectedQueen != nullptr && isPositionAvailable(*chessTile)) {
            auto *queen = dynamic_cast<Queen *>(selectedQueen);
            if (checkIsMoveAvailable(*queen, *chessTile)) {
                deletePosition(make_pair(queen->position.x, queen->position.z));
                auto location = make_pair(chessTile->position.x, chessTile->position.z);
                storePosition(location);
                queen->onStartMove(getQueenLocation(location), &isBoardNeedUpdating);
            }
        }
        selectedQueen = nullptr;
    }
    for (auto &queen: queens) {
        temp = queen.processSelect(name);
        if (temp != nullptr) {
            selectable = temp;
            selectedQueen = selectable;
        }
    }
    return selectable;
}

void ChessGame::onSelect(bool isSelected) {

}

bool ChessGame::isPositionAvailable(ChessTile chessTile) {
    return isPositionAvailable(make_pair(chessTile.position.x, chessTile.position.z));
}

glm::vec3 ChessGame::getQueenLocation(std::pair<int, int> location) const {
    return glm::vec3(location.first * side, 0, location.second * side);
}

void ChessGame::update(int time) {
    for (auto &queen: queens) {
        queen.update(time);
    }
}


std::pair<int, int> ChessGame::getIndexLocation(glm::vec3 loc) const {
    float qx = loc.x / side;
    float qz = loc.z / side;
    return make_pair((qx - int(qx)) >= 0.5 ? (int(qx) + 1) : int(qx), (qz - int(qz)) >= 0.5 ? (int(qz) + 1) : int(qz));
}

void ChessGame::queenThreatChecking(int i, int j) {
    auto q1Location = getIndexLocation(queens[i].position);
    auto q2Location = getIndexLocation(queens[j].position);
    if (q1Location.first == q2Location.first || q1Location.second == q2Location.second) {
        queens[i].changeColor(glm::vec3(1, 0, 0));
        queens[i].isUnderThreat = true;
        return;
    }
    float m = float(q2Location.second - q1Location.second) / (q2Location.first - q1Location.first);
    if (abs(abs(m) - 1) < 0.1) {
        queens[i].changeColor(glm::vec3(1, 0, 0));
        queens[i].isUnderThreat = true;
        return;
    }
}

void ChessGame::checkAllQueensThreat() {
    for (auto &queen: queens) {
        queen.isUnderThreat = false;
        queen.changeColor(queen.originalColor);
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == j) continue;
            queenThreatChecking(i, j);
        }
    }
}

bool ChessGame::checkIsMoveAvailable(const Queen &queen, ChessTile chessTile) {
    auto q1Location = getIndexLocation(queen.position);
    auto q2Location = getIndexLocation(chessTile.position);
    if (q1Location.first == q2Location.first || q1Location.second == q2Location.second) {
        return true;
    }
    float m = float(q2Location.second - q1Location.second) / (q2Location.first - q1Location.first);
    if (abs(abs(m) - 1) < 0.1) {
        return true;
    }
    return false;
}
