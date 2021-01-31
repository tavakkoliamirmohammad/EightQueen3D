#include "Queen.h"

Queen::Queen() {

}

Queen::Queen(glm::vec3 position, int &name) : ObjectModel("queen.obj", position, glm::vec3(1, 1, 1), name) {

}

void Queen::onStartMove(glm::vec3 destination) {
    this->destination = destination;
    movingState = MovingState::Rising;
    startTime = glutGet(GLUT_ELAPSED_TIME);
}

void Queen::update(int time) {

    if (movingState != MovingState::Stopped) {
        float difference_time = float(time - startTime) / 1000.0;
        if (movingState == MovingState::Rising) {
            int yMax = 2;
            if (position.y >= yMax) {
                movingState = MovingState::Forwarding;
                startTime = time;
            } else {
                position.y += difference_time * 0.2;
            }

        } else if (movingState == MovingState::Forwarding) {
            glm::vec3 direction = destination - position;
            glm::vec3 displacement = glm::vec3(direction.x, 0, direction.z);
            if (glm::length(displacement) > 0.05f) {
                position += (glm::normalize(displacement) * 0.1f);
            } else {
                movingState = MovingState::Falling;
            }

        } else if (movingState == MovingState::Falling) {
            if (position.y < 0.1) {
                movingState = MovingState::Stopped;
                position.y = 0;
            } else {
                position.y -= difference_time * 0.2;
            }
        }
    }
}
