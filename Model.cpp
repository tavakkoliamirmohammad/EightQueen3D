#include "GL/glew.h"
#include "Model.h"
#include <iostream>

using namespace std;

Model::Model() {
    this->position = glm::vec3(0, 0, 0);

}

Model::Model(glm::vec3 position, glm::vec3 color, int &name) : Selectable(name) {
    this->position = position;
    this->color = color;
    this->originalColor = color;
    ++name;
}

void Model::initializeBuffers() {
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indices_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_VBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &color_VBO);

    changeColor(color);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Model::changeColor(glm::vec3 color) {
    colors.clear();

    for (int i = 0; i < vertices.size(); i++) {
        colors.emplace_back(glm::vec4(color, 1));
    }

    this->color = color;

    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Model::render() {
    glLoadName(selectName);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glColor4f(color.x, color.y, color.z, 1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColorMaterial(GL_FRONT, GL_AMBIENT);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
    glColorPointer(4, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
    glNormalPointer(GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_VBO);
    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, nullptr);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopMatrix();


}

void Model::onSelect(bool isSelected) {
    this->isSelected = isSelected;
    if (isSelected) {
        changeColor(selectColor);
    } else {
        changeColor(originalColor);
    }

}

void Model::processSelect(GLuint name) {
    if (selectName == name) {
        onSelect(!isSelected);
    } else {
        onSelect(false);
    }
}
