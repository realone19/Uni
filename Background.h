#pragma once
#include "Actor.h"
class Background:
	public Actor
{
public:
	Background(int lenght, int width, int xPos, int yPos,char *image);
	~Background();
	void display();
	
	void translate(float x, float y);
	GLuint loadPNG(char* name);
	
};

