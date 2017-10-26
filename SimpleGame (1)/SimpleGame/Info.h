#pragma once

class Object;
class Info : public Object
{
private:


 public:
	 void Init();
	 void Update(float);
	 void Render();
	 void Release();
	 void timeGetTime();
	 void destory();
	 Info();
	 ~Info();
 };