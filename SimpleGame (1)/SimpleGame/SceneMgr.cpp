#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::update(float Time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		update(Time);
	}

}
void SceneMgr::Renderer()
{


}
void SceneMgr::Collision()
{


}