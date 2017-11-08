#pragma once
#include<iostream>
using namespace std;

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <time.h>
#include "Renderer.h"
#include "Object.h"
#include"SceneMgr.h"
#include "SceneMgr.h"
#include<vector>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#define WINSIZEX 500
#define WINSIZEY 500
enum OBJECT_TYPE
{
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};
