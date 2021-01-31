#ifndef CHESSFINALPROJECT_CHESSGAME_H
#define CHESSFINALPROJECT_CHESSGAME_H

#include <vector>
#include <set>
#include "Queen.h"
#include "ChessBoard.h"
#include "Renderable.h"
#include "Selectable.h"

class ChessGame : Renderable, Selectable {
public:
    ChessGame();

    ChessGame(float side, glm::vec3 start, int &name);

    Selectable *processSelect(GLuint name) override;

    void render() override;

    bool isPositionAvailable(std::pair<int, int> location);
    bool isPositionAvailable(ChessTile chessTile);

protected:
    void onSelect(bool isSelected) override;

private:

    void storePosition(std::pair<int, int> location);

    std::pair<int, int> getRandomPosition();


    std::set<std::pair<int, int>> queenPositions;
    ChessBoard chessBoard;
    std::vector<Queen> queens;
    Selectable *selectedQueen;

};

#endif //CHESSFINALPROJECT_CHESSGAME_H
