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

double pi = 3.14159265359;

// Ranges
double x1_min = 0, x1_max = 2 * pi, dx1 = .1;
double x2_min = -10, x2_max = 10, dx2 = .1; // height of the cylinder

double r = 10; // radius of the cylinder

double F1(double x1, double x2) {
    return r * cos(x1);
}

double F2(double x1, double x2) {
    return r * sin(x1);
}

double F3(double x1, double x2) {
    return x2;
}

double alpha = 0.0; // Global transparency parameter

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

void draw_x_field(float b_v, float length, float alpha) {
    glColor4f(0.0, 0.0, 1.0, alpha); // Set color with transparency
    glBegin(GL_LINES);
    glVertex3f(b_v, 0, 0);
    glVertex3f(b_v + length, 0, 0);
    glVertex3f(-b_v, 0, 0);
    glVertex3f(-b_v - length, 0, 0);
    glEnd();
}

void draw_y_field(float b_v, float length, float alpha) {
    glColor4f(0.0, 0.0, 1.0, alpha); // Set color with transparency
    glBegin(GL_LINES);
    glVertex3f(0, b_v, 0);
    glVertex3f(0, b_v + length, 0);
    glVertex3f(0, -b_v, 0);
    glVertex3f(0, -b_v - length, 0);
    glEnd();
}

void draw_cylinder() {
    glColor4f(1.0, 0.0, 0.0, 0.4); // Gray color for the cylinder
    glBegin(GL_QUADS);

    for (double x1 = x1_min; x1 < x1_max; x1 += dx1) {
        for (double x2 = x2_min; x2 < x2_max; x2 += dx2) {
            // Calculate vertices for a small quad
            double x1_next = x1 + dx1;
            double x2_next = x2 + dx2;

            glVertex3f(F1(x1, x2), F2(x1, x2), F3(x1, x2));
            glVertex3f(F1(x1_next, x2), F2(x1_next, x2), F3(x1_next, x2));
            glVertex3f(F1(x1_next, x2_next), F2(x1_next, x2_next), F3(x1_next, x2_next));
            glVertex3f(F1(x1, x2_next), F2(x1, x2_next), F3(x1, x2_next));
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glPushMatrix();

    GLfloat a = .25 * pi;
    GLfloat R = 50; // Adjust the camera distance for better view

    gluLookAt(R * cos(a), R * sin(a), 25.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    //--------------------------------------
    // Coordinate system
    // X axis
    glLineWidth(5.0);
    glColor3f(1.0, 0.0, 0.0);
    float V1[3] = {-10.0, 0.0f, 0.0f};
    float V2[3] = {10.0, 0.0f, 0.0f};

    Draw_line(V1, V2);


    // Y axis
    glColor3f(0.0, 1.0, 0.0);
    V1[0] = 0.0f;
    V1[1] = -10.0;
    V2[0] = 0.0f;
    V2[1] = 10.0;
    Draw_line(V1, V2);

    // Hide x axis between -25 to -10 and 10 to 25 after some time
    glLineWidth(4.0);
    glColor4f(1.0, 0.0, 0.0, 1 - alpha);
    if (alpha <= 0.5) {
        V1[0] = -25.0;
        V1[1] = 0.0f;
        V2[0] = -10.0;
        V2[1] = 0.0f;
        Draw_line(V1, V2);
        V1[0] = 10.0;
        V2[0] = 25.0;
        Draw_line(V1, V2);
    }

    // Hide y axis between -25 to -10 and 10 to 25 after some time
    glColor4f(0.0, 1.0, 0.0, 1 - alpha);
    if (alpha <= 0.5) {
        V1[0] = 0.0f;
        V1[1] = -25.0;
        V2[0] = 0.0f;
        V2[1] = -10.0;
        Draw_line(V1, V2);
        V1[1] = 25.0;
        V2[1] = 10.0;
        Draw_line(V1, V2);
    }

    // Z axis
    glColor3f(0.0, 0.0, 1.0);
    V1[1] = 0.0;
    V1[2] = -25.0;
    V2[1] = 0.0;
    V2[2] = 25.0;
    Draw_line(V1, V2);

    draw_cylinder();

    // Animate vector field once alpha reaches threshold
    if (alpha > 0.5) {
        draw_y_field(10.0, 20.0, alpha);
        draw_x_field(10.0, 20.0, alpha);
    }

    glPopMatrix();
}


int main(int argc, char *args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int running = 1;
    SDL_Event event;

    init();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Gradually increase the alpha value
        if (alpha < 1.0) {
            alpha += 0.001; // Adjust speed of appearance
        }

        display();
        SDL_GL_SwapBuffers();
        SDL_Delay(16); // Delay for ~60 FPS
    }

    SDL_Quit();
    return 0;
}
