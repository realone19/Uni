#pragma once
#include <windows.h>	
#include <iostream>
#include <vector>
#include "Image_Loading/nvImage.h"
using namespace std;
class Actor
{

protected:
	int	mouse_x, mouse_y;
	bool LeftPressed;
	int screenWidth, screenHeight;
	bool keys[256];
	float spin;
	float speed;
	float lenght;
	float width;
	float xPos;
	float yPos;

public:
	Actor();

	//OPENGL FUNCTION PROTOTYPES
	void display();				//called in winmain to draw everything to the screen
	void update(float dt);				//called in winmain to update variables
	
	bool aabb(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
};

inline bool Actor::aabb(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 < x2 || x2 + w2 < x1)
	{
		
		return false;
	}
	if (y1 + h1 < y2 || y2 + h2 < y1)
	{
		//cout << "y" << endl;
		return false;
	}
	return true;
}