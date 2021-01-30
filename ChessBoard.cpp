#include "ChessBoard.h"

ChessBoard::ChessBoard() {}

ChessBoard::ChessBoard(float side, glm::vec3 position) {
    this->side = side;
    this->position = position;
    bool pattern = true;
    bool isBlack;
    for (int i = 0; i < 8; i++) {
        isBlack = pattern;
        for (int j = 0; j < 8; j++) {
            chessTiles.emplace_back(ChessTile(side, position + glm::vec3(i * side, 0, j * side),
                                              isBlack ? TileColor::Black
                                                      : TileColor::White));
            isBlack = !isBlack;
        }
        pattern = !pattern;
    }
}

void ChessBoard::render() {
    for (auto &tile : chessTiles) {
        glPushMatrix();
        glTranslatef(tile.position.x, tile.position.y, tile.position.z);
        tile.render();
        glPopMatrix();
    }
}