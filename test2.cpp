#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
//============================
//=====================================================

#include <math.h>
#include <cmath>
//============================

//=================================
// Vortices:

float V1 [3] = {0.0f, 0.0f,0.0f};
float V2 [3] = {1.0, 0.0f,0.0f};
float V3 [3] = {0.0f, 1.0f,0.0f};
float V4 [3] = {0.0f, 0.0f,1.0f};
//===================================




void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
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


void f(double x, double y,double r){
    glVertex3f(r * cos(x),r * sin(x), y);
}


void display()
{
//------
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();

GLfloat pi=3.14, a=.1;
GLfloat r=20;

gluLookAt(r*cos(a*pi), r*sin(a*pi), 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);


//--------------------------------------
// Coordinate system

//------------------------
// X axis
glLineWidth(5.0);
glColor3f( 1.0, 0.0, 0.0);
float V1 [3] = {-5.0, 0.0f,0.0f};
float V2 [3] = {5.0, 0.0f,0.0f};
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 1.0, 0.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(5,0,0);
glEnd();
//-----------------
//------------------------


//------------------------
// Y axis
glColor3f( 0.0, 1.0, 0.0);
V1[0] = 0.0;
V1[1] = -5.0;
V2[0] = 0.0;
V2[1] = 5.0;
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 1.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(0,5,0);
glEnd();
//-----------------

//------------------------

//------------------------
// Z axis
glColor3f( 0.0, 0.0, 1.0);
V1[1] = 0.0;
V1[2] = -5.0;
V2[1] = 0.0;
V2[2] = 5.0;
Draw_line(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 0.0, 1.0, 1);
glBegin(GL_POINTS);
    glVertex3f(0,0,5);
glEnd();
//-----------------
// end: Z axis
//------------------------


//End: coord system
//--------------------------------------


//--------------------------
glBegin(GL_TRIANGLE_STRIP);
    double R = 5.0;
    //double x1, x2;
    glColor4f( 1.0, 0.0, 0.0, 0.5);
    //x1 = 0;
    //x2 = 0;
    int d[21] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i<21; i++){
        for (int j = 0; j<21; j++){
            f(i*pi/10, d[i], R);
            f(i*pi/10, d[i+1], R);}
        //f((i+1)*pi/10, d[i], R);
    }

//    glVertex3f(R * cos(x1),R * sin(x1), x2);
    //glVertex3f(0,0,0);
    //glVertex3f(0,0,5);
    //glVertex3f(2,0,0);
    //glVertex3f(2,0,5);
    //glVertex3f(4,0,0);
    //glVertex3f(4,0,5);

glEnd();
//--------------------------


//--------------------------------------
// Planes

//----------------------------------
//glColor4f( 1.0, 0.0, 0.0, 0.1);
//glBegin(GL_POLYGON);
//    glVertex3f(-2,-2,5);
//    glVertex3f(2, -2, 1);
//    glVertex3f(2, 2, -3);
//    glVertex3f(-2, 2, 1);
//glEnd();
//----------------------------------

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
