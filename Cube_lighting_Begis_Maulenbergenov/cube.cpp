#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void drawCube()
{
    float difamb[] = {1.0, 1.0, 1.0, 1.0}; // White material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    // Back face
    glNormal3f(0.0, 0.0, -1.0);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Left face
    glNormal3f(-1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    // Right face
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5); // Grey
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    // Top face
    glNormal3f(0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);

    // Bottom face
    glNormal3f(0.0, -1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glEnd();
}

float angle = 0.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    float dif[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);

    float amb[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float pos[] = {-2.0, 2.0, -3.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, -1.0, 1.0, 1.0); // Rotate around (-1,1,1)

    drawCube();
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE | SDL_OPENGL | SDL_FULLSCREEN);

    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;

    init();

    while (running)
    {
        start = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        display();
        SDL_GL_SwapBuffers();

        angle += 0.5; // Rotation speed

        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }

    SDL_Quit();
    return 0;
}
