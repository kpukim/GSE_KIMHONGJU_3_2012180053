#pragma once
#include <cstdlib>
#include <iostream>
#include "Renderer.h"
#include "Object.h"


#define MAX_OBJECT_COUNT 1000
#define CHARACTER_OBJECT 0
#define BUILDING_OBJECT 1
#define BULLET_OBJECT 2
#define ARROW_OBJECT 3
#define ENEMYTEAM 4
#define MYTEAM 5
#define BUILDING_GAUGEWIDTH 100
#define BUILDING_GAUGEHEIGHT 10
class SceneMgr
{
public:
	SceneMgr(int, int);
	~SceneMgr();
	int AddObjects(float, float, int, int);
	void UpdateObjects(float);
	void DrawObjects(float);

private:
	bool TrueFalseCollision(float, float, float, float, float, float, float, float);
	void Collision();
	void EnemyCharacter(float);
	Object *Objects[MAX_OBJECT_COUNT];
	Object *BulletObjects[MAX_OBJECT_COUNT];
	Renderer *Rend;
	int width;
	int height;
	int EnemyBuilding;
	int Building;
	int BackGround;
	float EnemyCoolTime = 0;
	float MyCoolTime = 0;
};

