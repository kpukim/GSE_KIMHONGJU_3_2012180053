#include<Windows.h>
#include "stdafx.h" 
#include <time.h>
#define MOVE 1
#define TOP 270
#define WIDTH 800
#define HEIGHT 600
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
void Info::timeGetTime()
{

}
void Info::Init()
{	
	 m_Info->x_dir -= MOVE;
	 m_Info->y_dir += MOVE; 
}

void Info::Update(float Time)
{
	
	Time *= 0.5;
	if (TOP < m_Info->y + m_Info->size)
		m_Info->y_dir *= -1;
	
	m_Info->x += m_Info->x_dir * Time;
	m_Info->y += m_Info->y_dir * Time;


	//if ((m_Info->x + m_Info->x_dir + m_Info->size <= WIDTH) && (m_Info->x + m_Info->x_dir >= 0))  //바로 x 진행
	//	m_Info->x += m_Info->x_dir;
	//else
	//{
	//	m_Info->x_dir = -m_Info->x_dir;
	//	m_Info->x += m_Info->x_dir;
	//}
	//if ((m_Info->y + m_Info->y_dir + m_Info->size <= HEIGHT) && (m_Info->y + m_Info->y_dir >= 0))      //바로 y진행
	//	m_Info->y += m_Info->y_dir;
	//else
	//{          
	//	m_Info->y_dir = -m_Info->y_dir;
	//	m_Info->y += m_Info->y_dir;
	//}
}

void Info::Render()
{

}
void Info::Release()
{

}


