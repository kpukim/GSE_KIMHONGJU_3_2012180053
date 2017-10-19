#include "stdafx.h" 
#include <time.h>
#define MOVE 1
Info::Info()
{
	m_Info = new Information();
	Init();
	m_Info->x = 100;
	m_Info->y = 0;
	m_Info->z = 100;
	m_Info->size = 30;
	m_Info->r = 1;
	m_Info->g = 0;
	m_Info->b = 0;
	m_Info->type = 0;
	m_Info->a = 0;
}

Info::~Info()
{
}

void Info::Init()
{	
		m_Info->x_dir -= MOVE;	
		m_Info->y_dir += MOVE;	
		_isInit = true;
		
}
void Info::Update(float Time)
{
	m_Info->x += m_Info->x_dir * Time;
	m_Info->y += m_Info->y_dir * Time;


}
void Info::Render()
{

}
void Info::Release()
{

}


