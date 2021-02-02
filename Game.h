#ifndef CHESSFINALPROJECT_GAME_H
#define CHESSFINALPROJECT_GAME_H

#include <GL/glut.h>


namespace Game {
    enum class RotateState {
        Left, Right, Steady
    };

    enum class ZoomState {
        In, Out, Steady
    };

    void init();

    void keyboardFunc(int key, int x, int y);

    int main(int argc, char **argv);

    void renderScene();

    void processHits(GLint hits, GLuint *buffer);

    void pickItems(int button, int state, int x, int y);

    void render();

    void timer(int value);

    void reshape(int w, int h);
}

#endif //CHESSFINALPROJECT_GAME_H
