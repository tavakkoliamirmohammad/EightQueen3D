#ifndef CHESSFINALPROJECT_SELECTABLE_H
#define CHESSFINALPROJECT_SELECTABLE_H

#include <GL/glut.h>

class Selectable {
public:
    Selectable();

    Selectable(int name);

protected:
    int selectName;

    virtual void onSelect(bool isSelected) = 0;

    virtual Selectable * processSelect(GLuint name) = 0;
};

#endif //CHESSFINALPROJECT_SELECTABLE_H
