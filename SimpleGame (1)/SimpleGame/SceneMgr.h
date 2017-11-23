#pragma once
#include <cstdlib>
#include <iostream>
#include"stdafx.h"
#include "Renderer.h"
#include "Object.h"
#define MAX_OBJECT_COUNT 1000
#define MAX_CHARACTEROBJECT_COUNT 100

class SceneMgr
{
public:
	SceneMgr(int, int);
	~SceneMgr();

	int AddObject(float , float , enum OBJECT_TYPE);
	int AddBulletObject(float, float, enum OBJECT_TYPE);
	int AddBulletObject(float, float, enum OBJECT_TYPE, enum TEAM);
	void DeleteObject(int );
	void UpdateObjects(float );
	void DrawObjects();
	int AddArrowObject(float, float, enum OBJECT_TYPE);
	int AddBuildingObject(float, float, enum OBJECT_TYPE, enum TEAM);
	int AddEnemyBuildingObject(float, float, enum OBJECT_TYPE, enum TEAM);

	void DeleteBuildingObject(int);
	void DeleteArrowObject(int); 
	bool Col(Object* FObject, Object* SObeject);


	int Return() { return m_Objects[MAX_OBJECT_COUNT] != NULL; }
	int ReturnArr() { return m_arrowObjects[MAX_OBJECT_COUNT] != NULL; }
	int ReturnArrNull() { return m_arrowObjects[MAX_OBJECT_COUNT] == NULL; }
private:
	int num;


	Object *m_Objects[MAX_OBJECT_COUNT];
	Object *m_BuildingObject[MAX_OBJECT_COUNT];
	Object *m_bulletObjects[MAX_OBJECT_COUNT];
	Object *m_arrowObjects[MAX_OBJECT_COUNT];
	Object* m_EnemyBuildingObjects[MAX_OBJECT_COUNT];


	Renderer *m_renderer;
	Renderer* TextRender;
	int m_Width;
	int m_Height;
};


