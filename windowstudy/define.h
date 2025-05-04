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

#define fDT TimeMgr::Instance()->getfDT();
#define DT TimeMgr::Instance()->getDT();

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