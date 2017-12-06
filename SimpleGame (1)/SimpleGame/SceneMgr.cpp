#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr(int width, int height)
{
	Rend = new Renderer(width, height);
	this->width = width;
	this->height = height;
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		Objects[i] = NULL;
		BulletObjects[i] = NULL;
	}
}

void SceneMgr::DrawObjects(float Time)
{
	Rend->DrawSolidRectXY(0, 0, 0, width, height, 0, 0, 0, 0.3, Time);
	EnemyBuilding = Rend->CreatePngTexture("EnemyBuilding.png");
	Building = Rend->CreatePngTexture("Building.png");
	BackGround = Rend->CreatePngTexture("Map.png");
	int texture = -1;
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Objects[i] != NULL)
		{
			if (Objects[i]->Info.type == BUILDING_OBJECT)
			{		
				if (Objects[i]->Info.team == ENEMYTEAM)
				{
					texture = EnemyBuilding;
				}
				else if (Objects[i]->Info.team == MYTEAM)
				{
					texture = Building;
				}
				Rend->DrawTexturedRect(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size,
					Objects[i]->Info.r,
					Objects[i]->Info.g,
					Objects[i]->Info.b,
					Objects[i]->Info.a,
					texture,
					0.1
				);
			}

			/*Rend->DrawTexturedRect(
				Objects[i]->Info.x,
				Objects[i]->Info.y,
				0,
				Objects[i]->Info.size,
				1,
				1,
				1,
				1,
				texture,
				0.1f
			);

			Rend->DrawSolidRectGauge(
				Objects[i]->Info.x,
				Objects[i]->Info.y + Objects[i]->Info.size / 2,
				0,
				100,
				10,
				Objects[i]->Info.r,
				Objects[i]->Info.g,
				Objects[i]->Info.b,
				1.f,
				Objects[i]->Info.life / 500,
				0.01f
			);*/
			else
			{
				Rend->DrawSolidRect(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size,
					Objects[i]->Info.r,
					Objects[i]->Info.g,
					Objects[i]->Info.b,
					Objects[i]->Info.a,
					Time
				);
			}
		}
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Objects[i] == NULL)
		{
			delete Objects[i];
			Objects[i] = NULL;
		}
	}
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (BulletObjects[i] == NULL)
		{
			delete BulletObjects[i];
			BulletObjects[i] = NULL;
		}
	}
}

int SceneMgr::AddObjects(float x, float y, int type, int team)
{
	if (team == MYTEAM && type == CHARACTER_OBJECT)
	{
		if (MyCoolTime < 7.f)
		{
			return -1;
		}
		if (y > 0)
		{
			return -1;
		}
		MyCoolTime = 0.f;
	}
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Objects[i] == NULL)
		{
			Objects[i] = new Object(x, y, type, width, height, team);
			return i;
		}
	}
	return -1;
}

void SceneMgr::EnemyCharacter(float Time)
{
	EnemyCoolTime += Time / 1000.f;
	if (EnemyCoolTime > 5.f)
	{
		int x, y;
		x = (int)(height * rand() / (float)RAND_MAX);
		y = (int)(width * rand() / (float)RAND_MAX);
		AddObjects(x, y, CHARACTER_OBJECT, ENEMYTEAM);
		EnemyCoolTime = 0.f;
	}
}
void SceneMgr::UpdateObjects(float Time)
{
	MyCoolTime += Time / 1000;
	EnemyCharacter(Time);
	Collision();

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Objects[i] != NULL)
		{
			if (Objects[i]->GetLife() < 0.0001f || Objects[i]->GetLifeTime() < 0.0001f)
			{
				if (Objects[i]->GetType() == CHARACTER_OBJECT)
				{
					for (int j = 0; j < MAX_OBJECT_COUNT; j++)
					{
						if (Objects[j] != NULL && Objects[j]->Info.type == ARROW_OBJECT)
						{
							delete Objects[j];
							Objects[j] = NULL;
						}
					}
				}
				delete Objects[i];
				Objects[i] = NULL;
			}
			else
			{
				Objects[i]->Update(Time);
				if (Objects[i]->GetType() == BUILDING_OBJECT)
				{
					if (Objects[i]->Info.bullet > 10.f)
					{
						int bulletID = AddObjects(
							Objects[i]->Info.x,
							Objects[i]->Info.y,
							BULLET_OBJECT,
							Objects[i]->Info.team);

						Objects[i]->Info.bullet = 0.f;

					}
				}
				if (Objects[i]->GetType() == CHARACTER_OBJECT)
				{
					if (Objects[i]->Info.arrow > 3.f)
					{
						int arrowID = AddObjects(Objects[i]->Info.x, Objects[i]->Info.y, ARROW_OBJECT, Objects[i]->Info.team);
						Objects[i]->Info.arrow = 0.f;
					}
				}
			}
		}
		if (BulletObjects[i] != NULL)
		{
			BulletObjects[i]->Update(Time);
		}
	}
}

void SceneMgr::Collision()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		collisionCount = 0;
		if (Objects[i] != NULL)
		{
			for (int j = i + 1; j < MAX_OBJECT_COUNT; j++)
			{
				if (Objects[j] != NULL && Objects[i] != NULL)
				{
					float minX, minY, minX1, minY1, maxX, maxY, maxX1, maxY1;

					minX = Objects[i]->Info.x - Objects[i]->Info.size / 2;
					minY = Objects[i]->Info.y - Objects[i]->Info.size / 2;
					maxX = Objects[i]->Info.x + Objects[i]->Info.size / 2;
					maxY = Objects[i]->Info.y + Objects[i]->Info.size / 2;
					minX1 = Objects[j]->Info.x - Objects[j]->Info.size / 2;
					minY1 = Objects[j]->Info.y - Objects[j]->Info.size / 2;
					maxX1 = Objects[j]->Info.x + Objects[j]->Info.size / 2;
					maxY1 = Objects[j]->Info.y + Objects[j]->Info.size / 2;
					if (TrueFalseCollision(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						if ((Objects[i]->GetType() == BUILDING_OBJECT) && (Objects[j]->GetType() == CHARACTER_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0.f;
							collisionCount++;
						}
						else if ((Objects[j]->GetType() == BUILDING_OBJECT) && (Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0.f;
							collisionCount++;
						}
						else if ((Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[j]->GetType() == BULLET_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0.f;
						}
						else if ((Objects[j]->GetType() == CHARACTER_OBJECT) && (Objects[i]->GetType() == BULLET_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0.f;
						}
						else if ((Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[j]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0.f;
						}
						else if ((Objects[j]->GetType() == CHARACTER_OBJECT) && (Objects[i]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0.f;
						}
						else if ((Objects[i]->GetType() == BUILDING_OBJECT) && (Objects[j]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0.f;
						}
						else if ((Objects[j]->GetType() == BUILDING_OBJECT) && (Objects[i]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0.f;
						}
					}
				}
			}
		}
	}
}

bool SceneMgr::TrueFalseCollision(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)return false;
	if (maxX < minX1)return false;
	if (minY > maxY1)return false;
	if (maxY < minY1)return false;
	return true;
}
