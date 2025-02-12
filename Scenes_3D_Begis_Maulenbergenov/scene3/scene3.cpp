#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // system
#include <math.h>
using namespace std;

//===================================

const float pi = M_PI;
double theta = pi / 4;  // Vertical angle
double phi = pi / 4;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640.0 / 480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Draw_line(float V1[3], float V2[3]) {
    glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
    glEnd();
}


// Function to draw the coordinate system
void Draw_coord_system() {
    // X axis
    glLineWidth(5.0);
    glColor3f(1.0, 0.0, 0.0);
    float V1[3] = {-5.0, 0.0, 0.0};
    float V2[3] = {5.0, 0.0, 0.0};
    Draw_line(V1, V2);

    // Tip of X axis
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();

    // Y axis
    glColor3f(0.0, 1.0, 0.0);
    V1[0] = 0.0; V1[1] = -5.0;
    V2[0] = 0.0; V2[1] = 5.0;
    Draw_line(V1, V2);

    // Tip of Y axis
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3f(0.0, 5.0, 0.0);
    glEnd();

    // Z axis
    glColor3f(0.0, 0.0, 1.0);
    V1[1] = 0.0; V1[2] = -5.0;
    V2[1] = 0.0; V2[2] = 5.0;
    Draw_line(V1, V2);

    // Tip of Z axis
    glColor4f(0.0, 0.0, 1.0, 0.4);
    glBegin(GL_POINTS);
    glVertex3f(0.0, 0.0, 5.0);
    glEnd();
}

// Function to draw a surface M with F(x1, x2)
void Draw_Surface_M(){
    glColor4f(0.5, 0.5, 0.5, 0.2f); // Grey color for the surface
    float x1, x2, step_x1 = pi/50.0f, step_x2 = 0.1f;
    glLineWidth(1.0);
    for (x1 = 0.0; x1 < 2 * pi; x1 += step_x1) {  // Loop till just below 2*pi
        for (x2 = -3.0; x2 < 0.0; x2 += step_x2) {

            glBegin(GL_TRIANGLE_STRIP);
            // Compute vertices of the triangle
            float x = -cos(x1) * x2;
            float y = -sin(x1) * x2;
            float z = x2;

            float x_next1 = -cos(x1 + step_x1) * x2;
            float y_next1 = -sin(x1 + step_x1) * x2;

            float x_next2 = -cos(x1) * (x2 + step_x2);
            float y_next2 = -sin(x1) * (x2 + step_x2);
            float z_next2 = x2 + step_x2;

            float x_next3 = -cos(x1 + step_x1) * (x2 + step_x2);
            float y_next3 = -sin(x1 + step_x1) * (x2 + step_x2);
            float z_next3 = x2 + step_x2;

            // Specify the triangle vertices
            glVertex3f(x, y, z);
            glVertex3f(x_next1, y_next1, z);
            glVertex3f(x_next2, y_next2, z_next2);
            glVertex3f(x_next3, y_next3, z_next3);
            glEnd();
        }
    }
}

// Function to draw a point p with F(pi/4, -2)
void Draw_Point_p(float radius, int slices, int stacks, float p_x, float p_y, float p_z) {
    float phi1, phi2;
    float theta_p;
    float x, y, z;

    for (int i = 0; i < stacks; ++i) {
        // Calculate latitude angles for current and next stacks
        phi1 = (i * pi / stacks) - (pi / 2);      // Current latitude
        phi2 = ((i + 1) * pi / stacks) - (pi / 2); // Next latitude

        glBegin(GL_TRIANGLE_STRIP); // Start drawing a triangle strip

        for (int j = 0; j <= slices; ++j) {
            // Calculate longitude angle
            theta_p = (j * 2 * pi) / slices;

            // First vertex (current stack)
            x = radius * cos(phi1) * cos(theta_p) + p_x;
            y = radius * cos(phi1) * sin(theta_p) + p_y;
            z = radius * sin(phi1) + p_z;
            glVertex3f(x, y, z);

            // Second vertex (next stack)
            x = radius * cos(phi2) * cos(theta_p) + p_x;
            y = radius * cos(phi2) * sin(theta_p) + p_y;
            z = radius * sin(phi2) + p_z;
            glVertex3f(x, y, z);
        }

        glEnd(); // Finish the triangle strip for this stack
    }
}

// Function to draw a curve g(t)
void Draw_curve_g() {
    glColor3f(1.0, 0.0, 0.0); // Red color for the curve
    float t, step = 0.01f;
    glLineWidth(15.0);
    glBegin(GL_LINE_STRIP);
    for (t = -pi; t <= pi; t += step) {
        float c1 = t + pi / 4.0f; // Parametric equation c1(t)
        float c2 = -2.0f;           // Parametric equation c2(t) (constant)

        // Convert to Cartesian coordinates
        float x = -cos(c1) * c2; // Adjusted for surface M
        float y = -sin(c1) * c2; // Adjusted for surface M
        float z = c2;           // Adjusted for surface M

        glVertex3f(x, y, z);
    }
    glEnd();

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    GLfloat R = 13.0f; // Adjust the camera distance for better view

    gluLookAt(
            R * sin(theta) * cos(phi),
            R * sin(theta) * sin(phi),
            R * cos(theta),
            0.0, 0.0, 0.0,
            0.0, 0.0, 1.0
    );


    Draw_coord_system();
    // Draw the Surface M
    Draw_Surface_M();

    // Calculate point center coordinates
    float p_x = -cos(pi / 4) * -2;
    float p_y = -sin(pi / 4) * -2;
    float p_z = -2;

    // Draw the point
    glColor3f(0.0, 0.0, 1.0);  // Blue color
    Draw_Point_p(0.2f, 20, 20, p_x, p_y, p_z);

    // Draw the point
    Draw_curve_g();
}

// Function to handle keyboard input for camera rotation
void handle_input(SDL_Event event) {
    const double angle_step = 0.1; // Angle step for camera rotation


    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                theta -= angle_step; // Move camera up
                if (theta < 0.1) theta = 0.1; // Prevent flipping
                break;
            case SDLK_DOWN:
                theta += angle_step; // Move camera down
                if (theta > pi - 0.1) theta = pi - 0.1; // Prevent flipping
                break;
            case SDLK_LEFT:
                phi -= angle_step; // Move camera left
                break;
            case SDLK_RIGHT:
                phi += angle_step; // Move camera right
                break;
        }
    }
}

int main(int argc, char *args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(320, 240, 32, SDL_SWSURFACE | SDL_OPENGL);

    int running = 1;
    SDL_Event event;

    init();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            handle_input(event);
        }

        display();
        SDL_GL_SwapBuffers();
        SDL_Delay(16); // Delay for ~60 FPS
    }

    SDL_Quit();
    return 0;
}
