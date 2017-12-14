#pragma once
#include <cstdlib>
#include <iostream>
#include "Renderer.h"
#include "Object.h"
#include"Sound.h"

#define MAX_OBJECT_COUNT 1000
#define CHARACTER_OBJECT 0
#define BUILDING_OBJECT 1
#define BULLET_OBJECT 2
#define ARROW_OBJECT 3
#define ENEMYTEAM 4
#define MYTEAM 5
#define WIDTH 500
#define HEIGHT 800
#define BUILDING_GAUGEWIDTH 100
#define BUILDING_GAUGEHEIGHT 10
#define BUILDING_LIFE 500
#define CHARACTER_LIFE 100
#define CHARACTER_GAUGEWIDTH 30
#define CHARACTER_GAUGEHEIGHT 5


class SceneMgr
{
public:
	SceneMgr(int, int);
	~SceneMgr();
	int AddObjects(float, float, int, int);
	void UpdateObjects(float);
	void DrawObjects(float);
	bool TrueFalseCollision(float, float, float, float, float, float, float, float);

	void EnemyCharacter(float);
private:
	int texture = -1;
	void Collision();
	Sound* m_sound;
	int m_collSIndex;
	Object *Objects[MAX_OBJECT_COUNT];
	Object *BulletObjects[MAX_OBJECT_COUNT];
	Renderer *Rend;
	int width;
	int height;
	float Second;
	int EnemyBuilding;
	int Building;
	int Character;
	int Particle;
	int Enemycharacter;
	int BackGround;
	float EnemyCoolTime = 0;
	float MyCoolTime = 0;
};

