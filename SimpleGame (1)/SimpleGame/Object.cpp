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
		Info.Life = 10000;
		Info.LifeTime = 10000;
		Info.r = 1;
		Info.g = 0;
		Info.b = 3;
		Info.a = 1;
	}
	if (OBJECT_ARROW==type)
	{	
		Info.size = 5;
		Info.Life = 2;
		Info.LifeTime = 1000;
		Info.r = 0;
		Info.g = 3;
		Info.b = 3;
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
		Info.size = 10;
		Info.Life = 10;
		Info.LifeTime = 100;
	
		Info.r = 1;
		Info.g = 1;
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
		Info.r = 0;
		Info.g = 1;
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
		Info.LifeTime = 100000;
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

