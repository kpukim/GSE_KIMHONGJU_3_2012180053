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

SceneMgr *g_SceneMgr = NULL;
DWORD g_prevTime = 0;

bool Button = false;

void RenderScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
	glutInitWindowSize(500, 800);
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
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	g_SceneMgr = new SceneMgr(500, 800);

	g_SceneMgr->AddObjects(-150, 300, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(0, 300, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(150, 300, BUILDING_OBJECT, ENEMYTEAM);
	g_SceneMgr->AddObjects(-150, -300, BUILDING_OBJECT, MYTEAM);
	g_SceneMgr->AddObjects(0, -300, BUILDING_OBJECT, MYTEAM);
	g_SceneMgr->AddObjects(150, -300, BUILDING_OBJECT, MYTEAM);

	g_prevTime = timeGetTime();
	glutMainLoop();
	delete g_SceneMgr;
	return 0;
}

