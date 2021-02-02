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

    void update(int time);

protected:
    void onSelect(bool isSelected) override;

private:

    void storePosition(std::pair<int, int> location);

    void deletePosition(std::pair<int, int> location);

    glm::vec3 getQueenLocation(std::pair<int, int> location) const;

    std::pair<int, int> getIndexLocation(glm::vec3 loc) const;

    void queenThreatChecking(int i, int j);

    bool checkIsMoveAvailable(const Queen &queen, ChessTile chessTile);

    void checkAllQueensThreat();


    static std::pair<int, int> getRandomPosition();

    std::set<std::pair<int, int>> queenPositions;
    glm::vec3 start;
    float side;
    ChessBoard chessBoard;
    std::vector<Queen> queens;
    Selectable *selectedQueen = nullptr;
    bool isBoardNeedUpdating = false;

};

#endif //CHESSFINALPROJECT_CHESSGAME_H
