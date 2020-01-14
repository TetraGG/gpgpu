#include "graphics.h"

#include "main.h"

#include <GL/glut.h>

typedef struct {
	double eyeX, eyeY, eyeZ;            // position of camera
    double centerX, centerY, centerZ;   // point at which camera looks
    double upX, upY, upZ;               // "up" direction of camera
} CameraView;

CameraView SMOKE_VIEW = {
    .eyeX = SMOKE_EMITTER_X - 400,
    .eyeY = SMOKE_EMITTER_Y,
    .eyeZ = SMOKE_EMITTER_Z,
    .centerX = SMOKE_EMITTER_X,
    .centerY = SMOKE_EMITTER_Y + 200,
    .centerZ = SMOKE_EMITTER_Z,
    .upX = 0.0,
    .upY = 1.0,
    .upZ = 0.0
};

// View of the smoke from above
CameraView SMOKE_TOP_VIEW = {
    .eyeX = SMOKE_EMITTER_X,
    .eyeY = 600,
    .eyeZ = SMOKE_EMITTER_Z,
    .centerX = SMOKE_EMITTER_X,
    .centerY = SMOKE_EMITTER_Y,
    .centerZ = SMOKE_EMITTER_Z,
    .upX = 0.0,
    .upY = 0.0,
    .upZ = 1.0
};

// Current view
CameraView *currentView = &SMOKE_VIEW;

void graphics_init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Particle system");
	glutDisplayFunc(generic_display);
	glutReshapeFunc(graphics_reshape);

	// Render points as circles and make them span a few pixels instead of one
	glEnable(GL_POINT_SMOOTH);
	glPointSize(POINT_SIZE);
}

void graphics_clear()
{
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the screen and depth buffer
}

void graphics_refresh()
{
	glutPostRedisplay();                  // Mark the current window to be redisplayed
	glutSwapBuffers();                    // Double buffering in place

}

void graphics_mainloop()
{
	glutMainLoop();
}

void graphics_particles()
{
	// Draw the fountain
	glBegin (GL_POINTS);
	// Draw the smoke
	for (int index = 0; index < smokeEmitter.aliveParticles; index++)
	{
		glColor3f(smokeEmitter.particles[index].r, smokeEmitter.particles[index].g, smokeEmitter.particles[index].b);
		glVertex3f(smokeEmitter.particles[index].xpos, smokeEmitter.particles[index].ypos, smokeEmitter.particles[index].zpos);
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

void graphics_setView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(currentView->eyeX, currentView->eyeY, currentView->eyeZ,
			currentView->centerX, currentView->centerY, currentView->centerZ,
			currentView->upX, currentView->upY, currentView->upZ);
}
