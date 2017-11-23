#include "stdafx.h"
#include "SceneMgr.h"
#define T 2
int CharacterCollisionCount = 0;
int ArrowCollisionCount = 0;
int BuildingCollisionCount = 0;
SceneMgr::~SceneMgr()
{
}
SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);
	m_Width = width;
	m_Height = height;

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		m_Objects[i] = NULL;
		m_Objects[i] = NULL;
		m_arrowObjects[i] = NULL;
		m_BuildingObject[i] = NULL;
		m_bulletObjects[i] = NULL;
		m_EnemyBuildingObjects[i] = NULL;
	}
}

void SceneMgr::DrawObjects()
{
	m_renderer->DrawSolidRect(1, 1, 0, m_Width, 0, 0.3, 0.3, 1);

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			m_renderer->DrawSolidRect
			(
				m_Objects[i]->Info.x,
				m_Objects[i]->Info.y,
				0,
				m_Objects[i]->Info.size,
				m_Objects[i]->Info.r,
				m_Objects[i]->Info.g,
				m_Objects[i]->Info.b,
				m_Objects[i]->Info.a
			);
		}
		if (m_BuildingObject[i] != NULL)
		{
			m_renderer->DrawTexturedRect
			(
				m_BuildingObject[i]->Info.x,
				m_BuildingObject[i]->Info.y,
				0,
				m_BuildingObject[i]->Info.size,
				m_BuildingObject[i]->Info.r,
				m_BuildingObject[i]->Info.g,
				m_BuildingObject[i]->Info.b,
				m_BuildingObject[i]->Info.a,
				TextRender->CreatePngTexture("Building.png")
			);
		}
		if (m_EnemyBuildingObjects[i] != NULL)
		{
			m_renderer->DrawTexturedRect
			(
				m_BuildingObject[i]->Info.x,
				m_BuildingObject[i]->Info.y+-700,
				0,
				m_BuildingObject[i]->Info.size,
				m_BuildingObject[i]->Info.r,
				m_BuildingObject[i]->Info.g,
				m_BuildingObject[i]->Info.b,
				m_BuildingObject[i]->Info.a,
				TextRender->CreatePngTexture("EnemyBuilding.png")
			);
		}

		if (m_bulletObjects[i] != NULL)
		{
			m_renderer->DrawSolidRect
			(
				m_bulletObjects[i]->Info.x,
				m_bulletObjects[i]->Info.y,
				0,
				m_bulletObjects[i]->Info.size,
				m_bulletObjects[i]->Info.r,
				m_bulletObjects[i]->Info.g,
				m_bulletObjects[i]->Info.b,
				m_bulletObjects[i]->Info.a
			);
		}
		if (m_arrowObjects[i] != NULL)
		{
			m_renderer->DrawSolidRect
			(
				m_arrowObjects[i]->Info.x,
				m_arrowObjects[i]->Info.y,
				0,
				m_arrowObjects[i]->Info.size,
				m_arrowObjects[i]->Info.r,
				m_arrowObjects[i]->Info.g,
				m_arrowObjects[i]->Info.b,
				m_arrowObjects[i]->Info.a
			);
		}
	}
	
}


int SceneMgr::AddObject(float x, float y, OBJECT_TYPE type)
{
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type);
			AddArrowObject(m_Objects[i]->Info.x, m_Objects[i]->Info.y, OBJECT_ARROW);		
			return i;
		}
		
	}
	return -1;
}
int SceneMgr::AddBuildingObject(float x, float y, enum OBJECT_TYPE type, enum TEAM team)
{
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		if (m_BuildingObject[i] == NULL)
		{
			m_BuildingObject[i] = new Object(x, y, type, team);
			return i;
		}
	}
	return -1;
}

int SceneMgr::AddEnemyBuildingObject(float x, float y, enum OBJECT_TYPE type, enum TEAM team)
{
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		if (m_EnemyBuildingObjects[i] == NULL)
		{
			m_EnemyBuildingObjects[i] = new Object(x, y, type, team);
			return i;
		}
	}
	return -1;
}
//int SceneMgr::AddEnemyBuildingObject(float x, float y, enum OBJECT_TYPE type)
//{
//	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
//	{
//		if (m_BuildingObject[i]->Info.TEAM_2 == NULL)
//		{
//			m_BuildingObject[i]->Info.TEAM_2 = new Object(x, y, type);
//			return i;
//		}
//	}
//	return -1;
//}
void SceneMgr::DeleteObject(int index)
{
	if (m_Objects[index] != NULL)
	{
		delete m_Objects[index];
		m_Objects[index] = NULL;
	}
}

void SceneMgr::DeleteBuildingObject(int index)
{
	if (m_BuildingObject[index] != NULL)
	{
		delete m_BuildingObject[index];
		m_BuildingObject[index] = NULL;
	}
}

void SceneMgr::DeleteArrowObject(int index)
{
	if (m_arrowObjects[index] != NULL)
	{
		delete m_arrowObjects[index];
		m_arrowObjects[index] = NULL;
	}
}

int SceneMgr::AddArrowObject(float x, float y, enum OBJECT_TYPE type)
{
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		if (m_arrowObjects[i] == NULL)
		{
			m_arrowObjects[i] = new Object(x, y, type);
			return i;
		}
	}
	return -1;
}

int SceneMgr::AddBulletObject(float x, float y, enum OBJECT_TYPE type, enum TEAM team)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_bulletObjects[i] == NULL)
		{
			m_bulletObjects[i] = new Object(x, y, type);
			return i;
		}
	}
	return -1; 
}

void SceneMgr::UpdateObjects(float elapsedTime)
{
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->GetLife() < 1 || m_Objects[i]->GetLifeTime() < 1)
			{
				delete m_Objects[i];
				m_Objects[i] = NULL;
			}
			else
			{
				m_Objects[i]->Update(elapsedTime);	
			}
		}
	}

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_bulletObjects[i] != NULL)
		{
			if (m_bulletObjects[i]->GetLife() < 0.0001f || m_bulletObjects[i]->GetLifeTime() < 0.0001f)
			{
				if (m_Objects[i]->GetType() == OBJECT_CHARACTER)
				{
					for (int j = 0; j < MAX_OBJECT_COUNT; j++)
					{
						if (m_bulletObjects[j] != NULL && m_arrowObjects[j]->Info._type == OBJECT_ARROW )
						{
							delete m_bulletObjects[j];
							m_bulletObjects[j] = NULL;
						}
					}
				}
				delete m_bulletObjects[i];
				m_bulletObjects[i] = NULL;
			}
			else
			{
				m_bulletObjects[i]->Update(elapsedTime);
				
					if (m_bulletObjects[i]->Info.Bullet > 1 )
					{
						int bullet = AddBulletObject(m_bulletObjects[i]->Info.x,m_bulletObjects[i]->Info.y,OBJECT_BULLET, TEAM_2);
						m_bulletObjects[i]->Info.Bullet = 0.f;
					}
			}
		}
	}

	/*
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_bulletObjects[i] != NULL)
		{
			if (m_bulletObjects[i]->GetLife() < 1 || m_bulletObjects[i]->GetLifeTime() < 1)
			{
				delete m_bulletObjects[i];
				m_bulletObjects[i] = NULL;
			}
			else
			{
				m_bulletObjects[i]->Update(elapsedTime);
			}
		}
		AddBulletObject(0, 0, OBJECT_BULLET);
	}
	*/

	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; i++)
	{
		if (m_arrowObjects[i] != NULL)
		{
			if (m_arrowObjects[i]->GetLife() < 1 || m_arrowObjects[i]->GetLifeTime() < 1)
			{
				delete m_arrowObjects[i];
				m_arrowObjects[i] = NULL;
			}
			else
			{
				m_arrowObjects[i]->Update(elapsedTime);
			}
		}
	}
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; ++i)
	{
		if (m_BuildingObject[i] != NULL)
		{
			if (m_BuildingObject[i]->GetLife() < 1 || m_BuildingObject[i]->GetLifeTime() < 1)
			{
				delete[] m_BuildingObject;
				m_BuildingObject[i] = NULL;
			}
			else
			{
				m_BuildingObject[i]->Update(elapsedTime);
			}
		}
	}

	
	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; ++i)
	{
		for (int j = 0; j < MAX_CHARACTEROBJECT_COUNT; ++j)
		{
			if (m_Objects[i] != NULL)
			{
				if (Col(m_Objects[i], m_BuildingObject[j]))
				{
					DeleteObject(i);
					m_BuildingObject[j]->Damage(m_BuildingObject[j]->GetLife());
				}
			}
		}
	}

	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; ++i)
	{
		for (int j = 0; j < MAX_CHARACTEROBJECT_COUNT; ++j)
		{
			if (m_arrowObjects[i] != NULL)
			{
				if (Col(m_arrowObjects[i], m_BuildingObject[j]))
				{
					DeleteArrowObject(i);
					m_BuildingObject[j]->Damage(m_BuildingObject[j]->GetLife());
				}
			}
		}
	}

	for (int i = 0; i < MAX_CHARACTEROBJECT_COUNT; ++i)
	{

			if (m_Objects[i] == NULL)
			{
				DeleteArrowObject(i);
			}
		
	}	
}

bool SceneMgr::Col(Object* FObject, Object* SObeject)
{
	return FObject->MyCollision(SObeject);
}



