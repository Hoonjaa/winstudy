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
	//���� �������� �ð��� speed��ŭ �̵�
	currPos.x += fDT * speed* dir;

	//��ȸ �Ÿ� �������� �Ѿ���� Ȯ��
	float dist = abs(centerPos.x - currPos.x) - maxDis;
	//�Ѿ� ���ٸ� ���� ����
	if (0.f < dist) {
		dir *= -1;
		currPos.x += dist * dir;
	}
	setPos(currPos);
}

//���� �� �ѽð��� ���� �˻�
//1) ���ݱ��� �� ���� + �ڵ�����ؼ� �ð������� �����ϱ�(flowChart�� �׸���)

//2) �÷��̾� �������� space�� ������ �̻���(��) �߻�