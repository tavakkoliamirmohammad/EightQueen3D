#ifndef CHESSFINALPROJECT_CHESSBOARD_H
#define CHESSFINALPROJECT_CHESSBOARD_H

#include <vector>
#include <glm/glm.hpp>
#include "Renderable.h"
#include "ChessTile.h"


class ChessBoard : public Renderable {
public:
    ChessBoard();
    ChessBoard(float side, glm::vec3 position);
    void render() override;

private:
    float side;
    glm::vec3 position;
    std::vector<ChessTile> chessTiles;
};

#endif //CHESSFINALPROJECT_CHESSBOARD_H
