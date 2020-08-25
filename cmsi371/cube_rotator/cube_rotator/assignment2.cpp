/***
 Assignment-2: Rotating a Cube in 3-Dimensional Space

 Name: Mikol, Miliano
 
 Collaborators: None
 
 Project Summary: This program rotates a cube about the z-axis by 90 degrees. First, the program
 compiles a set of points for each plane into a homogenous matrix. It then multiplies the said matrix
 by a Z-rotation matrix.
 ***/

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#pragma GCC diagnostic pop

#include <math.h>
#include <vector>
using namespace std;

float theta = 90.0;

// Converts degrees to radians for rotation
float deg2rad(float d) {
    return (d*M_PI)/180.0;
}

// Converts a vector to an array
GLfloat* vector2array(vector<GLfloat> vec) {
    GLfloat* arr = new GLfloat[vec.size()];
    for (int i = 0; i < vec.size(); i++) {
        arr[i] = vec[i];
    }
    return arr;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_homogenous_coord(vector<GLfloat> cartesian_coords) {
    vector<GLfloat> result;

    result.insert(result.begin(),
                  cartesian_coords.begin(),
                  cartesian_coords.end());
    
    result.push_back(1.0);

    return result;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_cartesian_coord(vector<GLfloat> homogenous_coords) {
    vector<GLfloat> result;
    
    result.insert(result.begin(),
                  homogenous_coords.begin(),
                  homogenous_coords.end() - 1);

    return result;
}

// Definition of a rotation matrix about the x-axis theta degrees
vector<GLfloat> rotation_matrix_x (float theta) {
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    vector<GLfloat> rotate_mat_x = {
        1.0,     0.0,     0.0,  0.0,
        0.0,  cosine,   -sine,  0.0,
        0.0,    sine,  cosine,  0.0,
        0.0,     0.0,     0.0,  1.0
    };

    return rotate_mat_x;
}

// Definition of a rotation matrix along the y-axis by theta degrees
vector<GLfloat> rotation_matrix_y (float theta) {
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    vector<GLfloat> rotate_mat_y = {
        cosine,  0.0,    sine,  0.0,
           0.0,  1.0,     0.0,  0.0,
         -sine,  0.0,  cosine,  0.0,
           0.0,  0.0,     0.0,  1.0
    };

    return rotate_mat_y;
}

// Definition of a rotation matrix along the z-axis by theta degrees
vector<GLfloat> rotation_matrix_z (float theta) {
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    vector<GLfloat> rotate_mat_z = {
        cosine,    sine,  0.0,  0.0,
         -sine,  cosine,  0.0,  0.0,
           0.0,     0.0,  1.0,  0.0,
           0.0,     0.0,  0.0,  1.0
    };

    return rotate_mat_z;
}

// Perform matrix multiplication for A B
vector<GLfloat> mat_mult(vector<GLfloat> A, vector<GLfloat> B) {
    vector<GLfloat> result;
    
    result.assign(16, 0);
    
    for (int i = 0, num_rows = 4; i < num_rows; i++) {
        for (int j = 0, num_cols = 4; j < num_cols; j++) {
            int dot_prod = 0;
            
            for (int k = 0, vector_size = 4; k < vector_size; k++) {
                dot_prod += A[(num_rows * k) + j] * B[(num_cols * i) + k];
            }
            
            result[(num_rows * i) + j] = dot_prod;
        }
    }
    
    return result;
}

void setup() {
    // Enable the vertex array functionality
    glEnableClientState(GL_VERTEX_ARRAY);
    // Enable the color array functionality (so we can specify a color for each vertex)
    glEnableClientState(GL_COLOR_ARRAY);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Set up some default base color
    glColor3f(0.5, 0.5, 0.5);
    // Set up white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init_camera() {
    // Camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a 50 degree field of view, 1:1 aspect ratio, near and far planes at 3 and 7
    gluPerspective(50.0, 1.0, 2.0, 10.0);
    // Position camera at (2, 3, 5), attention at (0, 0, 0), up at (0, 1, 0)
    gluLookAt(2.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // World model parameters
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    vector<GLfloat> points = {
         // Front plane
         +1.0,   +1.0,   +1.0,
         -1.0,   +1.0,   +1.0,
         -1.0,   -1.0,   +1.0,
         +1.0,   -1.0,   +1.0,
         // Back plane
         +1.0,   +1.0,   -1.0,
         -1.0,   +1.0,   -1.0,
         -1.0,   -1.0,   -1.0,
         +1.0,   -1.0,   -1.0,
         // Right
         +1.0,   +1.0,   -1.0,
         +1.0,   +1.0,   +1.0,
         +1.0,   -1.0,   +1.0,
         +1.0,   -1.0,   -1.0,
         // Left
         -1.0,   +1.0,   -1.0,
         -1.0,   +1.0,   +1.0,
         -1.0,   -1.0,   +1.0,
         -1.0,   -1.0,   -1.0,
         // Top
         +1.0,   +1.0,   +1.0,
         -1.0,   +1.0,   +1.0,
         -1.0,   +1.0,   -1.0,
         +1.0,   +1.0,   -1.0,
         // Bottom
         +1.0,   -1.0,   +1.0,
         -1.0,   -1.0,   +1.0,
         -1.0,   -1.0,   -1.0,
         +1.0,   -1.0,   -1.0,
    };

    GLfloat colors[] = {
        // Front plane
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        // Back plane
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        // Right
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        // Left
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        // Top
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        // Bottom
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0
    };

    vector<GLfloat> result;
    
    for (int i = 0, num_planes = 6; i < num_planes; i++) {
        vector<GLfloat> plane;
        
        for (int j = 0, num_points = 4; j < num_points; j++) {
            vector<GLfloat> point;
            
            for (int k = 0, num_coords = 3; k < num_coords; k++) {
                point.push_back(points[(i * 12) + (j * 3) + k]);
            }
            
            point = to_homogenous_coord(point);
            
            plane.insert(plane.end(), point.begin(), point.end());
        }
                
        vector<GLfloat> Z = rotation_matrix_z(theta);
                
        plane = mat_mult(Z, plane);
        
        for (int j = 0; j < plane.size(); j += 4) {
            vector<GLfloat> point;
            
            for (int k = j; k < j + 4; k++) {
                point.push_back(plane[k]);
            }
            
            point = to_cartesian_coord(point);
            
            result.insert(result.end(), point.begin(), point.end());
        }
    }

    points = result;
    
    GLfloat* vertices = vector2array(points);

    glVertexPointer(3,          // 3 components (x, y, z)
                    GL_FLOAT,   // Vertex type is GL_FLOAT
                    0,          // Start position in referenced memory
                    vertices);  // Pointer to memory location to read from

    //pass the color pointer
    glColorPointer(3,           // 3 components (r, g, b)
                   GL_FLOAT,    // Vertex type is GL_FLOAT
                   0,           // Start position in referenced memory
                   colors);     // Pointer to memory location to read from

    // Draw quad point planes: each 4 vertices
    glDrawArrays(GL_QUADS, 0, 4*6);

    glFlush();			//Finish rendering
    glutSwapBuffers();
}

void idle_func() {
    theta = theta+5.0;
    display_func();
}

int main (int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // Create a window with rendering context and everything else we need
    glutCreateWindow("Assignment 2");

    setup();
    init_camera();

    // Set up our display function
    glutDisplayFunc(display_func);
    glutIdleFunc(idle_func);
    // Render our world
    glutMainLoop();
    return 0;
}

