#include "emitter.h"
#include "view.h"

#include <GL/glut.h>

/******************************************************************************
* Reshape function called whenever the application window is reshaped
******************************************************************************/
void reshape(int width, int height)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

void graphics_init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Particle system");
	glutFullScreen();
	glutDisplayFunc(particles_display);
	glutReshapeFunc(reshape);

	// Render points as circles and make them span a few pixels instead of one
	glEnable(GL_POINT_SMOOTH);
	glPointSize(POINT_SIZE);
}

void particles_draw(void)
{
   // Draw the fountain
    glBegin (GL_POINTS);
    // Draw the smoke
    for (int index = 0; index < fire.alive_particles; index++)
    {
      glColor3f(fire.particles[index].color.r, fire.particles[index].color.g, fire.particles[index].color.b);
      glVertex3f(fire.particles[index].position.x, fire.particles[index].position.y, fire.particles[index].position.z);
    }
    glEnd();
}

void graphics_mainloop(void)
{
	glutMainLoop();
}

void graphics_clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void set_view(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(current_view.position.x, current_view.position.y, current_view.position.z,
			  current_view.center.x, current_view.center.y, current_view.center.z,
			  current_view.direction.x, current_view.direction.y, current_view.direction.z);
}
