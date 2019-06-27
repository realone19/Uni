#pragma once
#include "Actor.h"
#include <vector>
#include "Image_Loading/nvImage.h"
using namespace std;
class Platform:
	public Actor
{


protected:
	float lenght;
	float width;
	float xPos;
	float yPos;
public:
	Platform();
	~Platform();
	Platform(int lenght, int width, int xPos, int yPos);
	void display();
	float getXPos();
	float getYPos();
	float getWidth();
	float getLenght();
	GLuint loadPNG(char* name);

};

inline float Platform::getXPos()
{
	return xPos;
}

inline float Platform::getYPos()
{
	return yPos;
}

inline float Platform::getWidth()
{
	return width;
}

inline float Platform::getLenght()
{
	return lenght;
}