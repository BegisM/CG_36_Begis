#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // system
#include <math.h>
using namespace std;

//===================================

double pi=3.14159265359;

//-------------------------------
// ranges
double x1_min=0, x1_max=2*pi, dx1=.1;
double x2_min=-10, x2_max=10, dx2=.1; // height of the cylinder
// Parametrization F

double r=10; // radius of the cylinder

double F1(double x1, double x2) {
  return r*cos(x1);
}

double F2(double x1, double x2) {
  return r*sin(x1);
}

double F3(double x1, double x2) {
  return x2;
}

//-------------------------------


void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
}


void Draw_line(float V1 [3],float V2 [3])
{

glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
glEnd();
}

void draw_x_filed(float b_v, float length){
    if (b_v < 0){
        length = -1*length;
    }
    glBegin(GL_LINES);
        glColor3f( 0.0, 0.0, 1.0);
        glVertex3f(b_v, 0, 0);
        glVertex3f(b_v + length, 0, 0);
    glEnd();
}

void draw_y_filed(float b_v, float length){
    if (b_v < 0){
        length = -1*length;
    }
    glBegin(GL_LINES);
        glColor3f( 0.0, 0.0, 1.0);
        glVertex3f(0, b_v, 0);
        glVertex3f(0, b_v + length, 0);
    glEnd();
}


void display()
{
//------
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();
glPushMatrix();

GLfloat a=.25*pi;
GLfloat R=50; // Adjust the camera distance for better view

gluLookAt(R*cos(a), R*sin(a), 25.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);


//--------------------------------------
// Coordinate system

//------------------------
// X axis
glLineWidth(5.0);
glColor3f( 1.0, 0.0, 0.0);
float V1 [3] = {-25.0, 0.0f,0.0f};
float V2 [3] = {25.0, 0.0f,0.0f};
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(25);
glEnable(GL_POINT_SMOOTH);
glColor4f( 1.0, 0.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(25,0,0);
glEnd();
//-----------------
//------------------------


//------------------------
// Y axis
glColor3f( 0.0, 1.0, 0.0);
V1[0] = 0.0;
V1[1] = -25.0;
V2[0] = 0.0;
V2[1] = 25.0;
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 1.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(0,25,0);
glEnd();
//-----------------


//------------------------

//------------------------
// Z axis
glColor3f( 0.0, 0.0, 1.0);
V1[1] = 0.0;
V1[2] = -25.0;
V2[1] = 0.0;
V2[2] = 25.0;
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 0.0, 1.0, .4);
glBegin(GL_POINTS);
    glVertex3f(0,0,25);
glEnd();
//-----------------
// end: Z axis
//------------------------


/* End: coord system */
//--------------------------------------


//--------------------------

double y1=0, y2=0, y3=0;
double x1=0;
double x2=0;

glColor4f( 1.0, 0.0, 0.0, .3);

for (int j = 0; x2_min+j*dx2 <= x2_max; j++) {
// build horizontally
glBegin(GL_TRIANGLE_STRIP);
for (int i = 0; x1_min+i*dx1 <= x1_max; i++) {
//--------------
// First point
  x1=x1_min+i*dx1;
  x2=x2_min+j*dx2;

  y1=F1(x1,x2);
  y2=F2(x1,x2);
  y3=F3(x1,x2);

  glVertex3f(y1,y2,y3);
//--------------

//--------------
// Second point
  x2=x2+dx2;

  y1=F1(x1,x2);
  y2=F2(x1,x2);
  y3=F3(x1,x2);

  glVertex3f(y1,y2,y3);
//--------------

}
glEnd();
}

//--------------------------
draw_x_filed(20.0 , 10.0);
draw_x_filed(-20.0 , 10.0);
draw_y_filed(20.0 , 10.0);
draw_y_filed(-20.0 , 10.0);

glPopMatrix();

}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;

    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {

        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
            }
        }
       display();

        SDL_GL_SwapBuffers();

    }
    SDL_Quit();
    return 0;
}
