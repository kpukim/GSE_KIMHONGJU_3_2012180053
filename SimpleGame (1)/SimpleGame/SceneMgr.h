#pragma once
#include <cstdlib>
#include <iostream>
#include"stdafx.h"
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECT_COUNT 1000

class SceneMgr
{
public:
	SceneMgr(int, int);
	~SceneMgr();

	int AddObject(float , float , enum OBJECT_TYPE);
	int AddBulletObject(float, float, enum OBJECT_TYPE);
	void DeleteObject(int );
	void UpdateObjects(float );
	void DrawObjects();
	
private:
	bool ColTF(float, float, float, float, float, float, float, float);
	void Collision();
	Object *m_Objects[MAX_OBJECT_COUNT];
	Object *m_bulletObjects[MAX_OBJECT_COUNT];
	int GetMax();
	Renderer *m_renderer;

	int m_Width;
	int m_Height;
};


