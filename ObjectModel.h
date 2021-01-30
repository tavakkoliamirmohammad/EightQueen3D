#ifndef CHESSFINALPROJECT_OBJECTMODEL_H
#define CHESSFINALPROJECT_OBJECTMODEL_H

#include "Model.h"

class ObjectModel : public Model {
public:
    ObjectModel(const string &path, glm::vec3 position, glm::vec3 color);

private:
    void load(const string &path);
};

#endif //CHESSFINALPROJECT_OBJECTMODEL_H
