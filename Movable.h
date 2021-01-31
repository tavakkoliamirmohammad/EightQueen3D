#ifndef CHESSFINALPROJECT_MOVABLE_H
#define CHESSFINALPROJECT_MOVABLE_H

class Movable {
public:
    Movable();

protected:
    virtual void onStartMove() = 0;
};

#endif //CHESSFINALPROJECT_MOVABLE_H
