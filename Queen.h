#ifndef CHESSFINALPROJECT_QUEEN_H
#define CHESSFINALPROJECT_QUEEN_H

#include "ObjectModel.h"
#include "Movable.h"

class Queen : public ObjectModel, public Movable {
public:
    Queen();

    Queen(glm::vec3 position, int &name);

    void onStartMove(glm::vec3 destination, bool *finished) override;

    void update(int time) override;

    void onSelect(bool isSelected) override;

    bool isUnderThreat;
    bool *finished;

};

#endif //CHESSFINALPROJECT_QUEEN_H
