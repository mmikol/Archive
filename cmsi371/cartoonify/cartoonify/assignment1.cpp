/***
 assignment1.cpp
 Assignment-1: Cartoonify
 
 Name: Mikol, Miliano
 
 Collaborators: None
 
 Project Summary: I implemented Chaikin's algorithm in an iterative fashion. I used
 the algorithm to draw a (really) rough sketch of Dwayne the Rock Johnson. In order
 to give decent initial control points for the algorithm, I plotted points on a graph over a portrait of his
 face, then scaled to the size of the window that would portray a "cartoonified" image.
 ***/

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
using namespace std;

class Vertex {
    GLfloat x, y;
public:
    Vertex(GLfloat, GLfloat);
    GLfloat get_y() { return y; };
    GLfloat get_x() { return x; };
};

Vertex::Vertex(GLfloat X, GLfloat Y) {
    x = X;
    y = Y;
}

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

vector<Vertex> generate_points(vector<Vertex> control_points) {
    vector<Vertex> points;
    
    for (int i = 0; i < control_points.size() - 1; i++) {
        GLfloat p0_x = control_points[i].get_x(), p0_y = control_points[i].get_y();
        GLfloat p1_x = control_points[i + 1].get_x(), p1_y = control_points[i + 1].get_y();
        
        Vertex p0_new = Vertex((3 * p0_x / 4) + (p1_x / 4), (3 * p0_y / 4) + (p1_y / 4));
        Vertex p1_new = Vertex((p0_x / 4) + (3 * p1_x / 4), (p0_y / 4) + (3 * p1_y / 4));
        
        points.push_back(p0_new);
        points.push_back(p1_new);
    }
    
    return points;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {
    int i = 0;
    while (i++ < n_iter) {
        control_points = generate_points(control_points);
    }
    
    glBegin(GL_LINES);
    for (int i = 0; i < control_points.size() - 1; i ++) {
        glVertex2f(control_points[i].get_x(), control_points[i].get_y());
        glVertex2f(control_points[i + 1].get_x(), control_points[i + 1].get_y());
    }
    glEnd();
    
}

void display() {
    vector<Vertex> head, lips, mouth, right_eye, right_bag, right_pupil, right_iris, nose, left_eye, left_bag, left_pupil, left_iris, right_eyebrow, left_eyebrow, right_cheek, left_cheek, right_chin_line, left_chin_line, left_ear;
    
    head.push_back(Vertex(-0.1f, -0.5f));
    head.push_back(Vertex(0.1f, -0.5f));
    head.push_back(Vertex(0.25f, -0.25f));
    head.push_back(Vertex(0.3f, 0.5f));
    head.push_back(Vertex(0.0f, 0.75f));
    head.push_back(Vertex(-0.3f, 0.5f));
    head.push_back(Vertex(-0.25f, -0.25f));
    head.push_back(Vertex(-0.1f, -0.5f));
    head.push_back(Vertex(0.1f, -0.5f));

    lips.push_back(Vertex(-0.15f, -0.17f));
    lips.push_back(Vertex(0.015f, -0.24f));
    lips.push_back(Vertex(0.17f, -0.18f));
    lips.push_back(Vertex(0.04, -0.14f));
    lips.push_back(Vertex(0.008f, -0.17f));
    lips.push_back(Vertex(-0.016f, -0.15f));
    lips.push_back(Vertex(-0.15f, -0.17f));
    lips.push_back(Vertex(0.015f, -0.24f));

    mouth.push_back(Vertex(-0.15f, -0.17f));
    mouth.push_back(Vertex(-0.028f, -0.18f));
    mouth.push_back(Vertex(0.0f, -0.191f));
    mouth.push_back(Vertex(0.028f, -0.18f));
    mouth.push_back(Vertex(0.15f, -0.17f));

    right_eye.push_back(Vertex(-0.22f, 0.18f));
    right_eye.push_back(Vertex(-0.201f, 0.22f));
    right_eye.push_back(Vertex(-0.136f, 0.23f));
    right_eye.push_back(Vertex(-0.077f, 0.17f));
    right_eye.push_back(Vertex(-0.14f, 0.178f));
    right_eye.push_back(Vertex(-0.195f, 0.178f));
    right_eye.push_back(Vertex(-0.22f, 0.18f));
    right_eye.push_back(Vertex(-0.201f, 0.216f));

    right_bag.push_back(Vertex(-0.08f, 0.18f));
    right_bag.push_back(Vertex(-0.1f, 0.13f));
    right_bag.push_back(Vertex(-0.14f, 0.1f));

    right_pupil.push_back(Vertex(-0.19f, 0.29f));
    right_pupil.push_back(Vertex(-0.16f, 0.15f));
    right_pupil.push_back(Vertex(-0.10f, 0.29f));

    right_iris.push_back(Vertex(-0.17f, 0.25f));
    right_iris.push_back(Vertex(-0.162f, 0.18f));
    right_iris.push_back(Vertex(-0.12f, 0.25f));

    // Right bridge
    nose.push_back(Vertex(-0.03f, 0.193f));
    nose.push_back(Vertex(-0.036f, 0.117f));
    nose.push_back(Vertex(-0.07f, -0.017f));
    nose.push_back(Vertex(-0.06f, -0.064f));
    nose.push_back(Vertex(-0.018f, -0.068f));

    // Right nostril
    nose.push_back(Vertex(-0.048f, -0.025f));
    nose.push_back(Vertex(-0.073f, -0.036f));
    nose.push_back(Vertex(-0.018f, -0.068f));

    // Left nostril
    nose.push_back(Vertex(0.018f, -0.068f));
    nose.push_back(Vertex(0.048f, -0.025f));
    nose.push_back(Vertex(0.073f, -0.036f));
    nose.push_back(Vertex(0.018f, -0.068f));

    // Left bridge
    nose.push_back(Vertex(0.06f, -0.064f));
    nose.push_back(Vertex(0.07f, -0.017f));
    nose.push_back(Vertex(0.036f, 0.117f));
    nose.push_back(Vertex(0.03f, 0.193f));

    left_eye.push_back(Vertex(0.22f, 0.18f));
    left_eye.push_back(Vertex(0.201f, 0.22f));
    left_eye.push_back(Vertex(0.136f, 0.23f));
    left_eye.push_back(Vertex(0.077f, 0.17f));
    left_eye.push_back(Vertex(0.14f, 0.178f));
    left_eye.push_back(Vertex(0.195f, 0.178f));
    left_eye.push_back(Vertex(0.22f, 0.18f));
    left_eye.push_back(Vertex(0.201f, 0.216f));

    left_bag.push_back(Vertex(0.08f, 0.18f));
    left_bag.push_back(Vertex(0.1f, 0.13f));
    left_bag.push_back(Vertex(0.14f, 0.1f));

    left_pupil.push_back(Vertex(0.19f, 0.29f));
    left_pupil.push_back(Vertex(0.16f, 0.15f));
    left_pupil.push_back(Vertex(0.10f, 0.29f));

    left_iris.push_back(Vertex(0.17f, 0.25f));
    left_iris.push_back(Vertex(0.162f, 0.18f));
    left_iris.push_back(Vertex(0.12f, 0.25f));
    
    right_eyebrow.push_back(Vertex(-0.05f, 0.23f));
    right_eyebrow.push_back(Vertex(-0.15f, 0.30f));
    right_eyebrow.push_back(Vertex(-0.27f, 0.24f));
    right_eyebrow.push_back(Vertex(-0.16f, 0.26f));
    right_eyebrow.push_back(Vertex(-0.05f, 0.23f));
    right_eyebrow.push_back(Vertex(-0.15f, 0.30f));

    left_eyebrow.push_back(Vertex(0.05f, 0.23f));
    left_eyebrow.push_back(Vertex(0.15f, 0.30f));
    left_eyebrow.push_back(Vertex(0.27f, 0.24f));
    left_eyebrow.push_back(Vertex(0.16f, 0.26f));
    left_eyebrow.push_back(Vertex(0.05f, 0.23f));
    left_eyebrow.push_back(Vertex(0.15f, 0.30f));

    right_cheek.push_back(Vertex(-0.12f, -0.07f));
    right_cheek.push_back(Vertex(-0.16f, -0.15f));
    right_cheek.push_back(Vertex(-0.13f, -0.27f));

    left_cheek.push_back(Vertex(0.14f, -0.07f));
    left_cheek.push_back(Vertex(0.18f, -0.15f));
    left_cheek.push_back(Vertex(0.15f, -0.27f));

    right_chin_line.push_back(Vertex(-0.19, -0.11));
    right_chin_line.push_back(Vertex(-0.2, -0.225));
    right_chin_line.push_back(Vertex(-0.02, -0.6));

    left_chin_line.push_back(Vertex(0.19, -0.11));
    left_chin_line.push_back(Vertex(0.2, -0.225));
    left_chin_line.push_back(Vertex(0.02, -0.6));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    
    draw_curve(head, 11);
    draw_curve(lips, 11);
    draw_curve(mouth, 11);
    draw_curve(right_eye, 11);
    draw_curve(right_bag, 11);
    draw_curve(right_pupil, 11);
    draw_curve(right_iris, 11);
    draw_curve(nose, 11);
    draw_curve(left_eye, 11);
    draw_curve(left_bag, 11);
    draw_curve(left_pupil, 11);
    draw_curve(left_iris, 11);
    draw_curve(right_eyebrow, 11);
    draw_curve(left_eyebrow, 11);
    draw_curve(right_cheek, 11);
    draw_curve(left_cheek, 11);
    draw_curve(right_chin_line, 11);
    draw_curve(left_chin_line, 11);
    
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 1000); // Set your own window size
    glutCreateWindow("Assignment 1");
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

