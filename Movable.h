#ifndef CHESSFINALPROJECT_MOVABLE_H
#define CHESSFINALPROJECT_MOVABLE_H

#include <glm/glm.hpp>

enum class MovingState {
    Rising, Forwarding, Falling, Stopped
};

class Movable {
public:
    Movable();

    virtual void update(int time) = 0;

protected:
    virtual void onStartMove(glm::vec3 destination, bool *finished) = 0;

    glm::vec3 destination;
    MovingState movingState = MovingState::Stopped;
    int startTime;
};

#endif //CHESSFINALPROJECT_MOVABLE_H
