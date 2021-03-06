#include "ChessTile.h"


ChessTile::ChessTile(float side, glm::vec3 position, TileColor tileColor, int &name) : Model() {
    this->position = position;

    this->vertices.emplace_back(glm::vec3(-side / 2, 0, -side / 2));
    this->vertices.emplace_back(glm::vec3(-side / 2, 0, +side / 2));
    this->vertices.emplace_back(glm::vec3(+side / 2, 0, +side / 2));
    this->vertices.emplace_back(glm::vec3(+side / 2, 0, -side / 2));

    this->normals.emplace_back(glm::vec3(0, 1, 0));
    this->normals.emplace_back(glm::vec3(0, 1, 0));
    this->normals.emplace_back(glm::vec3(0, 1, 0));
    this->normals.emplace_back(glm::vec3(0, 1, 0));

    this->indices.emplace_back(3);
    this->indices.emplace_back(2);
    this->indices.emplace_back(1);
    this->indices.emplace_back(0);
    initializeBuffers();
    this->selectName = name;
    changeColor(tileColor == TileColor::Black ? glm::vec3(0, 0, 0) : glm::vec3(1, 1, 1));
    this->originalColor = tileColor == TileColor::Black ? glm::vec3(0, 0, 0) : glm::vec3(1, 1, 1);
    ++name;
}