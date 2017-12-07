#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"
#include <math.h>


Object::Object(float x, float y, int type, int fieldWidth, int fieldHeight, int team)
{
	Info.team = team;
	Info.width = fieldWidth;
	Info.height = fieldHeight;
	Info.x = x;
	Info.y = y;
	Info.type = type;
	Info.bullet = 0;
	Info.arrow = 0;
	if (type == BUILDING_OBJECT)
	{
		if (Info.team == ENEMYTEAM)
		{
			Info.r = 1;
			Info.g = 1;
			Info.b = 1;
			Info.a = 1;
		}
		else if (Info.team == MYTEAM)
		{
			Info.r = 1;
			Info.g = 1;
			Info.b = 1;
			Info.a = 1;
		}
		Info.dirX = 0;
		Info.dirY = 0;
		Info.size = 100;
		Info.life = 500;
		Info.lifetime = 100000;
	}
	else if (type == CHARACTER_OBJECT)
	{
		if (Info.team == ENEMYTEAM)
		{
			Info.r = 1;
			Info.g = 0;
			Info.b = 0;
			Info.a = 1;
		}
		else if (Info.team == MYTEAM)
		{
			Info.r = 0;
			Info.g = 0;
			Info.b = 1;
			Info.a = 1;
		}
		float randX, randY = 0;
		randX = rand() % 3 + 1;
		randY = rand() % 3 + 1;
		if (randX == 0)
			Info.dirX = rand() % 100;
		if (randX == 1)
			Info.dirX = rand() % 100;
		if (randX == 2)
			Info.dirX = rand() % 100;

		if (randY == 0)
			Info.dirY = rand() % 100;
		if (randY == 1)
			Info.dirY = rand() % 100;
		if (randY == 2)
			Info.dirY = rand() % 100;

		Info.size = 30;
		Info.life = 100;

		Info.lifetime = 100000;
	}
	else if (type == BULLET_OBJECT)
	{
		if (Info.team == ENEMYTEAM)
		{
			Info.r = 1;
			Info.g = 0;
			Info.b = 0;
			Info.a = 1;
		}
		else if (Info.team == MYTEAM)
		{
			Info.r = 0;
			Info.g = 0;
			Info.b = 1;
			Info.a = 1;
		}
		float randX, randY = 0;
		randX = rand() % 3 + 1;
		randY = rand() % 3 + 1;
		if (randX == 0)
			Info.dirX = rand() % 100;
		if (randX == 1)
			Info.dirX = rand() % 100;
		if (randX == 2)
			Info.dirX = rand() % 100;

		if (randY == 0)
			Info.dirY = rand() % 100;
		if (randY == 1)
			Info.dirY = rand() % 100;
		if (randY == 2)
			Info.dirY = rand() % 100;
		Info.size = 4;
		Info.life = 15;
		Info.lifetime = 100000;
	}
	else if (type == ARROW_OBJECT)
	{
		if (Info.team == ENEMYTEAM)
		{
			Info.r = 0.7;
			Info.g = 0.5;
			Info.b = 0.5;
			Info.a = 1;
		}
		else if (Info.team == MYTEAM)
		{
			Info.r = 1;
			Info.g = 1;
			Info.b = 0;
			Info.a = 1;
		}
		float randX, randY = 0;
		randX = rand() % 3 + 1;
		randY = rand() % 3 + 1;
		if (randX == 0)
			Info.dirX = rand() % 100;
		if (randX == 1)
			Info.dirX = rand() % 100;
		if (randX == 2)
			Info.dirX = rand() % 100;

		if (randY == 0)
			Info.dirY = rand() % 100;
		if (randY == 1)
			Info.dirY = rand() % 100;
		if (randY == 2)
			Info.dirY = rand() % 100;
		Info.size = 4;
		Info.life = 10;
		Info.lifetime = 100000;
	}
}
Object::~Object()
{
}
void Object::Update(float Time)
{
	float elapsedTimeInSecond = Time / 1000;
	Info.bullet += elapsedTimeInSecond;
	Info.arrow += elapsedTimeInSecond;
	Info.x = Info.x + Info.dirX * elapsedTimeInSecond;
	Info.y = Info.y + Info.dirY * elapsedTimeInSecond;


}

