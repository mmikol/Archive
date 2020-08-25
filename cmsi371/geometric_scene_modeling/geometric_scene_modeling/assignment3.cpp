/***
 Assignment-3: Geometric Modeling of a Scene
 
 Name: Mikol, Miliano
 
 Collaborators: None
 
 Project Summary: A short paragraph (3-4 sentences) describing the work you
 did for the project.
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

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

// If a float is < EPSILON or > -EPILSON then it should be 0
float EPSILON = 0.000001;
// theta is the angle to rotate the scene
float THETA = 0.0;
// Vector placeholders for the scene and color array
vector<GLfloat> SCENE;
vector<GLfloat> COLOR;

/**************************************************
 *  Rectangular Prisms via Hierarchical Modeling  *
 *                                                *
 *  using planes as building blocks, build a unit *
 *  cube with transformations that will serve as  *
 *  a primitive for modeling objects in the scene *
 *                                                *
 *************************************************/

// Initializes a square plane of unit lengths
vector<GLfloat> init_plane() {
    vector<GLfloat> vertices = {
        -0.5,   +0.5,   +0.0,
        -0.5,   -0.5,   +0.0,
        +0.5,   -0.5,   +0.0,
        +0.5,   +0.5,   +0.0
    };
    return vertices;
}

// Converts degrees to radians for rotation
float deg2rad(float d) {
    return (d*M_PI) / 180.0;
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
vector<GLfloat> to_homogeneous_coord(vector<GLfloat> cartesian_coords) {
    vector<GLfloat> result;
    for (int i = 0; i < cartesian_coords.size(); i++) {
        result.push_back(cartesian_coords[i]);
        if ((i+1) % 3 == 0) {
            result.push_back(1.0);
        }
    }
    return result;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_cartesian_coord(vector<GLfloat> homogeneous_coords) {
    vector<GLfloat> result;
    for (int i = 0; i < homogeneous_coords.size(); i++) {
        if ((i+1) % 4 == 0) {
            continue;
        } else {
            result.push_back(homogeneous_coords[i]);
        }
    }
    return result;
}

// Definition of a translation matrix
vector<GLfloat> translation_matrix (float dx, float dy, float dz) {
    vector<GLfloat> translate_mat;
    
    translate_mat = {
        1.0, 0.0, 0.0, dx,
        0.0, 1.0, 0.0, dy,
        0.0, 0.0, 1.0, dz,
        0.0, 0.0, 0.0, 1.0
    };
    
    return translate_mat;
}

// Definition of a scaling matrix
vector<GLfloat> scaling_matrix (float sx, float sy, float sz) {
    vector<GLfloat> scale_mat;
    
    scale_mat = {
        sx, 0.0, 0.0, 0.0,
        0.0, sy, 0.0, 0.0,
        0.0, 0.0, sz, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    
    return scale_mat;
}

// Definition of a rotation matrix about the x-axis theta degrees
vector<GLfloat> rotation_matrix_x (float theta) {
    vector<GLfloat> rotate_mat_x;
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    rotate_mat_x = {
        1.0, 0.0, 0.0, 0.0,
        0.0, cosine, sine, 0.0,
        0.0, -sine, cosine, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    
    return rotate_mat_x;
}

// Definition of a rotation matrix about the y-axis by theta degrees
vector<GLfloat> rotation_matrix_y (float theta) {
    vector<GLfloat> rotate_mat_y;
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    rotate_mat_y = {
        cosine, 0.0, sine, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sine, 0.0, cosine, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    
    return rotate_mat_y;
}

// Definition of a rotation matrix about the z-axis by theta degrees
vector<GLfloat> rotation_matrix_z (float theta) {
    vector<GLfloat> rotate_mat_z;
    GLfloat cosine = round(cos(deg2rad(theta)));
    GLfloat sine = round(sin(deg2rad(theta)));
    
    rotate_mat_z = {
        cosine, sine, 0.0, 0.0,
        -sine, cosine, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    
    return rotate_mat_z;
}

// Perform matrix multiplication for A B
vector<GLfloat> mat_mult(vector<GLfloat> A, vector<GLfloat> B) {
    vector<GLfloat> result;
    for (int i = 0; i < B.size(); i += 4) {
        for (int j = 0; j < A.size(); j += 4) {
            GLfloat dot_product = 0.0;
            for (int k = 0; k < 4; k++){
                GLfloat value = A[j+k] * B[i+k];
                if (value < EPSILON && value > -EPSILON) {
                    value = 0.0;
                }
                dot_product += value;
            }
            result.push_back(dot_product);
        }
    }
    return result;
}

// Builds a unit cube centered at the origin
vector<GLfloat> build_cube() {
    vector<GLfloat> result, front, back, left, right, top, bottom;
    
    vector<GLfloat> unit_plane = to_homogeneous_coord(init_plane());
    
    front = mat_mult(translation_matrix(0.0, 0.0, 0.5), unit_plane);
    result.insert(result.end(), front.begin(), front.end());
    
    back = mat_mult(rotation_matrix_y(180.0), unit_plane);
    back = mat_mult(translation_matrix(0.0, 0.0, -0.5), back);
    result.insert(result.end(), back.begin(), back.end());

    left = mat_mult(rotation_matrix_y(-90.0), unit_plane);
    left = mat_mult(translation_matrix(-0.5, 0.0, 0.0), left);
    result.insert(result.end(), left.begin(), left.end());

    right = mat_mult(rotation_matrix_y(90.0), unit_plane);
    right = mat_mult(translation_matrix(0.5, 0.0, 0.0), right);
    result.insert(result.end(), right.begin(), right.end());

    top = mat_mult(rotation_matrix_x(-90.0), unit_plane);
    top = mat_mult(translation_matrix(0.0, 0.5, 0.0), top);
    result.insert(result.end(), top.begin(), top.end());

    bottom = mat_mult(rotation_matrix_x(90.0), unit_plane);
    bottom = mat_mult(translation_matrix(0.0, -0.5, 0.0), bottom);
    result.insert(result.end(), bottom.begin(), bottom.end());

    return result;
}

/**************************************************
 *            Camera and World Modeling           *
 *                                                *
 *  create a scene by applying transformations to *
 *  the objects built from planes and position    *
 *  the camera to view the scene by setting       *
 *  the projection/viewing matrices               *
 *                                                *
 *************************************************/

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
    gluPerspective(50.0, 1.0, 1.0, 100.0);
    // Position camera at (2, 3, 5), attention at (0, 0, 0), up at (0, 1, 0)
    gluLookAt(8.0, 8.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

vector<GLfloat> build_table(vector<GLfloat> unit_cube) {
    vector<GLfloat> table, table_top, bottom_left_leg, bottom_right_leg, top_left_leg, top_right_leg;
    vector<GLfloat> unit_leg = mat_mult(scaling_matrix(0.2, 2.0, 0.2), unit_cube);
    
    table_top = mat_mult(scaling_matrix(3.0, .1, 5.0), unit_cube);
    table_top = mat_mult(translation_matrix(0.0, 2.0, 0.0), table_top);
    table.insert(table.end(), table_top.begin(), table_top.end());

    bottom_left_leg = mat_mult(translation_matrix(-1.0, 1.0, 2.0), unit_leg);
    table.insert(table.end(), bottom_left_leg.begin(), bottom_left_leg.end());

    bottom_right_leg = mat_mult(translation_matrix(1.0, 1.0, 2.0), unit_leg);
    table.insert(table.end(), bottom_right_leg.begin(), bottom_right_leg.end());

    top_left_leg = mat_mult(translation_matrix(-1.0, 1.0, -2.0), unit_leg);
    table.insert(table.end(), top_left_leg.begin(), top_left_leg.end());

    top_right_leg = mat_mult(translation_matrix(1.0, 1.0, -2.0), unit_leg);
    table.insert(table.end(), top_right_leg.begin(), top_right_leg.end());

    return table;
}

vector<GLfloat> build_chair(vector<GLfloat> unit_cube) {
    vector<GLfloat> chair, seat, back, left_cross_line, right_cross_line, short_left_leg, short_right_leg, long_left_leg, long_right_leg;
    vector<GLfloat> unit_leg = mat_mult(scaling_matrix(0.15, 1.15, 0.15), unit_cube);
    vector<GLfloat> unit_cross_line = mat_mult(scaling_matrix(0.1, 1.0, 0.1), unit_cube);
    
    seat = mat_mult(scaling_matrix(1.25, .2, 1.25), unit_cube);
    seat = mat_mult(translation_matrix(2.5, 1.5, 0.5), seat);
    chair.insert(chair.end(), seat.begin(), seat.end());

    back = mat_mult(scaling_matrix(0.75, 0.2, 1.0), unit_cube);
    back = mat_mult(rotation_matrix_z(90.0), back);
    back = mat_mult(translation_matrix(3.0, 3.5, 0.5), back);
    chair.insert(chair.end(), back.begin(), back.end());

    left_cross_line = mat_mult(rotation_matrix_x(-55.0), unit_cross_line);
    left_cross_line = mat_mult(translation_matrix(3.0, 2.5, 0.5), left_cross_line);
    chair.insert(chair.end(), left_cross_line.begin(), left_cross_line.end());

    right_cross_line = mat_mult(rotation_matrix_x(55.0), unit_cross_line);
    right_cross_line = mat_mult(translation_matrix(3.0, 2.5, 0.5), right_cross_line);
    chair.insert(chair.end(), right_cross_line.begin(), right_cross_line.end());

    short_left_leg = mat_mult(translation_matrix(2.0, 1.0, 0.0), unit_leg);
    chair.insert(chair.end(), short_left_leg.begin(), short_left_leg.end());

    short_right_leg = mat_mult(translation_matrix(2.0, 1.0, 1.0), unit_leg);
    chair.insert(chair.end(), short_right_leg.begin(), short_right_leg.end());
            
    long_left_leg = mat_mult(scaling_matrix(1.0, 3.25, 1.0), unit_leg);
    long_left_leg = mat_mult(translation_matrix(3.0, 2.25, 1.0), long_left_leg);
    chair.insert(chair.end(), long_left_leg.begin(), long_left_leg.end());

    long_right_leg = mat_mult(scaling_matrix(1.0, 3.25, 1.0), unit_leg);
    long_right_leg = mat_mult(translation_matrix(3.0, 2.25, 0.0), long_right_leg);
    chair.insert(chair.end(), long_right_leg.begin(), long_right_leg.end());

    chair = mat_mult(rotation_matrix_y(30.0), chair);
    chair = mat_mult(translation_matrix(-0.25, -0.5, 1.75), chair);
    
    return chair;
}

vector<GLfloat> build_lamp(vector<GLfloat> unit_cube) {
    vector<GLfloat> lamp, base, pole, lamp_shade;
    
    base = mat_mult(scaling_matrix(.75, 0.3, .75), unit_cube);
    base = mat_mult(translation_matrix(-1.0, 2.15, 2.0), base);
    lamp.insert(lamp.end(), base.begin(), base.end());

    pole = mat_mult(scaling_matrix(0.15, 1.5, 0.15), unit_cube);
    pole = mat_mult(translation_matrix(-1.0, 3.0, 2.0), pole);
    lamp.insert(lamp.end(), pole.begin(), pole.end());

    lamp_shade = mat_mult(scaling_matrix(0.5, 1.0, 0.5), unit_cube);
    lamp_shade = mat_mult(translation_matrix(-1.0, 3.5, 2.0), lamp_shade);
    lamp.insert(lamp.end(), lamp_shade.begin(), lamp_shade.end());

    return lamp;
}

// Construct the scene using objects built from cubes/prisms
vector<GLfloat> init_scene() {
    vector<GLfloat> scene, table, chair, lamp, laptop;
    vector<GLfloat> unit_cube = build_cube();
    
    table = to_cartesian_coord(build_table(unit_cube));
    scene.insert(scene.end(), table.begin(), table.end());

    chair = to_cartesian_coord(build_chair(unit_cube));
    scene.insert(scene.end(), chair.begin(), chair.end());
        
    lamp = to_cartesian_coord(build_lamp(unit_cube));
    scene.insert(scene.end(), lamp.begin(), lamp.end());

    return scene;
}

// Construct the color mapping of the scene
vector<GLfloat> init_color(vector<GLfloat> scene) {
    vector<GLfloat> colors;
    for (int i = 0; i < scene.size(); i++) {
        colors.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }
    return colors;
}

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vector<GLfloat> scene;
    
    scene = mat_mult(rotation_matrix_y(THETA), to_homogeneous_coord(SCENE));
    scene = to_cartesian_coord(scene);
    
    GLfloat* scene_vertices = vector2array(scene);
    GLfloat* color_vertices = vector2array(COLOR);
    // Pass the scene vertex pointer
    glVertexPointer(3,                // 3 components (x, y, z)
                    GL_FLOAT,         // Vertex type is GL_FLOAT
                    0,                // Start position in referenced memory
                    scene_vertices);  // Pointer to memory location to read from    // Pass the color vertex pointer
    glColorPointer(3,                   // 3 components (r, g, b)
                   GL_FLOAT,            // Vertex type is GL_FLOAT
                   0,                   // Start position in referenced memory
                   color_vertices);     // Pointer to memory location to read from    // Draw quad point planes: each 4 vertices
    glDrawArrays(GL_QUADS, 0, SCENE.size()/3.0);    glFlush();            //Finish rendering
    glutSwapBuffers();
    
    delete scene_vertices;
    delete color_vertices;
}

void idle_func() {
    THETA = THETA + 0.3;
    display_func();
}

int main (int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // Create a window with rendering context and everything else we need
    glutCreateWindow("Assignment 3");
    
    setup();
    init_camera();
    // Setting global variables SCENE and COLOR with actual values
    SCENE = init_scene();
    COLOR = init_color(SCENE);
    
    // Set up our display function
    glutDisplayFunc(display_func);
    glutIdleFunc(idle_func);
    // Render our world
    glutMainLoop();
    
    // Remember to call "delete" on your dynmically allocated arrays
    // such that you don't suffer from memory leaks. e.g.
    // delete arr;
    
    return 0;
}

