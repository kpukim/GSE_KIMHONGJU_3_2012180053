/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/
#include "stdafx.h"


Renderer *g_Renderer = NULL;
Object * g_Object = NULL;
SceneMgr *g_SceneMgr = NULL;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	g_Renderer->DrawSolidRect(g_Object->GetInfo()->x,g_Object->GetInfo()->y,g_Object->GetInfo()->z,
		g_Object->GetInfo()->size,g_Object->GetInfo()->r,g_Object->GetInfo()->g,
		g_Object->GetInfo()->b,g_Object->GetInfo()->a);

	
	glutSwapBuffers();
}

void Idle(void)
{
	g_Object->Update(0.1);
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
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
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << " GLEW Version is 3.0\n ";

	else
		std::cout << "GLEW 3.0 not supported\n ";


	// Initialize Renderer
	g_Renderer = new Renderer(WINSIZEX, WINSIZEY);

	////////////
	g_Object = new Info();

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

	return 0;
}

