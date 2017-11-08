#include"stdafx.h"
#include "Object.h"

Object::Object()
{
}
Object::~Object()
{
}

Object::Object(float x, float y, OBJECT_TYPE type)
{
	if (OBJECT_BUILDING==type)
	{
		Info.size = 80;
		Info.Life = 50;
		Info.LifeTime = 10000;
	}
	if (OBJECT_ARROW==type)
	{	
	}
	if (OBJECT_CHARACTER==type)
	{
		Info.size = 10;
		Info.Life = 100;
		Info.LifeTime = 100000;
		int randX = rand() % 2;
		int randY = rand() % 2;
		if (randX == 0)
			Info.dirX = 50 + rand() % 10;
		if (randX == 1)
			Info.dirX = -(50 + rand() % 10);
		if (randY == 0)
			Info.dirY = 50 + rand() % 10;
		if (randY == 1)
			Info.dirY = -(50 + rand() % 10);
	}
	if (OBJECT_BULLET==type)
	{
		Info.size = 2;
		Info.r = 1;
		Info.g = 0;
		Info.b = 3;
		int randX = rand() % 3;
		int randY = rand() % 3;
		if (randX == 0)
			Info.dirX = 10 + rand() % 10;
		if (randX == 1)
			Info.dirX = -(10 + rand() % 10);

		if (randY == 0)
			Info.dirY = 10 + rand() % 10;
		if (randY == 1)
			Info.dirY = -(10 + rand() % 10);
		Info.Life = 100;
		Info.LifeTime = 100000;
	}
	Info.x = x;
	Info.y = y;	
}

void Object::Update(float fTime)
{
	float Time = fTime / 50.f;	
	Info.x =Info.x + Info.dirX * Time;
	Info.y = Info.y + Info.dirY * Time;

	if (240 <= Info.x)
		Info.dirX *= -1;
	if (-240 >= Info.x)
		Info.dirX *= -1;
	if (-240 >= Info.y)
		Info.dirY *= -1;
	if (240 <= Info.y)
		Info.dirY *= -1;	
}

