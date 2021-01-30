#ifndef CHESSFINALPROJECT_CHESSGAME_H
#define CHESSFINALPROJECT_CHESSGAME_H

#include <vector>
#include <set>
#include "Queen.h"
#include "ChessBoard.h"
#include "Renderable.h"

class ChessGame : Renderable {
public:
    ChessGame();

    ChessGame(float side, glm::vec3 start);

    void render() override;


private:
    bool isPositionAvailable(std::pair<int, int> location);

    void storePosition(std::pair<int, int> location);

    std::pair<int, int> getRandomPosition();

    std::set<std::pair<int, int>> queenPositions;
    ChessBoard chessBoard;
    std::vector<Queen> queens;

};

#endif //CHESSFINALPROJECT_CHESSGAME_H
