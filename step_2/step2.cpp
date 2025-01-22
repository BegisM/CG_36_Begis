#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Function to draw lines
void Draw_line(float V1[3], float V2[3]) {
    glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
    glEnd();
}

// Function to draw triangle arrowheads
void Draw_triangle(float x, float y, bool isXAxis) {
    glBegin(GL_TRIANGLES);
    if (isXAxis) {
        glVertex3f(x, y, 0.0f);
        glVertex3f(x - 0.4f, y - 0.2f, 0.0f);
        glVertex3f(x - 0.4f, y + 0.2f, 0.0f);
    } else { // Y axis
        glVertex3f(x, y, 0.0f);
        glVertex3f(x - 0.2f, y - 0.4f, 0.0f);
        glVertex3f(x + 0.2f, y - 0.4f, 0.0f);
    }
    glEnd();
}

// Initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-6.0, 6.0, -6.0, 6.0); // Set domain to [-6, 6]
    glMatrixMode(GL_MODELVIEW);
}

// Render axes and arrowheads
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Draw X-axis
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0); // Black
    float V1[3] = {-6.0f, 0.0f, 0.0f};
    float V2[3] = {6.0f, 0.0f, 0.0f};
    Draw_line(V1, V2);

    // Arrowhead for X-axis
    Draw_triangle(6.0f, 0.0f, true);

    // Draw Y-axis
    V1[0] = 0.0f;
    V1[1] = -6.0f;
    V2[0] = 0.0f;
    V2[1] = 6.0f;
    Draw_line(V1, V2);

    // Arrowhead for Y-axis
    Draw_triangle(0.0f, 6.0f, false);

    glColor3f(1.0, 0.0, 0.0);
    float redStart[3] = {-6.0f, 2.0f / 3.0f, 0.0f};
    float redEnd[3] = {6.0f, 26.0f / 3.0f, 0.0f};
    Draw_line(redStart, redEnd);


    glColor3f(0.0, 1.0, 0.0);
    float greenStart[3] = {-6.0f, 11.5f, 0.0f};  // start at (-6, -6)
    float greenEnd[3] = {6.0f, -6.5f, 0.0f};
    Draw_line(greenStart, greenEnd);


    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(12.0);
    glBegin(GL_POINTS);
    glVertex3f(-1.0f, 4.0f, 0.0f);
    glEnd();
    glDisable(GL_POINT_SMOOTH);

    SDL_GL_SwapBuffers();
}

int main(int argc, char* args[]) {
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
        display();
    }

    SDL_Quit();
    return 0;
}
