#ifndef CHESSFINALPROJECT_CAMERA_H
#define CHESSFINALPROJECT_CAMERA_H

class Camera {
public:
    Camera();

    Camera(float theta, float fov);

    void setProjectionMatrix(int w, int h);

    void configure(int w, int h);

    float theta = 0;
    float fov = 20;
};

#endif //CHESSFINALPROJECT_CAMERA_H
