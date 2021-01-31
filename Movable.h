#ifndef CHESSFINALPROJECT_MOVABLE_H
#define CHESSFINALPROJECT_MOVABLE_H

#include <glm/glm.hpp>

class Movable {
public:
    Movable();

protected:
    virtual void onStartMove(glm::vec3 destination) = 0;
};

#endif //CHESSFINALPROJECT_MOVABLE_H
