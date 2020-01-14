#include <GL/glut.h>

#include "graphics.hh"
#include "main.hh"
#include "point.hh"

typedef struct {
    point position;
    point center;
    point up;
} view;

view VIEW = {
    .position.x = EMITTER_X - 400,
    .position.y = EMITTER_Y,
    .position.z = EMITTER_Z,
    .center.x = EMITTER_X,
    .center.y = EMITTER_Y + 200,
    .center.z = EMITTER_Z,
    .up.x = 0.0,
    .up.y = 1.0,
    .up.z = 0.0
};

view TOP_VIEW = {
    .position.x = EMITTER_X,
    .position.y = 600,
    .position.z = EMITTER_Z,
    .center.x = EMITTER_X,
    .center.y = EMITTER_Y,
    .center.z = EMITTER_Z,
    .up.x = 0.0,
    .up.y = 0.0,
    .up.z = 1.0
};

view *current_view = &VIEW;

void graphics_init(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Fire");
    glutDisplayFunc(generic_display);
    glutReshapeFunc(graphics_reshape);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(POINT_SIZE);
}

void graphics_clear(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void graphics_refresh(void)
{
    glutPostRedisplay();
    glutSwapBuffers();
}

void graphics_mainloop(void)
{
    glutMainLoop();
}

void graphics_particles(void)
{
    glBegin (GL_POINTS);
    for (size_t index = 0; index < fire.particles_alive; ++index)
    {
        glColor3f(fire.particles[index].c.r, fire.particles[index].c.g, fire.particles[index].c.b);
        glVertex3f(fire.particles[index].position.x, fire.particles[index].position.y, fire.particles[index].position.z);
    }
    glEnd();
}

void graphics_reshape(int width, int height)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

void graphics_set_view(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(current_view->position.x, current_view->position.y, current_view->position.z,
            current_view->center.x, current_view->center.y, current_view->center.z,
            current_view->up.x, current_view->up.y, current_view->up.z);
}
