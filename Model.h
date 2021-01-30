#ifndef CHESSFINALPROJECT_MODEL_H
#define CHESSFINALPROJECT_MODEL_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glut.h>

using namespace std;

class Model {
public:
    Model();

    Model(glm::vec3 position, glm::vec3 color);

    glm::vec3 position;
    glm::vec3 color;

    void render();


protected:
    void initializeBuffers();

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    vector<glm::vec3> diffuse;
    vector<glm::vec3> ambient;
    vector<glm::vec3> specular;
    GLuint vertex_VBO;
    GLuint normal_VBO;
    GLuint indices_VBO;
    vector<GLuint> indices;


};

#endif //CHESSFINALPROJECT_MODEL_H
