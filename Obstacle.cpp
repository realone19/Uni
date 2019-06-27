#include "Obstacle.h"
#include <windows.h>		// Header file for Windows

GLuint obstacleTextureID;
Obstacle::Obstacle(int lenght, int width, int xPos, int yPos)
{
	this->lenght = lenght;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
	loadPNG("cone.png");
}


Obstacle::~Obstacle()
{
}

void Obstacle::display()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, obstacleTextureID);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glPushMatrix();

	glBegin(GL_QUADS);
	//glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);  glVertex2f(xPos, yPos);
	glTexCoord2f(0.0, 1.0); glVertex2f(xPos, yPos + lenght);
	glTexCoord2f(1.0, 1.0); glVertex2f(xPos + width, yPos + lenght);
	glTexCoord2f(1.0, 0.0); glVertex2f(xPos + width, yPos);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}



GLuint Obstacle::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &obstacleTextureID);
		glBindTexture(GL_TEXTURE_2D, obstacleTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return obstacleTextureID;
}