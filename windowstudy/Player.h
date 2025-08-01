#pragma once
#include "Object.h"

class Texture;

class Player : public Object {
private:
	Texture*	tex;
	void		CreateMissile();

public:
	Player();
	~Player();

	virtual void Update();
	virtual void Render(HDC _hdc);
};

