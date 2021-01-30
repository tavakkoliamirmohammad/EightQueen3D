#ifndef CHESSFINALPROJECT_OBJECTMODEL_H
#define CHESSFINALPROJECT_OBJECTMODEL_H

#include "Model.h"

class ObjectModel : public Model {
public:
    ObjectModel();

    ObjectModel(const string &path, glm::vec3 position, glm::vec3 color, int &name);

private:
    void load(const string &path);
};

#endif //CHESSFINALPROJECT_OBJECTMODEL_H
