#include "Actor.h"
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>	

using namespace std;

Actor::Actor()
{
	

}

void Actor::display()
{
	/*glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(xPos,yPos,0);
		glBegin(GL_POLYGON);
			glVertex2f(-50, 50);
			glVertex2f(50, 50);
			glVertex2f(50, -50);
			glVertex2f(-50, -50);
		glEnd();

	glPopMatrix();

	glFlush();*/
}

void Actor::update(float dt)
{
}


