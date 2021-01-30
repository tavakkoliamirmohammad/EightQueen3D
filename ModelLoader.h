#ifndef CHESSFINALPROJECT_MODELLOADER_H
#define CHESSFINALPROJECT_MODELLOADER_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glut.h>

using namespace std;

class ModelLoader {
public:
    struct vertex {
        vertex() {};

        vertex(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        double x, y, z;
    };

    ModelLoader();

    ModelLoader(string path, glm::vec3 position, glm::vec3 color);

    GLuint vertex_VBO;
    GLuint normal_VBO;
    GLuint indices_VBO;
    glm::vec3 position;
    glm::vec3 color;

    void render();


private:
    void load(const string &path);

    void initializeBuffers();

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    vector<glm::vec3> diffuse;
    vector<glm::vec3> ambient;
    vector<glm::vec3> specular;
    vector<GLuint> indices;


};

#endif //CHESSFINALPROJECT_MODELLOADER_H
