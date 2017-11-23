#include"stdafx.h"
#include "Object.h"

Object::Object()
{
}
Object::~Object()
{
}
Object::Object(float x, float y, OBJECT_TYPE type, TEAM team)
{
	if (OBJECT_BUILDING == type)
	{
		Info.size = 80;
		Info.Life = 10000;
		Info.LifeTime = 10000;
		Info.a = 1;
	}
	if (OBJECT_ENEMYBUILDING)
	{
		Info.size = 80;
		Info.Life = 10000;
		Info.LifeTime = 10000;
		Info.a = 1;
	}
	if (OBJECT_ARROW == type)
	{
		Info.size = 6;
		Info.Life = 2;
		Info.LifeTime = 10000;
		Info.r = 0.5;
		Info.g = 0.2;
		Info.b = 0.7;
		Info.a = 1;
		int randX = rand() % 2;
		int randY = rand() % 2;
		if (randX == 0)
			Info.dirX = 5 + rand() % 10;
		if (randX == 1)
			Info.dirX = -(5 + rand() % 10);
		if (randY == 0)
			Info.dirY = 5 + rand() % 10;
		if (randY == 1)
			Info.dirY = -(5 + rand() % 10);
	}
	if (OBJECT_CHARACTER == type)
	{
		Info.size = 20;
		Info.Life = 10;
		Info.LifeTime = 10000;
		Info.r = 0;
		Info.g = 0;
		Info.b = 1;
		Info.a = 1;
		int randX = rand() % 2;
		int randY = rand() % 2;
		if (randX == 0)
			Info.dirX = +rand() % 10;
		if (randX == 1)
			Info.dirX = +rand() % 10;
		if (randY == 0)
			Info.dirY = +rand() % 10;
		if (randY == 1)
			Info.dirY = +rand() % 10;
	}
	if (OBJECT_BULLET == type)
	{
		Info.size = 2;
		Info.r = 1;
		Info.g = 0;
		Info.b = 0;
		Info.a = 1;
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
		Info.Life = 100;
		Info.LifeTime = 10000;
	}
	Info.x = x;
	Info.y = y;
}
Object::Object(float x, float y, OBJECT_TYPE type)
{
	if (OBJECT_BUILDING==type)
	{
		Info.size = 80;
		Info.Life = 10000;
		Info.LifeTime = 10000;
		Info.a = 1;
	}
	if (OBJECT_ARROW==type)
	{	
		Info.size = 6;
		Info.Life = 2;
		Info.LifeTime = 10000;
		Info.r = 1;
		Info.g = 1;
		Info.b = 0;
		Info.a = 1;
		int randX = rand() % 2;
		int randY = rand() % 2;
		if (randX == 0)
			Info.dirX = 5 + rand() % 10;
		if (randX == 1)
			Info.dirX = -(5 + rand() % 10);
		if (randY == 0)
			Info.dirY = 5 + rand() % 10;
		if (randY == 1)
			Info.dirY = -(5 + rand() % 10);
	}
	if (OBJECT_CHARACTER==type)
	{
		Info.size = 20;
		Info.Life = 10;
		Info.LifeTime = 10000;
		Info.r = 0;
		Info.g = 0;
		Info.b = 1;
		Info.a = 1;
		int randX = rand() % 2;
		int randY = rand() % 2;
		if (randX == 0)
			Info.dirX =  + rand() % 10;
		if (randX == 1)
			Info.dirX =  + rand() % 10;
		if (randY == 0)
			Info.dirY =  + rand() % 10;
		if (randY == 1)
			Info.dirY =  + rand() % 10;
	}
	if (OBJECT_BULLET==type)
	{
		Info.size = 2;
		Info.r = 1;
		Info.g = 0;
		Info.b = 0;
		Info.a = 1;
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
		Info.Life = 100;
		Info.LifeTime = 10000;
	}
	Info.x = x;
	Info.y = y;	
}
void Object::Damage(float n)
{
	Info.Life -= 0.1;
}
bool Object::MyCollision(Object* Object)
{
	if (Object != NULL)
	{
		return(
			Info.x - Info.size / 2 < Object->Info.x + Object->Info.size / 2 &&
			Info.x + Info.size / 2 > Object->Info.x - Object->Info.size / 2 &&
			Info.y - Info.size / 2 < Object->Info.y + Object->Info.size / 2 &&
			Info.y + Info.size / 2 > Object->Info.y - Object->Info.size / 2
			);
	}
}
int Object::GetType()
{
	return Info._type;
}
void Object::Update(float fTime)
{
	float elapsedTimeInSecond = fTime / 50;

	Info.Bullet += elapsedTimeInSecond;
	Info.x =Info.x + Info.dirX * elapsedTimeInSecond;
	Info.y = Info.y + Info.dirY * elapsedTimeInSecond;
	 

	if (240 <= Info.x)
		Info.dirX *= -1;
	if (-240 >= Info.x)
		Info.dirX *= -1;
	if (-380 >= Info.y)
		Info.dirY *= -1;
	if (400 <= Info.y)
		Info.dirY *= -1;	

}

