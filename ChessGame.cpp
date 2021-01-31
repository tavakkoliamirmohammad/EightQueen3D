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
            deletePosition(make_pair(queen->position.x, queen->position.z));
            auto location = make_pair(chessTile->position.x, chessTile->position.z);
            storePosition(location);
            queen->onStartMove(getQueenLocation(location));
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
    return isPositionAvailable(make_pair(chessTile.position.x, chessTile.position.y));
}

glm::vec3 ChessGame::getQueenLocation(std::pair<int, int> location) const {
    return glm::vec3(location.first * side, 0, location.second * side);
}

void ChessGame::update(int time) {
    for (auto &queen: queens) {
        queen.update(time);
    }
}


