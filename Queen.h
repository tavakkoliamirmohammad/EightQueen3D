#ifndef CHESSFINALPROJECT_QUEEN_H
#define CHESSFINALPROJECT_QUEEN_H

#include "ObjectModel.h"

class Queen : public ObjectModel {
public:
    Queen();

    Queen(glm::vec3 position, int &name);
};

#endif //CHESSFINALPROJECT_QUEEN_H
