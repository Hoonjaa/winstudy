#pragma once
#include "Object.h"
class Missile: public Object
{
private:
	//이때 방향을 각도로 받는다면? 이게 숙제 Normalize!!
	float	theta;
	Vec2	dir;
public:
	Missile();
	~Missile();

	virtual void Update();
	virtual void Render(HDC _hdc);

	void SetDir(bool _th) { theta = _th; }
	void SetDir(Vec2 _dir)
	{
		dir = _dir;
		dir.Normalize();
	}
};