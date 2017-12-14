/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "windows.h"
#include "SceneMgr.h"
#include "Object.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#define WIDTH 500
#define HEIGHT 800
SceneMgr *g_SceneMgr = NULL;
DWORD g_prevTime = 0;
bool Button = false;

Sound* g_Sound = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.f);

	DWORD CurrentTime = timeGetTime();
	DWORD elapsedTime = CurrentTime - g_prevTime;
	g_prevTime = CurrentTime;

	g_SceneMgr->UpdateObjects(elapsedTime);
	g_SceneMgr->DrawObjects(elapsedTime);


	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Button = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (Button)
		{
			for (int i = 0; i < 1; i++)
			{
				g_SceneMgr->AddObjects(x - 250, -y + 400, CHARACTER_OBJECT, MYTEAM);
			}
		}
		Button = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	g_Sound = new Sound();
	int Sound = g_Sound->CreateSound("SoundSample.mp3");
	g_Sound->PlaySoundGSE(Sound, true, 1);


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	g_SceneMgr = new SceneMgr(WIDTH, HEIGHT);

	g_SceneMgr->AddObjects(-205, 230, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(0, 330, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(205, 230, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(-205, -200, BUILDING_OBJECT, MYTEAM);
	g_SceneMgr->AddObjects(0, -300, BUILDING_OBJECT, MYTEAM);
	g_SceneMgr->AddObjects(205, -200, BUILDING_OBJECT, MYTEAM);
	
	g_prevTime = timeGetTime();
	glutMainLoop();
	delete g_SceneMgr;
	return 0;
}

