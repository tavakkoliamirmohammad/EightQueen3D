#ifndef CHESSFINALPROJECT_MODEL_H
#define CHESSFINALPROJECT_MODEL_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include "Renderable.h"
#include "Selectable.h"

using namespace std;

class Model : public Renderable, public Selectable {
public:
    Model();

    Model(glm::vec3 position, glm::vec3 color, int &name);

    glm::vec3 position;
    glm::vec3 originalColor;
    glm::vec3 selectColor = glm::vec3(1, 1, 0);

    void changeColor(glm::vec3 color);

    void render() override;

    void onSelect(bool isSelected) override;

    void processSelect(GLuint name) override;

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
    GLuint color_VBO;
    vector<GLuint> indices;

    bool isSelected = false;

private:
    glm::vec3 color;
    vector<glm::vec4> colors;


};

#endif //CHESSFINALPROJECT_MODEL_H
