#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "ChessGame.h"
#include "Camera.h"
#include "Game.h"

#define BUFFER_SIZE 512

ChessGame chessGame;
Camera camera;

float fov = 20;
float theta = 0;
Game::RotateState rotateState;
Game::ZoomState zoomState;

void Game::renderScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    chessGame.render();
    glPopMatrix();
}

void Game::processHits(GLint hits, GLuint *buffer) {
    if (hits == 0) {
        chessGame.processSelect(-1);
    }
    unsigned int i, j;
    GLuint names, *ptr, minZ, *ptrNames;

    ptr = (GLuint *) buffer;
    minZ = 0xffffffff;
    for (i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < minZ) {
            minZ = *ptr;
            ptrNames = ptr + 2;
        }
        ptr += names + 2;
    }
    ptr = ptrNames;
    chessGame.processSelect(*ptr);
}

void Game::pickItems(int button, int state, int x, int y) {
    GLuint selectBuf[BUFFER_SIZE];
    GLint hits;
    GLint viewport[4];
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(BUFFER_SIZE, selectBuf);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(-1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    camera.setProjectionMatrix(w, h);

    renderScene();

    glPopMatrix();
    glutSwapBuffers();

    hits = glRenderMode(GL_RENDER);
    processHits(hits, selectBuf);
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);

    camera.configure(w, h);

    renderScene();

    glutSwapBuffers();
}

void Game::timer(int value) {
    auto current_time = glutGet(GLUT_ELAPSED_TIME);
    chessGame.update(current_time);
    bool isCameraChanged = false;
    if (rotateState != RotateState::Steady) {
        isCameraChanged = true;
        if (rotateState == RotateState::Left) {
            theta += 0.5;
        } else if (rotateState == RotateState::Right) {
            theta -= 0.5;
        }
        rotateState = RotateState::Steady;
    }

    if (zoomState != ZoomState::Steady) {
        isCameraChanged = true;
        if (zoomState == ZoomState::In) {
            fov -= 0.5;
        } else if (zoomState == ZoomState::Out) {
            fov += 0.5;
        }
        zoomState = ZoomState::Steady;
    }
    if (isCameraChanged) {
        camera.theta = theta;
        camera.fov = fov;
        auto w = glutGet(GLUT_WINDOW_WIDTH);
        auto h = glutGet(GLUT_WINDOW_HEIGHT);
        camera.configure(w, h);
    }
    glutTimerFunc(25, timer, value + 1);
    glutPostRedisplay();
}

void Game::reshape(int w, int h) {
    camera.configure(w, h);
}

void Game::init() {
    glewInit();
    glClearColor(0.6, 0.6, 0.6, 1.0);
    int name = 0;
    chessGame = ChessGame(1, glm::vec3(-4, 0, -4), name);
    camera = Camera(theta, fov);
    rotateState = RotateState::Steady;
    zoomState = ZoomState::Steady;

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glShadeModel(GL_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_ambient[] = {0.1f, 0.1f, 0.1f, 0.2f};
    float light_diffuse[] = {0.8f, 0.8f, 0.8f, 0};
    float light_specular[] = {0.5f, 0.5f, 0.5f, 0.2f};
    float light_pos[] = {200.0f, 300.0f, -400.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void Game::keyboardFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            zoomState = ZoomState::In;
            break;
        case GLUT_KEY_DOWN:
            zoomState = ZoomState::Out;
            break;
        case GLUT_KEY_LEFT:
            rotateState = RotateState::Left;
            break;
        case GLUT_KEY_RIGHT:
            rotateState = RotateState::Right;
            break;
    }
}


int Game::main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Eight Queen");

    init();

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardFunc);
    glutMouseFunc(pickItems);
    glutTimerFunc(25, timer, 0);
    glutMainLoop();
    return 0;
}