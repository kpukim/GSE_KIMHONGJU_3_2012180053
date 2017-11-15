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
#include <mmsystem.h>
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

SceneMgr *g_SceneMgr = NULL;

DWORD g_prevTime = 0;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	g_SceneMgr->UpdateObjects((float)elapsedTime);
	g_SceneMgr->DrawObjects();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y )
{
	static bool button_state = false;
	static int count = 0;
	int Time = 0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		button_state = true;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (button_state)
		{
			g_SceneMgr->AddObject(x - 250, 250 - y, OBJECT_CHARACTER);

			/*if (g_SceneMgr->AddObject(x ,  y, OBJECT_CHARACTER) && (g_SceneMgr->Return()))
			{
				g_SceneMgr->AddArrowObject(x - 250, 250 - y, OBJECT_ARROW);
			}
			while (g_SceneMgr->ReturnArrNull())
			{
				if (g_SceneMgr->ReturnArr())
				{
					continue;
				}
			}*/
		}
		button_state = false;
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
	glutInitWindowSize(500, 500);
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

	

	g_SceneMgr = new SceneMgr(500, 500);



	g_SceneMgr->AddBuildingObject(0, 0, OBJECT_BUILDING);
	g_prevTime = timeGetTime();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMainLoop();

	delete g_SceneMgr;
	return 0;
}

