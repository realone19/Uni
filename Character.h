 #pragma once
#include "Actor.h"
#include <vector>
#include "Platform.h"
#include "MovingPlatform.h"
#include "Obstacle.h"
#include "MovingObstacle.h"
#include "Tokens.h"
#include "Image_Loading/nvImage.h"
using namespace std;
class Character :
	public Actor
{

private:
	int lenght;
	int width;
	int xPosi;
	int yPosi;
	bool colliding;
	float yVel;
	float xVel;
	bool isJumping;
	bool isMoving;
	float platformxPos;
	float platformyPos;
	float platformLength;
	float platformWidth;
	bool moveBoost;
	bool jumpBoost;
	int health;
	bool hit;
	bool win;
	bool loseGame;
	int score;
	
public:
	Character();
	~Character();
	void obstacleCollision(Obstacle obstacles);
	void MovingObstacleCollision(MovingObstacle  obstacles);
	void leftButton(float dt);
	void rightButton(float dt);
	void jump();
	void display();
	void update(float dt);
	GLuint loadPNG(char* name);
	bool characterOnGround();
	bool highestPos();
	void platformCollision(Platform platforms);
	void movingPlatformCollision(MovingPlatform platforms, float dt);
	void walls();
	void lose();
	bool getWin();
	void resetHealth();
	void deactivateBoost();
	void resetScore();
	int getScore();
	
	bool tokenCollision(Tokens tokens);
	void activateBoost();
	void activateJumpBoost();
	void activateWin();
	void deactivateWin();

	inline bool getLoseGame()
	{
		return loseGame;
	}
	inline float getX() {
		return xPos;
	}

	inline float getY() {
		return yPos;
	}

	inline bool getMoveBoost()
	{
		return moveBoost;
	}

	inline bool getJumpBoost()
	{
		return jumpBoost;
	}

	inline void changeXPos(float x)
	{
		xPos = x;
	}

	inline void changeYPos(float y)
	{
		yPos = y;
	}

	inline int getHealth()
	{
		return health;
	}

	inline bool getHit()
	{
		return hit;
	}
	inline void resetHit()
	{
		hit = false;
	}
	inline void loseHealth()
	{
		health -= 1;
	}

	inline void deactivateLose()
	{
		loseGame = false;
	}
};

inline void Character::activateBoost()
{
	moveBoost = true;
}

inline void Character::activateJumpBoost()
{
	jumpBoost = true;
}

inline bool Character::getWin()
{
	return win;
}

inline void Character::activateWin()
{
	
	
	win = true;
}
inline void Character::deactivateWin()
{
	/*yPos = -200;
	xPos = -600;*/
	win = false;
}

inline void Character::resetHealth()
{
	health = 3;
}

inline void Character::deactivateBoost()
{
	moveBoost = false;
	jumpBoost = false;
}

inline void Character::resetScore()
{
	score = 0;
}
inline int Character::getScore()
{
	return score;
}