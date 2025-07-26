#pragma once

#include"pch.h"

#define SINGLE(type) public:\
	static type* Instance()\
	{\
	static type mgr;\
	return &mgr;\
	}\
	private:\
		type();\
		~type();

#define fDT TimeMgr::Instance()->getfDT()
#define DT TimeMgr::Instance()->getDT()

#define KEY_CHECK(key, state) KeyMgr::Instance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

enum class GROUP_TYPE {
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE {
	START,
	STAGE_01,
	STAGE_02,

	END,
};