#include "Tokens.h"
#include "GL\freeglut.h"
#include <iostream>

GLuint token1TextureID;
GLuint token2TextureID;
GLuint token3TextureID;
GLuint token4TextureID;

Tokens::Tokens(int lenght, int width, int xPos, int yPos,int tokenImg)
{
	this->lenght = lenght;
	this->width = width;
	this->xPos = xPos;
	this->yPos = yPos;
	this->tokenID = tokenImg;
	taken = false;
	if (tokenImg == 1)
	{
		token1loadPNG("wheels.png");
	}
	else if (tokenImg == 2)
	{
		token2loadPNG("shoe.png");
	}
	else if (tokenImg == 3)
	{
		token3loadPNG("win.png");
	}
	else if (tokenImg == 4)
	{
		token4loadPNG("coin.png");
	}
}


Tokens::~Tokens()
{
}

void Tokens::display()
{

	glEnable(GL_TEXTURE_2D);
	if (tokenID == 1)
	{
		glBindTexture(GL_TEXTURE_2D, token1TextureID);
	}
	else if (tokenID == 2)
	{
		glBindTexture(GL_TEXTURE_2D, token2TextureID);
	}
	else if (tokenID == 3)
	{
		glBindTexture(GL_TEXTURE_2D, token3TextureID);
	}
	else if (tokenID == 4)
	{
		glBindTexture(GL_TEXTURE_2D, token4TextureID);
	}
	

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



GLuint Tokens::token1loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token1TextureID);
		glBindTexture(GL_TEXTURE_2D, token1TextureID);
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

	return token1TextureID;
}


GLuint Tokens::token2loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token2TextureID);
		glBindTexture(GL_TEXTURE_2D, token2TextureID);
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

	return token2TextureID;
}


GLuint Tokens::token3loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token3TextureID);
		glBindTexture(GL_TEXTURE_2D, token3TextureID);
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

	return token3TextureID;
}


GLuint Tokens::token4loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token4TextureID);
		glBindTexture(GL_TEXTURE_2D, token4TextureID);
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

	return token4TextureID;
}


