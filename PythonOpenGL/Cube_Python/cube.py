import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

vertices = [
    [-1, -1, 1], [1, -1, 1], [1, 1, 1], [-1, 1, 1],  # Front face
    [-1, -1, -1], [-1, 1, -1], [1, 1, -1], [1, -1, -1]  # Back face
]

faces = [
    (0, 1, 2, 3), (4, 5, 6, 7),  # Front and Back
    (0, 3, 5, 4), (1, 2, 6, 7),  # Left and Right
    (3, 2, 6, 5), (0, 1, 7, 4)  # Top and Bottom
]

colors = [
    (1, 0, 0), (0, 1, 0), (0, 0, 1),
    (0.5, 0.5, 0.5), (1, 0, 1), (0, 1, 1)
]


def draw_cube():
    glBegin(GL_QUADS)
    for i, face in enumerate(faces):
        glColor3fv(colors[i])
        for vertex in face:
            glVertex3fv(vertices[vertex])
    glEnd()


def main():
    pygame.init()

    # Get the screen resolution
    display_info = pygame.display.Info()
    screen_width, screen_height = display_info.current_w, display_info.current_h

    # Set the display mode to fullscreen
    screen = pygame.display.set_mode((screen_width, screen_height), DOUBLEBUF | OPENGL | FULLSCREEN)

    # Perspective and initial translation
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (1, 1, 1, 1))
    glLightfv(GL_LIGHT0, GL_AMBIENT, (0.2, 0.2, 0.2, 1.0))
    glLightfv(GL_LIGHT0, GL_POSITION, (-2, 2, -3, 1))

    # Adjust the aspect ratio of the projection
    gluPerspective(45, screen_width / float(screen_height), 1, 50)

    glTranslatef(0, 0, -5)

    clock = pygame.time.Clock()
    angle = 0
    running = True

    while running:
        for event in pygame.event.get():
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                running = False

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glPushMatrix()  # Save current transformation matrix
        glRotatef(angle, -1, 1, 1)  # Apply rotation

        draw_cube()

        glPopMatrix()  # Restore transformation matrix
        pygame.display.flip()
        clock.tick(30)
        angle += 0.5

    pygame.quit()


main()
