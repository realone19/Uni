#pragma once
#include <windows.h>		// Header file for Windows
#include <iostream>

#include <vector>
#include "Image_Loading/nvImage.h"
using namespace std;
class Tokens
{
private:
private:
	float lenght;
	float width;
	float xPos;
	float yPos;
	int tokenID;
	bool taken;
public:
	Tokens(int lenght, int width, int xPos, int yPos,int tokenImg);
	~Tokens();
	void display();
	float getXPos();
	float getYPos();
	float getWidth();
	float getLenght();
	int getTokenID();
	void tokenTaken();
	bool getTaken();
	void resetTaken();
	GLuint token1loadPNG(char* name);
	GLuint token2loadPNG(char* name);
	GLuint token3loadPNG(char* name);
	GLuint token4loadPNG(char* name);
	

};

inline float Tokens::getXPos()
{
	return xPos;
}

inline float Tokens::getYPos()
{
	return yPos;
}

inline float Tokens::getWidth()
{
	return width;
}

inline float Tokens::getLenght()
{
	return lenght;
}

inline int Tokens::getTokenID()
{
	return tokenID;
}

inline void Tokens::tokenTaken()
{
	taken = true;
}

inline bool Tokens::getTaken()
{
	return taken;
}

inline void Tokens::resetTaken()
{
	taken = false;
}