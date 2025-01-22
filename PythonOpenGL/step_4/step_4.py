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


def draw_point(position, color, size=10):
    """Draw a point at the given position with the given color and size."""
    glColor3f(*color)
    glPointSize(size)
    glBegin(GL_POINTS)
    glVertex2f(*position)
    glEnd()


def draw_arrowhead(x, y, isXAxis, size=0.3):
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
    gluOrtho2D(-6, 6, -6, 6)  # Set the coordinate system
    glMatrixMode(GL_MODELVIEW)


def display_everything():
    draw_line((-6, 0), (6, 0), (0, 0, 0))  # X-axis
    draw_arrowhead(6, 0, True)  # Arrowhead for X-axis
    draw_line((0, -6), (0, 6), (0, 0, 0))  # Y-axis
    draw_arrowhead(0, 6, False)  # Arrowhead for Y-axis

    # Draw the red line
    red_start = (-6.0, 2.0 / 3.0)
    red_end = (6.0, 26.0 / 3.0)
    draw_line(red_start, red_end, (1.0, 0.0, 0.0))

    # Draw the green line
    green_start = (-6.0, 4.0)
    green_end = (6.0, 4.0)
    draw_line(green_start, green_end, (0.0, 1.0, 0.0))

    # Draw the blue point
    draw_point((-1.0, 4.0), (0.0, 0.0, 1.0))

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
