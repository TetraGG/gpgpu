#include <GL/glut.h>

#include "graphics.hh"
#include "main.hh"

typedef struct {
    double positionx;
    double positiony;
    double positionz;
    double centerx;
    double centery;
    double centerz;
    double upx;
    double upy;
    double upz;
} view;

view VIEW = {
    .positionx = EMITTER_X - 400,
    .positiony = EMITTER_Y,
    .positionz = EMITTER_Z,
    .centerx = EMITTER_X,
    .centery = EMITTER_Y + 200,
    .centerz = EMITTER_Z,
    .upx = 0.0,
    .upy = 1.0,
    .upz = 0.0
};

view TOP_VIEW = {
    .positionx = EMITTER_X,
    .positiony = 600,
    .positionz = EMITTER_Z,
    .centerx = EMITTER_X,
    .centery = EMITTER_Y,
    .centerz = EMITTER_Z,
    .upx = 0.0,
    .upy = 0.0,
    .upz = 1.0
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
    gluLookAt(current_view->positionx, current_view->positiony, current_view->positionz,
            current_view->centerx, current_view->centery, current_view->centerz,
            current_view->upx, current_view->upy, current_view->upz);
}
