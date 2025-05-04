#include "pch.h"
#include "Player.h"

#include "KeyMgr.h"
#include "TimeMgr.h"

void Player::Update()
{
	Vec2 vPos = getPos();

	if (KeyMgr::Instance()->GetKeyState(KEY::W) == KEY_STATE::HOLD) {
		vPos.y -= 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKeyState(KEY::S) == KEY_STATE::HOLD) {
		vPos.y += 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKeyState(KEY::A) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKeyState(KEY::D) == KEY_STATE::HOLD) {
		vPos.x += 200.f * DT;
	}
	setPos(vPos);
}
