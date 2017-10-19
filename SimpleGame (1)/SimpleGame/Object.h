#pragma once

#include <string>
#pragma once
typedef struct Information
{
	int type;
	float x, y, z, size, r, g, b, a;
	int x_dir, y_dir;

}Information;
class Object
{
public:
		Information* m_Info;
		Renderer* m_Render;
		virtual void Init() = 0;
		virtual void Update(float) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
		Information* GetInfo();
		Object();
		~Object();
};
