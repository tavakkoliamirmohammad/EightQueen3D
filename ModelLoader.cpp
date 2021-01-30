#include "GL/glew.h"
#include "ModelLoader.h"
#include <fstream>
#include <sstream>

ModelLoader::ModelLoader() {
    this->position = glm::vec3(0, 0, 0);

}

ModelLoader::ModelLoader(string path, glm::vec3 position, glm::vec3 color) {
    this->position = position;
    this->color = color;
    load(path);
}


void ModelLoader::load(const string &path) {

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
    initializeBuffers();
}

void ModelLoader::initializeBuffers() {
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indices_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_VBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModelLoader::render() {
    glColor4f(color.x, color.y, color.z, 1);

    glEnable (GL_COLOR_MATERIAL);
    glColorMaterial (GL_FRONT, GL_DIFFUSE);
    glColorMaterial (GL_FRONT, GL_SPECULAR);
    glColorMaterial (GL_FRONT, GL_AMBIENT);

    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
    glNormalPointer(GL_FLOAT, 0, nullptr);

    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, nullptr);
    glDisableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}