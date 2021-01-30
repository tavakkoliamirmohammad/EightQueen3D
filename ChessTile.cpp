#include "ChessTile.h"


ChessTile::ChessTile(glm::vec3 position, TileColor tileColor) : Model() {
    this->position = position;
    this->color = tileColor == TileColor::Black ? glm::vec3(0, 0, 0) : glm::vec3(1, 1, 1);
}