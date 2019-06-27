#include "Character.h"
//#include <windows.h>		// Header file for Windows
#include <iostream>
#include "GL\freeglut.h"
#include <vector>
#include "Image_Loading/nvImage.h"

using namespace std;

GLuint textureID;

Character::Character()
{
	xPos = -600;
	yPos = -200;
	lenght =100;
	width = 110;
	yVel = 0;
	xVel = 0;
	score = 0;
	isJumping = false;
	isMoving = true;
	colliding = false;
	moveBoost = false;
	jumpBoost = false;
	hit = false;
	health = 3;
	win = false;
	loseGame = false;
	loadPNG("character.png");
}


Character::~Character()
{

}

void Character::leftButton(float dt)
{
	if (isJumping)
	{
		loadPNG("character3.png");
	}
	else
	{
		loadPNG("character1.png");
	}
	if (moveBoost)
	{
		xVel = 0.3;
	}
	else
	{
		xVel = 0.2;
	}

	
	xPos -= xVel * dt;
}

void Character::rightButton(float dt)
{
	if (isJumping)
	{
		loadPNG("character2.png");
	}
	else
	{
		loadPNG("character.png");
	}
	
	if (moveBoost)
	{
		xVel = 0.3;
	}
	else
	{
		xVel = 0.2;
	}
	xPos += xVel * dt;

	
}
	
	


void Character::jump()
{
	if (!isJumping) {
		loadPNG("character2.png");
		if (jumpBoost)
		{
			yVel = 500.0f;
		}
		else
		{
			yVel = 400.0f;
		}
		isJumping = true;
	}
	
	

}



void Character::update(float dt)
{
	if (colliding)
	{
		yVel = 0;
		yPos += yVel * dt;

	}
	else
	{
		if (jumpBoost)
		{
			yVel -= 600.0f * dt;
		}
		else
		{
			yVel -= 500.0f * dt;
		}
		
		yPos += yVel * dt;
	}
	

	
}

bool Character::characterOnGround()
{
	/*if (colliding)
	{
		yVel = 0.0f;
		return true;
	}*/

	if (yPos <= -200)// && !colliding)
	{
		yPos = -200;
		yVel = 0.0f;
		isJumping = false;
		return true;
	}
	else
	{
		return false;
	}

}

bool Character::highestPos()
{
	if (yPos > 200)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Character::platformCollision(Platform platforms)
{
	if (aabb(xPos, yPos, width, lenght, platforms.getXPos(), platforms.getYPos(), platforms.getWidth(), platforms.getLenght()) == true)
	{

			if (yPos > (platforms.getYPos() + platforms.getLenght() - 10))
			{
				yPos = (platforms.getYPos() + platforms.getLenght());
				yVel = 0;
				isJumping = false;
			}
			else if ((yPos+lenght)<(platforms.getYPos() + 10 ))
			{
				yVel = 0;
				yPos = platforms.getYPos() - lenght-1;

			}
			else
			{
				if (xPos < platforms.getXPos())
				{
					xVel = 0;
					xPos = (platforms.getXPos() - width);
				}
				if (xPos > platforms.getXPos())
				{
					xVel = 0;
					xPos = platforms.getXPos() + platforms.getWidth();
				}
			}

	}
}


void Character::movingPlatformCollision(MovingPlatform platforms, float dt)
{
	if (aabb(xPos, yPos, width, lenght, platforms.getXPos(), platforms.getYPos(), platforms.getWidth(), platforms.getLenght()) == true)
	{

		if (yPos > (platforms.getYPos() + platforms.getLenght() - 10))
		{
			yPos = (platforms.getYPos() + platforms.getLenght());
			
			
			if (platforms.getFall() && platforms.getXFall() )
			{
				
				xPos -= 0.1 * dt;
			}
			else if(!platforms.getFall() && platforms.getXFall())
			{
				xPos += 0.1 * dt;
			}
			else if (platforms.getFall() && !platforms.getXFall())
			{
				yPos -= 0.1 * dt;
			}
			else if (!platforms.getFall() && !platforms.getXFall())
			{
				yPos += 0.1 * dt;
			}
			
			yVel = 0;
			isJumping = false;
		}
		else if ((yPos + lenght) < (platforms.getYPos() + 10))
		{
			yVel = 0;
			yPos = platforms.getYPos() - lenght - 15;

		}
		else
		{
			if (xPos < platforms.getXPos())
			{
				xVel = 0;
				xPos = (platforms.getXPos() - width -1);
			}
			if (xPos > platforms.getXPos())
			{
				xVel = 0;
				xPos = platforms.getXPos() + platforms.getWidth()+1 ;
			}
		}

	}

}

void Character::obstacleCollision(Obstacle obstacles)
{
	if (aabb(xPos, yPos, width, lenght, obstacles.getXPos(), obstacles.getYPos(), obstacles.getWidth(), obstacles.getLenght()) == true)
	{

		hit = true;
	}
}

void Character::MovingObstacleCollision(MovingObstacle obstacles)
{
	if (aabb(xPos, yPos, width, lenght, obstacles.getXPos(), obstacles.getYPos(), obstacles.getWidth(), obstacles.getLenght()) == true)
	{

		hit = true;
	}
}

bool Character::tokenCollision(Tokens tokens)
{
	//cout << score << endl;
	if (aabb(xPos, yPos, width, lenght, tokens.getXPos(), tokens.getYPos(), tokens.getWidth(), tokens.getLenght()) == true)
	{
		if (!tokens.getTaken() && tokens.getTokenID() == 4)
		{
			score += 100;
		}
		return true;
	}
	
	return false;
}



void Character::walls()
{
	if (xPos < -1100)
	{
		xVel = 0;
		xPos = -1100;

	}

	if (xPos > 1900)
	{
		xVel = 0;
		xPos = 1900;
	}
}

void Character::lose()
{
	if (health == 0)
	{
		loseGame = true;
	}
	
}

// This stores a handle to the texture


GLuint Character::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
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

	return textureID;
}

void Character::display()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(xPos, yPos, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0);   glVertex2f(0, 0 + lenght);
	glTexCoord2f(1.0, 1.0);  glVertex2f(0 + width, 0 + lenght);
	glTexCoord2f(1.0, 0.0); glVertex2f(0 + width, 0);

	//glTexCoord2f(0.0, 0.0); glVertex2f(xPosi, yPosi);
	//glTexCoord2f(0.0, 1.0);   glVertex2f(xPosi, yPosi + lenght);
	//glTexCoord2f(1.0, 1.0);  glVertex2f(xPosi + width, yPosi + lenght);
	//glTexCoord2f(1.0, 0.0); glVertex2f(xPosi + width, yPosi);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


