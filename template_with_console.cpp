
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

#include <windows.h>		// Header file for Windows
#include <iostream>
#include "Actor.h"
#include "Character.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "Background.h"
#include "Obstacle.h"
#include "MovingObstacle.h"
#include "Tokens.h"
#include "health.h"
#include "Image_Loading/nvImage.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <chrono>
#include "GL\freeglut.h"

std::chrono::milliseconds oldTime;
GLuint menuTexture;
GLuint loseTexture;
GLuint winTexture;

int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 800, screenHeight = 500;
bool keys[256];
bool start = false;
float spin = 0;
float speed = 0;
float cameraX = 0.0f;
float cameraY = 0.0f;
bool lose = false;
bool jumping = false;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys(float dt);         //called in winmain to process keyboard input
void menu();			
void loseScreen();
void winScreen();
GLuint loadMenuPNG(char* name);
GLuint loadWinPNG(char* name);
GLuint loadLosePNG(char* name);

/*************    START OF OPENGL FUNCTIONS   ****************/
Character* a1;
vector<Platform*> platforms;
vector<Obstacle*> obstacles;
vector<MovingPlatform*> movingPlatforms;
vector<Tokens*> tokens;
vector<health*> healths;
vector< MovingObstacle*> movingObstacles;


Platform* p1;
Platform* p2;
Background* background;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);						//sets the clear colour to yellow
															//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
	
	oldTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	a1 = new Character();
	background = new Background(1000,3200,-1100, -240, "city.png");

	healths.push_back(new health(30, 30, a1->getX() - 350, a1->getY()+400, 0));
	healths.push_back(new health(30, 30, a1->getX() - 300, a1->getY() + 400, 0));
	healths.push_back(new health(30, 30, a1->getX() - 250, a1->getY() + 400, 0));
	healths.push_back(new health(30, 30, a1->getX() - 200, a1->getY() + 400, 1));
	healths.push_back(new health(30, 30, a1->getX() - 150, a1->getY() + 400, 2));
	healths.push_back(new health(30, 30, a1->getX() - 100, a1->getY() + 400, 3));
	healths.push_back(new health(30, 30, a1->getX() - 50, a1->getY() + 400, 3));
	
	
	platforms.push_back(new Platform(50, 200, -50, -200));
	platforms.push_back(new Platform(50, 300, 300, -40));
	platforms.push_back(new Platform(50, 300, 800, -200));
	platforms.push_back(new Platform(50, 250,-500 , 150));
	platforms.push_back(new Platform(50, 200, -1100, -200));
	platforms.push_back(new Platform(50, 200, 1350, 150));
	platforms.push_back(new Platform(50, 200, 1800, 490));


	movingPlatforms.push_back(new MovingPlatform(50, 200, -850, -50));
	movingPlatforms.push_back(new MovingPlatform(50, 250, 700, 60));
	movingPlatforms.push_back(new MovingPlatform(50, 150, 1600, 150));

	obstacles.push_back(new Obstacle(50, 50, -350, -200));

	movingObstacles.push_back(new MovingObstacle(80, 250, 1150, -200));


	tokens.push_back(new Tokens(50, 50, -400, 203,1));
	tokens.push_back(new Tokens(50, 50, 1900, -200,2));
	tokens.push_back(new Tokens(50, 50, 1900,550, 3));
	tokens.push_back(new Tokens(40, 40, -450, -190, 4));
	tokens.push_back(new Tokens(40, 40, -700, -180, 4));
	tokens.push_back(new Tokens(40, 40, -870, -180, 4));
	tokens.push_back(new Tokens(40, 40, -350, -90, 4));
	tokens.push_back(new Tokens(40, 40, -200, -180, 4));
	tokens.push_back(new Tokens(40, 40, 20, -130, 4));
	tokens.push_back(new Tokens(40, 40, 350, 30, 4));
	tokens.push_back(new Tokens(40, 40, 500, 30, 4));
	tokens.push_back(new Tokens(40, 40, 350, 30, 4));
	tokens.push_back(new Tokens(40, 40, 800, 130, 4));
	tokens.push_back(new Tokens(40, 40, 1100, 130, 4));
	tokens.push_back(new Tokens(40, 40, 1430, 220, 4));
	tokens.push_back(new Tokens(40, 40, 1800, 350, 4));
	tokens.push_back(new Tokens(40, 40, 1850, 250, 4));
	tokens.push_back(new Tokens(40, 40, 1900, 150, 4));
	tokens.push_back(new Tokens(40, 40, 1900, 50, 4));
	tokens.push_back(new Tokens(40, 40, 1900, -50, 4));
	tokens.push_back(new Tokens(40, 40, 1900, -150, 4));
	tokens.push_back(new Tokens(40, 40, 1430, 50, 4));
	loadMenuPNG("menu.png");
	loadWinPNG("winscreen.png");
	loadLosePNG("lose.png");

	healths[6]->BuildFont();
	

}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
														  // we will use these values to set the coordinate system

	glViewport(0, 0, width, height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D((-1*(screenWidth/2)),(screenWidth/2), (-1 * (screenHeight / 2)),(screenHeight/2));           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void display()
{
	
	
	
	std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	float dt = (currentTime - oldTime).count();
	oldTime = currentTime;
	if (!lose)
	{
		menu();
	}
	
	

	if (start== true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processKeys(dt);			//process keyboard

		a1->update(dt / 1000.0f);
		a1->characterOnGround();
		a1->walls();
		//a1->autoMoving(dt);

		if (a1->getX() >= -700 && a1->getX() <= 1600)
		{
			cameraX = a1->getX();
		}

		if (a1->getY() > 5)
		{
			cameraY = a1->getY();
		}



		glPushMatrix();
		glTranslatef(-cameraX, -cameraY, 0.0f);
		background->display();


		a1->display();





		for (Platform *platform : platforms)
		{
			platform->display();
			a1->platformCollision(*platform);
		}

		for (MovingPlatform *platform : movingPlatforms)
		{
			platform->display();

			a1->movingPlatformCollision(*platform, dt);
		}
		movingPlatforms.at(0)->yMove(dt, -50, 150);
		movingPlatforms.at(1)->xMove(dt);
		movingPlatforms.at(2)->yMove(dt, 150, 300);


		for (int i = 0; i < obstacles.size(); i++)
		{
			obstacles[i]->display();
			a1->obstacleCollision(*obstacles.at(i));
			if (a1->getHit())
			{
				a1->resetHit();
				a1->changeXPos(-600);
				a1->changeYPos(-200);

				a1->loseHealth();
			}
		}

		for (MovingObstacle *obstacle : movingObstacles)
		{
			obstacle->display();
			obstacle->xMove(dt, 1150, 1600);
			a1->MovingObstacleCollision(*obstacle);
			if (a1->getHit())
			{
				a1->resetHit();
				a1->changeXPos(-600);
				a1->changeYPos(-200);

				a1->loseHealth();
			}
		}

		for (int i = 0; i < tokens.size(); i++)
		{
			if (!a1->getMoveBoost())
			{
				tokens[0]->display();
			}

			if (!a1->getJumpBoost())
			{
				tokens[1]->display();
			}

			tokens[2]->display();
			if (a1->tokenCollision(*tokens.at(0)))
			{
				a1->activateBoost();
			}
			if (a1->tokenCollision(*tokens.at(1)))
			{
				a1->activateJumpBoost();
			}

			if (a1->tokenCollision(*tokens.at(2)))
			{
				a1->activateWin();
			}

			if (tokens[i]->getTokenID() == 4 && !tokens[i]->getTaken())
			{
				tokens[i]->display();

			}
			if (tokens[i]->getTokenID() == 4 && a1->tokenCollision(*tokens.at(i)))
			{
				tokens[i]->tokenTaken();

			}

		}

		if (a1->getHealth() == 3)
		{
			healths[0]->translate(cameraX - 350, cameraY + 200);
			healths[0]->display();

			healths[1]->translate(cameraX - 300, cameraY + 200);
			healths[1]->display();

			healths[2]->translate(cameraX - 250, cameraY + 200);
			healths[2]->display();
		}
		else if (a1->getHealth() == 2)
		{
			healths[0]->translate(cameraX - 350, cameraY + 200);
			healths[0]->display();

			healths[1]->translate(cameraX - 300, cameraY + 200);
			healths[1]->display();
		}
		else if (a1->getHealth() == 1)
		{
			healths[0]->translate(cameraX - 350, cameraY + 200);
			healths[0]->display();
		}

		if (a1->getJumpBoost())
		{
			healths[3]->translate(cameraX - 200, cameraY + 200);
			healths[3]->display();
		}

		if (a1->getMoveBoost())
		{
			healths[4]->translate(cameraX - 150, cameraY + 200);
			healths[4]->display();
		}

		healths[5]->translate(cameraX - 100, cameraY + 200);
		healths[5]->display();

		healths[6]->translate(cameraX - 50, cameraY + 200);
		healths[6]->getScore(a1->getScore());
		healths[6]->displayText();

		a1->lose();
		
		if (a1->getWin())
		{
			a1->changeXPos(-620);
			//a1->changeYPos(-200);
		}

		glPopMatrix();
	}
	loseScreen();
	winScreen();
	
}

void processKeys(float dt)
{
	if (keys[VK_UP])
	{
		a1->jump();
	}
	if (keys[VK_DOWN])
	{
		//a1->downButton();
	}
	if (keys[VK_LEFT])
	{
		a1->leftButton(dt);
	}
	if (keys[VK_RIGHT])
	{
		a1->rightButton(dt);
	}
	
	
}
void menu()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menuTexture);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(-400, -250, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0);   glVertex2f(0, 0 + 500);
	glTexCoord2f(1.0, 1.0);  glVertex2f(0 + 800, 0 + 500);
	glTexCoord2f(1.0, 0.0); glVertex2f(0 + 800, 0);

	//glTexCoord2f(0.0, 0.0); glVertex2f(xPosi, yPosi);
	//glTexCoord2f(0.0, 1.0);   glVertex2f(xPosi, yPosi + lenght);
	//glTexCoord2f(1.0, 1.0);  glVertex2f(xPosi + width, yPosi + lenght);
	//glTexCoord2f(1.0, 0.0); glVertex2f(xPosi + width, yPosi);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	a1->deactivateLose();
	if (keys[VK_RETURN])
	{
		start = true;
	}
}

GLuint loadMenuPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &menuTexture);
		glBindTexture(GL_TEXTURE_2D, menuTexture);
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

	return menuTexture;
}


void loseScreen()
{
	
	if (a1->getLoseGame())
	{
		lose = true;
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, loseTexture);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glPushMatrix();
		glTranslatef(-400, -250, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
		glTexCoord2f(0.0, 1.0);   glVertex2f(0, 0 + 500);
		glTexCoord2f(1.0, 1.0);  glVertex2f(0 + 800, 0 + 500);
		glTexCoord2f(1.0, 0.0); glVertex2f(0 +800, 0);

		//glTexCoord2f(0.0, 0.0); glVertex2f(xPosi, yPosi);
		//glTexCoord2f(0.0, 1.0);   glVertex2f(xPosi, yPosi + lenght);
		//glTexCoord2f(1.0, 1.0);  glVertex2f(xPosi + width, yPosi + lenght);
		//glTexCoord2f(1.0, 0.0); glVertex2f(xPosi + width, yPosi);
		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);

		
		start = false;
		a1->resetHealth();
		a1->deactivateBoost();
		for (Tokens *token : tokens)
		{
			token->resetTaken();
		}
		a1->resetScore();
		
		if (keys[VK_RETURN])
		{
			lose = false;
		}
	}

}
GLuint loadLosePNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &loseTexture);
		glBindTexture(GL_TEXTURE_2D, loseTexture);
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

	return loseTexture;
}


void winScreen()
{

	if (a1->getWin())
	{
		lose = true;
		//
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, winTexture);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glPushMatrix();
		glTranslatef(-400, -250, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
		glTexCoord2f(0.0, 1.0);   glVertex2f(0, 0 + 500);
		glTexCoord2f(1.0, 1.0);  glVertex2f(0 + 800, 0 + 500);
		glTexCoord2f(1.0, 0.0); glVertex2f(0 + 800, 0);

		//glTexCoord2f(0.0, 0.0); glVertex2f(xPosi, yPosi);
		//glTexCoord2f(0.0, 1.0);   glVertex2f(xPosi, yPosi + lenght);
		//glTexCoord2f(1.0, 1.0);  glVertex2f(xPosi + width, yPosi + lenght);
		//glTexCoord2f(1.0, 0.0); glVertex2f(xPosi + width, yPosi);
		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);


		start = false;
		a1->resetHealth();
		a1->deactivateBoost();
		for (Tokens *token : tokens)
		{
			token->resetTaken();
		}
		a1->resetScore();

		if (keys[VK_RETURN])
		{
			//start = true;
			a1->deactivateWin();
			
			lose = false;
		}
	}

}

GLuint loadWinPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &winTexture);
		glBindTexture(GL_TEXTURE_2D, winTexture);
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

	return winTexture;
}


/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool done = false;		        				// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	
	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;
			
			display();					// Draw The Scene
			//update();					// update variables
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	 wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								250, 100,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();
	
	return true;									// Success
}



