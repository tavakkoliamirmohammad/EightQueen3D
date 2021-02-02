#include "Camera.h"
#include <GL/glut.h>


Camera::Camera() {}


Camera::Camera(float theta, float fov) {
    this->theta = theta;
    this->fov = fov;
}


void Camera::setProjectionMatrix(int w, int h) {
    gluPerspective(fov, (float) w / (float) h, 2.0, 500.0);

    gluLookAt(
            10, 10, 20,  // eye
            0.0, 0.0, 0.0,  // look at
            0.0, 1.0, 0.0); // up

    glRotatef(theta, 0, 1, 0);
}

void Camera::configure(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setProjectionMatrix(w, h);
}

