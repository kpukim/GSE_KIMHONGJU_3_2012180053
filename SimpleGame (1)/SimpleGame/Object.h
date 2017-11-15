#pragma once
#include <cstdlib>
#include"stdafx.h"
//#define MAX_OBJECT_COUNT 1000

struct Information
{
	float x, y, dirX, dirY, size, r, g, b, a, Life, LifeTime, type, speed;
	enum OBJECT_TYPE _type;
};
class SceneMgr;

class Object
{

public:
	Object();
	Object(float x, float y, enum OBJECT_TYPE);
	~Object();

public:
	Renderer* textRenderer;
	SceneMgr* g_SceneMgr;
	Information Info;
	bool MyCollision(Object* Object);
	float GetLife()  { return Info.Life; }
	float GetLifeTime() { return Info.LifeTime; }
	void Update(float elapsedTime);
	void Damage(float num);
};

