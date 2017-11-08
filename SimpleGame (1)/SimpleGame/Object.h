#pragma once
#include <cstdlib>
#include"stdafx.h"
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
	SceneMgr* g_SceneMgr;
	Information Info;

	float GetLife()  { return Info.Life; }
	float GetLifeTime() { return Info.LifeTime; }
	int Temp() {return Info.Life -= 2; }
	void Update(float elapsedTime);
};

