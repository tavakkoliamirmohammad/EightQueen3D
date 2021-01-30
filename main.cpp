#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"
#include "ChessBoard.h"
#include "Queen.h"

int init_time = 0;
float camera_theta = 0;
float camera_fov = 10;


#define floor_w 32
#define floor_h 32

GLfloat floor_vertices[floor_w * floor_h * 3];
GLuint floor_vertices_indice[(floor_w - 1) * (floor_h - 1) * 4];

GLuint vbo_floor = 0;
GLuint vbo_floor_indices = 0;

GLuint fboID, texID, depthID;

vector<Model> objs;
ChessBoard chessBoard;


void camera_config(int w, int h, float t, float fov) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(fov, (float) w / (float) h, 2.0, 500.0);

    gluLookAt(
            10, 5, 20,  // eye
            0.0, 0.0, 0.0,  // look at
            0.0, 1.0, 0.0); // up

    glRotatef(t, 0, 1, 0);
}

void render_scene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    srand(1);

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

//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glColor3f(0.0, 0.0, 0.0);

//    glBindBuffer(GL_ARRAY_BUFFER, NULL);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
//    glVertexPointer(3, GL_FLOAT, 0, floor_vertices);
//    glDrawElements(GL_QUADS, sizeof(floor_vertices_indice) / 4, GL_UNSIGNED_INT, floor_vertices_indice);
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_floor);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_floor_indices);
//    glVertexPointer(3, GL_FLOAT, 0, NULL);
//    glDrawElements(GL_QUADS, sizeof(floor_vertices_indice) / 4, GL_UNSIGNED_INT, NULL);

//    glPopAttrib();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
//    for (auto &obj : objs) {
//        glLoadIdentity();
//        glTranslatef(obj.position.x, obj.position.y, obj.position.z);
////        glScalef(0.5, 0.5, 0.5);
//        obj.render();
//    }
    glPopMatrix();

    glPushMatrix();
    chessBoard.render();
    glPopMatrix();
}

void render() {

    auto w = glutGet(GLUT_WINDOW_WIDTH);
    auto h = glutGet(GLUT_WINDOW_HEIGHT);

    camera_config(w, h, camera_theta, camera_fov);

    render_scene();

    glutSwapBuffers();
}


void init() {
    glewInit();

    for (int i = 0; i < 1; i++) {
//        objs.emplace_back(Queen(glm::vec3(2 * (i - 1.5), 0, 0)));
        objs.emplace_back(Queen(glm::vec3(0, 0, 0)));
    }

    chessBoard = ChessBoard(1, glm::vec3(0, 0, 0));

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glShadeModel(GL_SMOOTH);


    init_time = glutGet(GLUT_ELAPSED_TIME);

    for (int i = 0; i < floor_w; i++) {
        auto x = -floor_w / 2 + i;
        for (int j = 0; j < floor_h; j++) {
            auto y = -floor_h / 2 + j;

            floor_vertices[(i * floor_w + j) * 3 + 0] = x;
            floor_vertices[(i * floor_w + j) * 3 + 1] = 0;
            floor_vertices[(i * floor_w + j) * 3 + 2] = y;
        }
    }

    int id = 0;

    for (int i = 1; i < floor_w; i++) {
        int from = (i - 1) * floor_h;
        int to = i * floor_h;

        for (int j = 0; j < floor_h - 1; j++) {
            floor_vertices_indice[id++] = from++;
            floor_vertices_indice[id++] = to++;
            floor_vertices_indice[id++] = to;
            floor_vertices_indice[id++] = from;
        }
    }

    glGenBuffers(1, &vbo_floor);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_floor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertices), floor_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_floor_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_floor_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_vertices_indice), floor_vertices_indice, GL_STATIC_DRAW);

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
    glutMainLoop();
}