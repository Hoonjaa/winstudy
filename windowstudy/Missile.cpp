#include "pch.h"
#include "Missile.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

Missile::Missile()
	:dir(1.f)
{
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vec2 currPos = getPos();
	currPos.y += fDT * 600.f * dir;
	setPos(currPos);
}

void Missile::Render(HDC _hdc)
{
	Vec2 vPos = getPos();
	Vec2 vScale = getScale();
	Ellipse(_hdc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f));
}
