#pragma once
#include "Object.h"
class Missile: public Object
{
private:
	float		dir;			//πÊ«‚
public:
	Missile();
	~Missile();

	virtual void Update();
	virtual void Render(HDC _hdc);

	void SetDir(bool _up)
	{
		if (_up) {
			dir = -1.f;
		}
		else {
			dir = 1.f;
		}
	}

};