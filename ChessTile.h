#ifndef CHESSFINALPROJECT_CHESSTILE_H
#define CHESSFINALPROJECT_CHESSTILE_H

#include "Model.h"

enum class TileColor {
    Black, White
};

class ChessTile : public Model {
public:
    ChessTile(float side, glm::vec3 position, TileColor tileColor);
};

#endif //CHESSFINALPROJECT_CHESSTILE_H
