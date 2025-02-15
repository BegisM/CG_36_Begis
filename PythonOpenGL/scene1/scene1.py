import math
from OpenGL.GL import *
from OpenGL.GLU import *
import pygame
from pygame.locals import *

# ===================================

pi = math.pi
theta = pi / 4  # Vertical angle
phi = pi / 4


def init():
    glClearColor(1.0, 1.0, 1.0, 1.0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60, 640.0 / 480.0, 1.0, 500.0)
    glMatrixMode(GL_MODELVIEW)
    glEnable(GL_DEPTH_TEST)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glEnable(GL_BLEND)


def draw_line(V1, V2):
    glBegin(GL_LINES)
    glVertex3f(V1[0], V1[1], V1[2])
    glVertex3f(V2[0], V2[1], V2[2])
    glEnd()


# Function to draw the coordinate system
def draw_coord_system():
    # X axis
    glLineWidth(5.0)
    glColor3f(1.0, 0.0, 0.0)
    V1 = [-5.0, 0.0, 0.0]
    V2 = [5.0, 0.0, 0.0]
    draw_line(V1, V2)

    # Tip of X axis
    glPointSize(15)
    glEnable(GL_POINT_SMOOTH)
    glColor4f(1.0, 0.0, 0.0, 1.0)
    glBegin(GL_POINTS)
    glVertex3f(5.0, 0.0, 0.0)
    glEnd()

    # Y axis
    glColor3f(0.0, 1.0, 0.0)
    V1 = [0.0, -5.0, 0.0]
    V2 = [0.0, 5.0, 0.0]
    draw_line(V1, V2)

    # Tip of Y axis
    glColor4f(0.0, 1.0, 0.0, 1.0)
    glBegin(GL_POINTS)
    glVertex3f(0.0, 5.0, 0.0)
    glEnd()

    # Z axis
    glColor3f(0.0, 0.0, 1.0)
    V1 = [0.0, 0.0, -5.0]
    V2 = [0.0, 0.0, 5.0]
    draw_line(V1, V2)

    # Tip of Z axis
    glColor4f(0.0, 0.0, 1.0, 0.4)
    glBegin(GL_POINTS)
    glVertex3f(0.0, 0.0, 5.0)
    glEnd()


# Function to draw a surface M with F(x1, x2)
def draw_surface_M():
    glColor4f(0.5, 0.5, 0.5, 0.2)  # Grey color for the surface
    x1 = 0.0
    x2 = -3.0
    step_x1 = pi / 50.0
    step_x2 = 0.1
    glLineWidth(1.0)

    while x1 < 2 * pi:
        while x2 < 0.0:
            glBegin(GL_TRIANGLE_STRIP)

            # Compute vertices of the triangle
            x = -math.cos(x1) * x2
            y = -math.sin(x1) * x2
            z = x2

            x_next1 = -math.cos(x1 + step_x1) * x2
            y_next1 = -math.sin(x1 + step_x1) * x2

            x_next2 = -math.cos(x1) * (x2 + step_x2)
            y_next2 = -math.sin(x1) * (x2 + step_x2)
            z_next2 = x2 + step_x2

            x_next3 = -math.cos(x1 + step_x1) * (x2 + step_x2)
            y_next3 = -math.sin(x1 + step_x1) * (x2 + step_x2)
            z_next3 = x2 + step_x2

            # Specify the triangle vertices
            glVertex3f(x, y, z)
            glVertex3f(x_next1, y_next1, z)
            glVertex3f(x_next2, y_next2, z_next2)
            glVertex3f(x_next3, y_next3, z_next3)

            glEnd()
            x2 += step_x2
        x1 += step_x1
        x2 = -3.0


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    R = 13.0  # Adjust the camera distance for better view

    gluLookAt(
        R * math.sin(theta) * math.cos(phi),
        R * math.sin(theta) * math.sin(phi),
        R * math.cos(theta),
        0.0, 0.0, 0.0,
        0.0, 0.0, 1.0
    )

    draw_coord_system()
    draw_surface_M()


# Function to handle keyboard input for camera rotation
def handle_input():
    global theta, phi
    angle_step = 0.1  # Angle step for camera rotation

    keys = pygame.key.get_pressed()
    if keys[K_UP]:
        theta -= angle_step  # Move camera up
        if theta < 0.1:
            theta = 0.1  # Prevent flipping
    if keys[K_DOWN]:
        theta += angle_step  # Move camera down
        if theta > pi - 0.1:
            theta = pi - 0.1  # Prevent flipping
    if keys[K_LEFT]:
        phi -= angle_step  # Move camera left
    if keys[K_RIGHT]:
        phi += angle_step  # Move camera right


def main():
    pygame.init()
    pygame.display.set_mode((640, 480), DOUBLEBUF | OPENGL)
    init()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        handle_input()
        display()
        pygame.display.flip()
        pygame.time.wait(16)  # Delay for ~60 FPS

    pygame.quit()



main()
