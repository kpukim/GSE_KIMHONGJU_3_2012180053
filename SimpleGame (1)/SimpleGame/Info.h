#pragma once

class Object;
class Info : public Object
{
private:
	bool _isInit;

 public:
	 void Init();
	 void Update(float);
	 void Render();
	 void Release();

 public:
	 Info();
	 ~Info();
 };