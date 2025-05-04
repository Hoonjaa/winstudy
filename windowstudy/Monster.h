#pragma once
#include "Object.h"

class Monster: public Object {
private:
	float		speed;			//속도
	float		maxDis;			//최대 이동거리
	int			dir;			//방향
	Vec2		centerPos;		//중앙 기준값
public:
	Monster();
	~Monster();

	virtual void Update();

	float GetSpeed() { return speed; }
	Vec2 GetCenterPos() { return centerPos; }

	void SetSpeed(float spd) { speed = spd; }
	void SetMoveDist(float dis) { maxDis = dis; }
	void SetCenterPos(Vec2 pos) { centerPos = pos; }

};

//좌우로 일정 거리를 움직이는 몬스터