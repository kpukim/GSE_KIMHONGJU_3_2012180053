#pragma once
#define MAX_OBJECTS_COUNT 10

class Object;
class Renderer;

class SceneMgr
{
private:
	Object* m_Object[MAX_OBJECTS_COUNT];
	Renderer* m_Renderer;

public:
	void update(float);
	void Renderer();
	void Collision();



	SceneMgr();
	~SceneMgr();
};




 
