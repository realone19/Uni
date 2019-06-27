#include "MovingPlatform.h"


GLuint movingPlatformTextureID;
MovingPlatform::MovingPlatform(int lenght, int width, float xPos, float yPos)
{
	this->lenght = lenght;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
	//this->dir = dir;
	yVel = 0.1;
	fall = false;
	xFall = false;
	loadPNG("platform.png");
}


MovingPlatform::~MovingPlatform()
{
}


void MovingPlatform::display()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, movingPlatformTextureID);
	glPushMatrix();
	glTranslatef(xPos, yPos, 0);
	glBegin(GL_QUADS);
	//glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);  glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0); glVertex2f(0, 0 + lenght);
	glTexCoord2f(1.0, 1.0); glVertex2f(0 + width, 0 + lenght);
	glTexCoord2f(1.0, 0.0); glVertex2f(0 + width, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}



GLuint MovingPlatform::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &movingPlatformTextureID);
		glBindTexture(GL_TEXTURE_2D, movingPlatformTextureID);
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

	return movingPlatformTextureID;
}

void MovingPlatform::yMove(float dt,int min,int max)
{
	xFall = false;
	if (yPos >= max) fall = true;
	if(!fall)
	{
		yPos += yVel *dt;
		
	}
	 if (fall)  yPos -= yVel *dt;
	 
	 if (yPos <=min) fall = false;

}

void MovingPlatform::xMove(float dt)
{
	xFall = true;
	if (xPos >= 1000) fall = true;
	if (!fall)
	{
		xPos += yVel* dt;

	}
	if (fall)  xPos -= yVel * dt;

	if (xPos <= 700) fall = false;

}