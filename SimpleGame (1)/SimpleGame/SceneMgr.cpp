#include "stdafx.h"
#include "SceneMgr.h"
#define T 2

//총알오브젝트 함수add추가하고 draw에 bulletob도 추가 업데이트에 추가해서 움직일수있게 bulletob가
SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);
	m_Width = width;
	m_Height = height;

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		m_Objects[i] = NULL;
		m_Objects[i] = NULL;
	}
}

void SceneMgr::DrawObjects()
{
	m_renderer->DrawSolidRect(1, 1, 0, m_Width, 0,0.3,0.3,1);

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
		//
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
	}
}

SceneMgr::~SceneMgr()
{
}

int SceneMgr::AddObject(float x, float y, OBJECT_TYPE type)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y,type);
			return i;
		}
	}
	return -1;
}

void SceneMgr::DeleteObject(int index)
{
	if (m_Objects[index] != NULL)
	{
		delete m_Objects[index];
		m_Objects[index] = NULL;
	}
}
int SceneMgr::AddBulletObject(float x, float y, enum OBJECT_TYPE type)
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
	Collision();
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
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
}
int SceneMgr::GetMax()
{
	return MAX_OBJECT_COUNT;
}
void SceneMgr::Collision()
{
	int collisionCount = 0;
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		
			if (m_Objects[i] != NULL)
			{
				for (int j = 0; j < MAX_OBJECT_COUNT; j++)
				{
					if (i == j) continue;
					if (m_Objects[j] != NULL)
					{
						float minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1;
						minX  = m_Objects[i]->Info.x - m_Objects[i]->Info.size / T;
						minY  = m_Objects[i]->Info.y - m_Objects[i]->Info.size / T;
						maxX  = m_Objects[i]->Info.x + m_Objects[i]->Info.size / T;
						maxY  = m_Objects[i]->Info.y + m_Objects[i]->Info.size / T;
						minX1 = m_Objects[j]->Info.x - m_Objects[j]->Info.size / T;
						minY1 = m_Objects[j]->Info.y - m_Objects[j]->Info.size / T;
						maxX1 = m_Objects[j]->Info.x + m_Objects[j]->Info.size / T;
						maxY1 = m_Objects[j]->Info.y + m_Objects[j]->Info.size / T;
						if (ColTF(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
							collisionCount++;					
					}
				}
				if (collisionCount > 0)
				{
					m_Objects[i]->Info.r = 1;
					m_Objects[i]->Info.g = 0;
					m_Objects[i]->Info.b = 0;
					m_Objects[i]->Info.a = 1;
					m_Objects[i]->Info.Life -= 0.1;
				}
				else
				{
					m_Objects[i]->Info.r = 1;
					m_Objects[i]->Info.g = 1;
					m_Objects[i]->Info.b = 1;
					m_Objects[i]->Info.a = 1;
				}
			}
		}
}

bool SceneMgr::ColTF(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1) return false;
	if (maxX < minX1) return false;
	if (minY > maxY1) return false;
	if (maxY < minY1) return false;
	return true;
}
