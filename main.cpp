#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ChessGame.h"

int init_time = 0;
float camera_theta = 0;
float camera_fov = 10;


#define BUFSIZE 512

ChessGame chessGame;


void setProjectionMatrix(int w, int h) {
    gluPerspective(camera_fov, (float) w / (float) h, 2.0, 500.0);

    gluLookAt(
            10, 5, 20,  // eye
            0.0, 0.0, 0.0,  // look at
            0.0, 1.0, 0.0); // up

    glRotatef(camera_theta, 0, 1, 0);
}

void camera_config(int w, int h, float t, float fov) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setProjectionMatrix(w, h);
}

void render_scene() {

    glPushAttrib(GL_LINE_BIT);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(50, 0, 0);
    glColor3f(0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 50, 0);
    glColor3f(0, 0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 50);
    glEnd();
    glPopAttrib();


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    chessGame.render();
    glPopMatrix();
}

void processHits(GLint hits, GLuint buffer[]) {
    if (hits == 0) return;
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

void pickItems(int button, int state, int x, int y) {
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(BUFSIZE, selectBuf);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(-1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);
    setProjectionMatrix(w, h);

    render_scene();

    glPopMatrix();
    glutSwapBuffers();

    hits = glRenderMode(GL_RENDER);
    processHits(hits, selectBuf);
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);

    camera_config(w, h, camera_theta, camera_fov);

    render_scene();

    glutSwapBuffers();
}


void init() {
    glewInit();
    glClearColor(0.6, 0.6, 0.6, 1.0);
    int name = 0;
    chessGame = ChessGame(1, glm::vec3(-2, 0, -2), name);
//    for (int i = 0; i < 4; i++) {
//        objs.emplace_back(Queen(glm::vec3(2 * (i - 1.5), 0, 0)));
//    }
//
//    chessBoard = ChessBoard(1, glm::vec3(3, 0, 0));


    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glShadeModel(GL_SMOOTH);


    init_time = glutGet(GLUT_ELAPSED_TIME);

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


void reshape(int w, int h) {
    camera_config(w, h, camera_theta, camera_fov);
}

void keyboardFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            camera_fov -= 0.5;
            break;
        case GLUT_KEY_DOWN:
            camera_fov += 0.5;
            break;
        case GLUT_KEY_LEFT:
            camera_theta += 0.5;
            break;
        case GLUT_KEY_RIGHT:
            camera_theta -= 0.5;
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Test OpenGL");

    init();

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardFunc);
    glutMouseFunc(pickItems);
    glutMainLoop();
}