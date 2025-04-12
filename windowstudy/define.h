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