#ifndef CHESSFINALPROJECT_SELECTABLE_H
#define CHESSFINALPROJECT_SELECTABLE_H

class Selectable {
public:
    Selectable();

    Selectable(int name);

protected:
    int selectName;

    virtual void onSelect(bool isSelected) = 0;
};

#endif //CHESSFINALPROJECT_SELECTABLE_H
