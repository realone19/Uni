#include "MovingObstacle.h"
#include "Obstacle.h"

GLuint movingObstacleTextureID;

MovingObstacle::MovingObstacle(int lenght, int width, int xPos, int yPos)
{
	this->lenght = lenght;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
	vel = 0.1;
	fall = false;
	loadPNG("car.png");
}


MovingObstacle::~MovingObstacle()
{
}


void MovingObstacle::display()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, movingObstacleTextureID);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

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



GLuint MovingObstacle::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &movingObstacleTextureID);
		glBindTexture(GL_TEXTURE_2D, movingObstacleTextureID);
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

	return movingObstacleTextureID;
}


void MovingObstacle::xMove(float dt,int min , int max)
{
	if (xPos >= max)
	{
		//loadPNG("car.png");
		fall = true;
	}
	if (!fall)
	{
		
		xPos += vel * dt;

	}
	if (fall)
	{
		
		xPos -= vel * dt;

	}
	if (xPos <= min)
	{
		//loadPNG("car2.png");
		fall = false;
	}
}