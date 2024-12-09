import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

def draw_axes():
    """Draw the 3D coordinate system axes."""
    glBegin(GL_LINES)

    # X-axis (red)
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-10.0, 0.0, 0.0)
    glVertex3f(10.0, 0.0, 0.0)

    # Y-axis (green)
    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.0, -10.0, 0.0)
    glVertex3f(0.0, 10.0, 0.0)

    # Z-axis (blue)
    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.0, -10.0)
    glVertex3f(0.0, 0.0, 10.0)

    glEnd()

def draw_surface():
    R = 5.0  # Radius of the surface
    pi = np.pi  # Pi constant

    # Y coordinates array
    d = np.linspace(-10, 10, 21)  # Generate 21 points from -10 to 10

    glBegin(GL_TRIANGLE_STRIP)
    glColor4f(1.0, 0.0, 0.0, 0.5)  # Semi-transparent red color

    for i in range(len(d) - 1):  # Loop over the y-coordinate intervals
        for j in range(20):  # Generate 21 points for x (theta) from 0 to 2*pi
            theta = j * pi / 10  # Angle step
            # First vertex
            glVertex3f(R * np.cos(theta), R * np.sin(theta), d[i])
            # Second vertex
            glVertex3f(R * np.cos(theta), R * np.sin(theta), d[i + 1])

    glEnd()


def setup_opengl():
    """Setup OpenGL environment."""
    glClearColor(0.1, 0.1, 0.1, 1.0)  # Background color (dark gray)
    glEnable(GL_DEPTH_TEST)           # Enable depth testing

def main():
    # Initialize Pygame and create an OpenGL-enabled window
    pygame.init()
    display = (800, 600)
    pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    pygame.display.set_caption("3D Coordinate System")

    # Setup OpenGL perspective
    gluPerspective(45, (display[0] / display[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -20)  # Move the camera back

    setup_opengl()

    # Main loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False

        # Clear the screen and the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        # Rotate the scene for better viewing
        glRotatef(1, 3, 1, 0)  # Rotate 1 degree around X, Y, and Z axes

        # Draw the coordinate system
        draw_axes()
        draw_surface()

        # Update the display
        pygame.display.flip()
        pygame.time.wait(10)

    pygame.quit()

if __name__ == '__main__':
    main()
