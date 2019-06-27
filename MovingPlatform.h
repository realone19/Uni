#pragma once
#include "Platform.h"
#include <windows.h>		// Header file for Windows
#include <iostream>
#include "Actor.h"
#include <vector>
#include "Image_Loading/nvImage.h"

class MovingPlatform:
	public Platform
{
private:
	float yVel;
	bool fall;
	bool xFall;
	char dir;
public:
	MovingPlatform(int lenght, int width, float xPos, float yPos);
	~MovingPlatform();
	void display();
	void yMove(float dt, int min, int max);
	void xMove(float dt);
	char getDir();
	bool getFall();
	bool getXFall();
	GLuint loadPNG(char* name);
};

inline char MovingPlatform::getDir()
{
	return dir;
}

inline bool MovingPlatform::getFall()
{
	return fall;
}

inline bool MovingPlatform::getXFall()
{
	return xFall;
}