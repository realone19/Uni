#pragma once
#include "Actor.h"
#include "GL\freeglut.h"
#include <iostream>
#include <windows.h>		// Header File For Windows
#include <string>			// used for strings
#include <sstream>			// used for streaming text
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

using namespace std;
class health:
	public Actor
{
private:
	int imgID;
	int score;
public:
	health(int lenght, int width, int xPos, int yPos, int imgID);
	~health();
	void display();
	void dis();
	void getScore(int score);
	void translate(float x, float y);
	GLuint loadPNG(char* name);
	GLuint token1loadPNG(char* name);
	GLuint token2loadPNG(char* name);
	GLuint token3loadPNG(char* name);
	void renderText(float x, float y, void *font, string text);
	
	GLvoid glPrint(string fmt);
	int displayText(GLvoid);
	GLvoid BuildFont(GLvoid);
};

inline void health::getScore(int score) {
	this->score = score;
}