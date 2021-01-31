#include "ChessBoard.h"

ChessBoard::ChessBoard() {}

ChessBoard::ChessBoard(float side, glm::vec3 position, int &name) : Selectable(name) {
    this->side = side;
    this->position = position;
    bool pattern = true;
    bool isBlack;
    for (int i = 0; i < 8; i++) {
        isBlack = pattern;
        for (int j = 0; j < 8; j++) {
            chessTiles.emplace_back(ChessTile(side, glm::vec3(i * side, 0, j * side),
                                              isBlack ? TileColor::Black
                                                      : TileColor::White, name));
            isBlack = !isBlack;
        }
        pattern = !pattern;
    }
}

void ChessBoard::render() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    for (auto &tile : chessTiles) {
        tile.render();
    }
    glPopMatrix();
}

Selectable * ChessBoard::processSelect(GLuint name) {
    Selectable *selectable = nullptr;
    Selectable *temp;

    for (auto &tile : chessTiles) {
        temp = tile.processSelect(name);
        if (temp != nullptr) selectable = temp;
    }
    return selectable;
}

void ChessBoard::onSelect(bool isSelected) {

}
