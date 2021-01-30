#include "ObjectModel.h"
#include <fstream>
#include <sstream>
ObjectModel::ObjectModel(const string& path, glm::vec3 position, glm::vec3 color) : Model(position, color) {
    load(path);
    initializeBuffers();
}

void ObjectModel::load(const string &path) {

    std::string temp;
    std::string line;
    double d_temp;
    double current_v;

    std::ifstream fin(path);

    if (!fin)
        return;

    while (getline(fin, line)) {
        std::istringstream iss(line);

        if (line.substr(0, 2) == "v ") {
            glm::vec3 v;
            iss >> temp >> v.x >> v.y >> v.z;
            this->vertices.push_back(v);
        } else if (line.substr(0, 2) == "f ") {

            iss >> temp;
            iss >> current_v;
            this->indices.push_back(current_v - 1);
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> current_v;
            this->indices.push_back(current_v - 1);
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> current_v;
            this->indices.push_back(current_v - 1);
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> current_v;
            this->indices.push_back(current_v - 1);
            iss.ignore(1);
            iss >> d_temp;
            iss.ignore(1);
            iss >> d_temp;
        } else if (line.substr(0, 3) == "vn ") {

            glm::vec3 vn;
            iss >> temp >> vn.x >> vn.y >> vn.z;

            this->normals.push_back(vn);
        }
    }
}