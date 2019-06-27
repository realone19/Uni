#pragma once
#include "Character.h"
#include <windows.h>		// Header file for Windows
#include <iostream>

#include <vector>
#include "Image_Loading/nvImage.h"
class Obstacle
{
private:
	float lenght;
	float width;
	float xPos;
	float yPos;
public:
	Obstacle(int lenght, int width, int xPos, int yPos);
	~Obstacle();
	void display();
	float getXPos();
	float getYPos();
	float getWidth();
	float getLenght();
	GLuint loadPNG(char* name);
	
};

inline float Obstacle::getXPos()
{
	return xPos;
}

inline float Obstacle::getYPos()
{
	return yPos;
}

inline float Obstacle::getWidth()
{
	return width;
}

inline float Obstacle::getLenght()
{
	return lenght;
}