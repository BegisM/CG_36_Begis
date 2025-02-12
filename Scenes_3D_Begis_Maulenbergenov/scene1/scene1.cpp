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
