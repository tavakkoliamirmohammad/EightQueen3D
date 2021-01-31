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

    void processSelect(GLuint name) override;

    void render() override;

protected:
    void onSelect(bool isSelected) override;

private:
    bool isPositionAvailable(std::pair<int, int> location);

    void storePosition(std::pair<int, int> location);

    std::pair<int, int> getRandomPosition();


    std::set<std::pair<int, int>> queenPositions;
    ChessBoard chessBoard;
    std::vector<Queen> queens;

};

#endif //CHESSFINALPROJECT_CHESSGAME_H
