#pragma once
#include "Obstacle.h"
class MovingObstacle
{

private:
	float lenght;
	float width;
	float xPos;
	float yPos;
public:
	MovingObstacle(int lenght, int width, int xPos, int yPos);
	~MovingObstacle();
	void display();
	float getXPos();
	float getYPos();
	float getWidth();
	float getLenght();
	bool fall;
	float vel;
	void xMove(float dt, int min, int max);
	GLuint loadPNG(char* name);
};
inline float MovingObstacle::getXPos()
{
	return xPos;
}

inline float MovingObstacle::getYPos()
{
	return yPos;
}

inline float MovingObstacle::getWidth()
{
	return width;
}

inline float MovingObstacle::getLenght()
{
	return lenght;
}
