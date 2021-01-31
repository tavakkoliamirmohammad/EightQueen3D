#include "Queen.h"

Queen::Queen() {

}

Queen::Queen(glm::vec3 position, int &name) : ObjectModel("queen.obj", position, glm::vec3(1, 1, 1), name) {

}

void Queen::onStartMove(glm::vec3 destination) {
    this->position = destination;
}
