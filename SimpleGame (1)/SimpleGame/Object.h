#pragma once
#include <cstdlib>

struct Information
{
	float x, y, dirX, dirY, r, g, b, a, size, life, lifetime;
	int team, type;
	float width, height, bullet, arrow;
};
class Object
{
public:
	Object(float, float, int, int, int, int);
	~Object();
	Information Info;
	float GetLife() { return Info.life; }
	float GetLifeTime() { return Info.lifetime; }
	int GetType() { return Info.type; }
	void SetDamage(float num) { Info.life -= num; }
	void Update(float);
};
