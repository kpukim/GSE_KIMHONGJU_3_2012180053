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

	EnemyBuilding = Rend->CreatePngTexture("EnemyBuilding.png");
	Building = Rend->CreatePngTexture("Building.png");
	BackGround = Rend->CreatePngTexture("Map.png");
	Character = Rend->CreatePngTexture("Character.png");
	Enemycharacter = Rend->CreatePngTexture("EnemyCharacter.png");
	Particle = Rend->CreatePngTexture("ParticleEffect.png");
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
void SceneMgr::DrawObjects(float Time)
{
	Rend->DrawTexturedRectXY(0, 0, 0, WIDTH, HEIGHT, 1, 1, 1, 1, BackGround, 0.9);
	Rend->drawText
	(
		-60,
		150 ,
		GLUT_BITMAP_TIMES_ROMAN_24,
		0,
		0, 
		0,
		"Enemy Team"
	);
	Rend->drawText
	(
		-50,
		-150,
		GLUT_BITMAP_TIMES_ROMAN_24,
		0,
		0,
		0,
		"My Team"
	);
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Objects[i] != NULL)
		{
			if (Objects[i]->Info.type == BUILDING_OBJECT)
			{
				if (Objects[i]->Info.team == ENEMYTEAM)
					texture = EnemyBuilding;

				if (Objects[i]->Info.team == MYTEAM)
					texture = Building;

				Rend->DrawTexturedRect
				(
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
			
				Rend->DrawSolidRectGauge
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y + Objects[i]->Info.size / 2 + 5,
					0,
					BUILDING_GAUGEWIDTH,
					BUILDING_GAUGEHEIGHT,
					2,
					1,
					2,
					1,
					Objects[i]->Info.life / BUILDING_LIFE,
					0.1
				);
			}
			else if (Objects[i]->Info.type == CHARACTER_OBJECT)
			{
				if (Objects[i]->Info.team == ENEMYTEAM)
					texture = Enemycharacter;

				if (Objects[i]->Info.team == MYTEAM)
					texture = Character;
				
				Rend->DrawTexturedRectSeq
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size,
					1,
					1,
					1,
					1,
					texture,
					0,0,4,1,
					0.2
				);
				Rend->DrawSolidRectGauge
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y + Objects[i]->Info.size / 2 + 5,
					0,
					CHARACTER_GAUGEWIDTH,
					CHARACTER_GAUGEHEIGHT,
					Objects[i]->Info.r,
					Objects[i]->Info.g,
					Objects[i]->Info.b,
					1,
					Objects[i]->Info.life / CHARACTER_LIFE,
					0.2
				);
			}
			else if (Objects[i]->Info.type == BULLET_OBJECT)
			{				
				Rend->DrawParticle
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size, 
					1,
					1,
					1,
					1,
					Objects[i]->Info.dirX*(-5),
					Objects[i]->Info.dirY*(-5),
					Particle,
					Second
				);

				Rend->DrawSolidRect
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size,
					Objects[i]->Info.r,
					Objects[i]->Info.g,
					Objects[i]->Info.b,
					Objects[i]->Info.a,
					0.3
				);
			}
			else if (Objects[i]->Info.type == ARROW_OBJECT)
			{
				Rend->DrawSolidRect
				(
					Objects[i]->Info.x,
					Objects[i]->Info.y,
					0,
					Objects[i]->Info.size,
					Objects[i]->Info.r,
					Objects[i]->Info.g,
					Objects[i]->Info.b,
					Objects[i]->Info.a,
					0.3
				);
			}
		}
	}
}



int SceneMgr::AddObjects(float x, float y, int type, int team)
{
	if (team == MYTEAM && type == CHARACTER_OBJECT)
	{
		if (MyCoolTime < 2)
			return -1;
		if (y > 0)
			return -1;
		MyCoolTime = 0;
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
	EnemyCoolTime += Time / 1000;
	if (EnemyCoolTime > 1)
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
			if (Objects[i]->GetLife() < 0.0001 || Objects[i]->GetLifeTime() < 0.0001)
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
					if (Objects[i]->Info.bullet > 10)
					{
						int bulletID = AddObjects(
							Objects[i]->Info.x,
							Objects[i]->Info.y,
							BULLET_OBJECT,
							Objects[i]->Info.team);

						Objects[i]->Info.bullet =0;

					}
				}
				if (Objects[i]->GetType() == CHARACTER_OBJECT)
				{
					if (Objects[i]->Info.arrow > 3)
					{
						int arrowID = AddObjects(Objects[i]->Info.x, Objects[i]->Info.y, ARROW_OBJECT, Objects[i]->Info.team);
						Objects[i]->Info.arrow = 0;
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
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
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
							Objects[j]->Info.life = 0;
						}
						else if ((Objects[j]->GetType() == BUILDING_OBJECT) && (Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0;
						}
						else if ((Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[j]->GetType() == BULLET_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0;
						}
						else if ((Objects[j]->GetType() == CHARACTER_OBJECT) && (Objects[i]->GetType() == BULLET_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0;
						}
						else if ((Objects[i]->GetType() == CHARACTER_OBJECT) && (Objects[j]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0;
						}
						else if ((Objects[j]->GetType() == CHARACTER_OBJECT) && (Objects[i]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0;
						}
						else if ((Objects[i]->GetType() == BUILDING_OBJECT) && (Objects[j]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[i]->SetDamage(Objects[j]->GetLife());
							Objects[j]->Info.life = 0;
						}
						else if ((Objects[j]->GetType() == BUILDING_OBJECT) && (Objects[i]->GetType() == ARROW_OBJECT) && (Objects[i]->Info.team != Objects[j]->Info.team))
						{
							Objects[j]->SetDamage(Objects[i]->GetLife());
							Objects[i]->Info.life = 0;
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
