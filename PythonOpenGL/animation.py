import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import math

# Constants
pi = 3.14159265359

# Ranges
x1_min, x1_max, dx1 = 0, 2 * pi, 0.1
x2_min, x2_max, dx2 = -10, 10, 0.1  # height of the cylinder
r = 10  # radius of the cylinder
length_v, start_v = 10.0, 10.0

alpha = 0.0  # Global transparency parameter


def F1(x1, x2):
    return r * math.cos(x1)


def F2(x1, x2):
    return r * math.sin(x1)


def F3(x1, x2):
    return x2


def init():
    glClearColor(1.0, 1.0, 1.0, 1.0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60, 640.0 / 480.0, 1.0, 500.0)
    glMatrixMode(GL_MODELVIEW)
    glEnable(GL_DEPTH_TEST)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glEnable(GL_BLEND)


def Draw_line(V1, V2):
    glBegin(GL_LINES)
    glVertex3f(V1[0], V1[1], V1[2])
    glVertex3f(V2[0], V2[1], V2[2])
    glEnd()


def draw_x_field(b_v, length, alpha):
    glColor4f(0.0, 0.0, 1.0, alpha)  # Set color with transparency
    glBegin(GL_LINES)
    glVertex3f(b_v, 0, 0)
    glVertex3f(b_v + length, 0, 0)
    glVertex3f(-b_v, 0, 0)
    glVertex3f(-b_v - length, 0, 0)
    glEnd()


def draw_y_field(b_v, length, alpha):
    glColor4f(0.0, 0.0, 1.0, alpha)  # Set color with transparency
    glBegin(GL_LINES)
    glVertex3f(0, b_v, 0)
    glVertex3f(0, b_v + length, 0)
    glVertex3f(0, -b_v, 0)
    glVertex3f(0, -b_v - length, 0)
    glEnd()


def draw_cylinder():
    glColor4f(1.0, 0.0, 0.0, 0.4)  # Gray color for the cylinder
    glBegin(GL_QUADS)

    for x1 in frange(x1_min, x1_max, dx1):
        for x2 in frange(x2_min, x2_max, dx2):
            # Calculate vertices for a small quad
            x1_next = x1 + dx1
            x2_next = x2 + dx2

            glVertex3f(F1(x1, x2), F2(x1, x2), F3(x1, x2))
            glVertex3f(F1(x1_next, x2), F2(x1_next, x2), F3(x1_next, x2))
            glVertex3f(F1(x1_next, x2_next), F2(x1_next, x2_next), F3(x1_next, x2_next))
            glVertex3f(F1(x1, x2_next), F2(x1, x2_next), F3(x1, x2_next))

    glEnd()


# Utility function for range in Python with float step
def frange(start, stop, step):
    while start < stop:
        yield start
        start += step


def display():
    global alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glLoadIdentity()
    glPushMatrix()

    a = 0.25 * pi
    R = 50  # Adjust the camera distance for better view

    gluLookAt(R * math.cos(a), R * math.sin(a), 25.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)

    # Coordinate system
    # X axis
    glLineWidth(5.0)
    glColor3f(1.0, 0.0, 0.0)
    V1 = [-1.0 * start_v, 0.0, 0.0]
    V2 = [start_v, 0.0, 0.0]
    Draw_line(V1, V2)

    # Y axis
    glColor3f(0.0, 1.0, 0.0)
    V1 = [0.0, -1.0 * start_v, 0.0]
    V2 = [0.0, start_v, 0.0]
    Draw_line(V1, V2)

    # Hide x axis between -25 to -10 and 10 to 25 after some time
    glLineWidth(4.0)
    glColor4f(1.0, 0.0, 0.0, 1 - alpha)
    if alpha <= 0.5:
        V1 = [-1.0 * start_v, 0.0, 0.0]
        V2 = [-1.0 * (start_v + length_v), 0.0, 0.0]
        Draw_line(V1, V2)
        V1 = [start_v, 0.0, 0.0]
        V2 = [start_v + length_v, 0.0, 0.0]
        Draw_line(V1, V2)

    # Hide y axis between -25 to -10 and 10 to 25 after some time
    glColor4f(0.0, 1.0, 0.0, 1 - alpha)
    if alpha <= 0.5:
        V1 = [0.0, -1.0 * start_v, 0.0]
        V2 = [0.0, -1.0 * (start_v + length_v), 0.0]
        Draw_line(V1, V2)
        V1 = [0.0, start_v, 0.0]
        V2 = [0.0, start_v + length_v, 0.0]
        Draw_line(V1, V2)


    if start_v + length_v < 25:
        glColor3f(0.0, 1.0, 0.0)
        V1 = [0.0, -1.0 * (start_v + length_v), 0.0]
        V2 = [0.0, -25.0, 0.0]
        Draw_line(V1, V2)
        V1 = [0.0, start_v + length_v, 0.0]
        V2 = [0.0, 25, 0.0]
        Draw_line(V1, V2)
        glColor3f(1.0, 0.0, 0.0)
        V1 = [-1.0 * (start_v + length_v), 0.0, 0.0]
        V2 = [-25.0, 0.0, 0.0]
        Draw_line(V1, V2)
        V1 = [start_v + length_v, 0.0, 0.0]
        V2 = [25, 0.0, 0.0]
        Draw_line(V1, V2)

    # Z axis
    glColor3f(0.0, 0.0, 1.0)
    V1 = [0.0, 0.0, -25.0]
    V2 = [0.0, 0.0, 25.0]
    Draw_line(V1, V2)

    draw_cylinder()

    # Animate vector field once alpha reaches threshold
    if alpha > 0.5:
        draw_y_field(start_v, length_v, alpha)
        draw_x_field(start_v, length_v, alpha)

    glPopMatrix()


def main():
    global alpha

    pygame.init()
    display_mode = (640, 480)
    pygame.display.set_mode(display_mode, DOUBLEBUF | OPENGL)
    init()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Gradually increase the alpha value
        if alpha < 1.0:
            alpha += 0.01  # Adjust speed of appearance

        display()
        pygame.display.flip()
        pygame.time.wait(16)  # Delay for ~60 FPS

    pygame.quit()


if __name__ == "__main__":
    main()
