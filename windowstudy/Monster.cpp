#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"

Monster::Monster()
	:speed(100.f)
	, centerPos(Vec2(0.f, 0.f))
	, maxDis(50.f)
	, dir(1)
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	/*Vec2 vPos = getPos();

	if (vPos.x < 400.f) {
		vPos.x += 200.f * DT;
	}
	if (vPos.x > 800.f) {
		vPos.x -= 200.f * DT;
	}

	setPos(vPos);*/

	Vec2 currPos = getPos();

	//l-value / r-value
	// 
	//진행 방향으로 시간당 speed만큼 이동
	currPos.x += fDT * speed* dir;

	//배회 거리 기준점을 넘어섰는지 확인
	float dist = abs(centerPos.x - currPos.x) - maxDis;
	//넘어 섰다면 방향 변경
	if (0.f < dist) {
		dir *= -1;
		currPos.x += dist * dir;
	}
	setPos(currPos);
}

//다음 주 한시간은 숙제 검사
//1) 지금까지 한 수업 + 코드관련해서 시각적으로 정리하기(flowChart로 그리기)

//2) 플레이어 기준으로 space바 누르면 미사일(원) 발사