#include "emitter.h"
#include "view.h"

#include <GL/glut.h>

void graphics_init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Particle system");
	glutFullScreen();
	glutDisplayFunc(particles_display);

	// Render points as circles and make them span a few pixels instead of one
	glEnable(GL_POINT_SMOOTH);
	glPointSize(POINT_SIZE);

	/*--------------------------------------------------------------------------
	 * Setup for the smoke rendering method using textures
	 *-------------------------------------------------------------------------*/

	// Make points very large (in pixel terms), set the blending funcion
	glPointSize(POINT_SIZE_TEXTURE);
	// Render antialiased points and lines in arbitrary order, pixel aithmetic
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//  Specify the drawing mode for point sprites
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Enable point sprites and 2D textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE);
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

void graphics_clear(void)
{
	//TODO
}

void set_view(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(current_view.position.x, current_view.position.y, current_view.position.z,
			  current_view.center.x, current_view.center.y, current_view.center.z,
			  current_view.direction.x, current_view.direction.y, current_view.direction.z);
}
