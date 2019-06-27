#include "health.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library


//#include "glfont2.h"
//using namespace glfont;
//
//GLFont myfont;

extern HDC			hDC;		// Private GDI Device Context
//HGLRC		hRC = NULL;		// Permanent Rendering Context
//HWND		hWnd = NULL;		// Holds Our Window Handle
//HINSTANCE	hInstance;		// Holds The Instance Of The Application
GLuint	base;
health::health(int lenght, int width, int xPos, int yPos, int imgID)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->lenght = lenght;
	this->imgID = imgID;
	//BuildFont();
				
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	////Create our glFont from Arial.glf, using texture 1
	//if (!myfont.Create("glfont.glf", 1))
	//	exit(0);
	if (imgID == 0)
	{
		loadPNG("heart.png");
	}
	else if (imgID == 1)
	{
		token1loadPNG("shoe.png");
	}
	else if (imgID == 2)
	{
		token2loadPNG("wheels.png");
	}
	else if (imgID == 3)
	{
		token3loadPNG("coin.png");
	}
}


GLuint token1ID;
GLuint token2ID;
GLuint token3ID;
GLuint healthTextureID;

health::~health()
{
}

void health::display() {
	glEnable(GL_TEXTURE_2D);
	if (imgID == 0)
	{
		glBindTexture(GL_TEXTURE_2D, healthTextureID);
	}
	else if (imgID == 1)
	{
		glBindTexture(GL_TEXTURE_2D, token1ID);
	}
	else if (imgID == 2)
	{
		glBindTexture(GL_TEXTURE_2D, token2ID);
	}
	else if (imgID == 3)
	{
		glBindTexture(GL_TEXTURE_2D, token3ID);
	}
	
	//glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(xPos, yPos, 0);
	glBegin(GL_QUADS);
	//glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);  glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0); glVertex2f(0, 0 + lenght);
	glTexCoord2f(1.0, 1.0); glVertex2f(0 + width, 0 + lenght);
	glTexCoord2f(1.0, 0.0); glVertex2f(0 + width, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}


GLuint health::loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &healthTextureID);
		glBindTexture(GL_TEXTURE_2D, healthTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return healthTextureID;
}


GLuint health::token1loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token1ID);
		glBindTexture(GL_TEXTURE_2D, token1ID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return token1ID;
}

GLuint health::token2loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token2ID);
		glBindTexture(GL_TEXTURE_2D, token2ID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return token2ID;
}

GLuint health::token3loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &token3ID);
		glBindTexture(GL_TEXTURE_2D, token3ID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return token3ID;
}

void health::translate(float x, float y)
{
	//if ( x > -1050 && x<1250)
	{
		xPos = x;
	}
	//else
	{

	}
	
	//if (y > 405)
	{
		yPos = y; //-200;
	}
	
}

void health::renderText(float x, float y, void *font, string text)
{

	glRasterPos2i(x, y);
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		glutBitmapCharacter(font, *c);
	}

}

//void health::displayText()
//{
//	glPushAttrib(GL_CURRENT_BIT);
//	glColor3f(0, 0, 0);
//	char buffer[50] = { 0 };
//	sprintf_s(buffer, "fuck off");
//	renderText(xPos, yPos, GLUT_BITMAP_HELVETICA_18, buffer);
//	glPopAttrib();
//}


GLvoid health::BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(-30,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_NORMAL,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Times New Roman");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}


int health::displayText(GLvoid)									// Here's Where We Do All The Drawing
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glColor3f(1.0f, 1.0f, 1.0f);

	// Position The Text On The Screen
	//glRasterPos2f(xPos, yPos);

	glRasterPos2f(-50,205);

	glPrint("");	// Print GL Text To The Screen
	 
	


	

	return TRUE;										// Everything Went OK
}

GLvoid health::glPrint(string fmt)					// Custom GL "Print" Routine
{
	stringstream stream;
	stream << fmt << " " << score;

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
														// first 32 chars not used
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

//void health::dis()
//{
//	myfont.Begin();
//
//	glPushMatrix();
//	glRotatef(5, 0, 0, 1);
//
//	myfont.DrawString("Hello World!", 1.0f, 60.0f, 440.0f);
//	glPopMatrix();
//}