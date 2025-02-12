import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *


def draw_line(start, end, color):
    """Draw a line between two points with the given color."""
    glColor3f(*color)
    glBegin(GL_LINES)
    glVertex2f(*start)
    glVertex2f(*end)
    glEnd()


def draw_point(position, color, size=14):
    """Draw a point at the given position with the given color and size."""
    glEnable(GL_POINT_SMOOTH)  # Enable smooth (round) points
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST)  # Best quality
    glColor3f(*color)
    glPointSize(size)
    glBegin(GL_POINTS)
    glVertex2f(*position)
    glEnd()
    glDisable(GL_POINT_SMOOTH)


def draw_arrowhead(x, y, isXAxis, size=0.4):
    """Draw a triangle arrowhead for an axis."""
    glColor3f(0, 0, 0)
    glBegin(GL_TRIANGLES)
    if isXAxis:
        glVertex2f(x, y)
        glVertex2f(x - size, y - size / 2)
        glVertex2f(x - size, y + size / 2)
    else:
        glVertex2f(x, y)
        glVertex2f(x - size / 2, y - size)
        glVertex2f(x + size / 2, y - size)
    glEnd()


def setup_opengl():
    """Setup OpenGL for 2D rendering."""
    glClearColor(1.0, 1.0, 1.0, 1.0)  # White background
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(-8, 8, -8, 8)  # Set the coordinate system
    glMatrixMode(GL_MODELVIEW)


def display_everything():
    draw_line((-8, 0), (8, 0), (0, 0, 0))  # X-axis
    draw_arrowhead(8, 0, True)  # Arrowhead for X-axis
    draw_line((0, -8), (0, 8), (0, 0, 0))  # Y-axis
    draw_arrowhead(0, 8, False)  # Arrowhead for Y-axis

    glLineWidth(5.0)
    # Draw the red line
    red_start = (-8.0, -7.0 / 3.0)
    red_end = (8.0, 25.0 / 3.0)
    draw_line(red_start, red_end, (1.0, 0.0, 0.0))

    # Draw the green line
    green_start = (-8.0, -11.5)
    green_end = (8.0, 12.5)
    draw_line(green_start, green_end, (0.0, 1.0, 0.0))

    # Draw the blue point
    draw_point((3.0, 5.0), (0.0, 0.0, 1.0))

def main():
    # Initialize pygame and set up an OpenGL context
    pygame.init()
    display = (800, 600)
    pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    pygame.display.set_caption("2D Line Plot")

    setup_opengl()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False

        # Clear the screen
        glClear(GL_COLOR_BUFFER_BIT)

        display_everything()

        pygame.display.flip()
        pygame.time.wait(10)

    pygame.quit()



main()
