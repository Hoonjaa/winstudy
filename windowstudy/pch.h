#pragma once

#include <windows.h>
#include<iostream>

#include <vector>//3학년 stl에 수강 예정
using std::vector;

#include "define.h"
#include "struct.h"

// 미리 컴파일 된 헤더
// 프로그램 -> 크기는 점점 커짐
// 전처리기가 컴파일 해야 하는 헤더가 엄청 많아진다.
// => 컴파일 시간 증가

// 자주 변경되지 않는 긴 소스를 미리 컴파일해서 시간을 단축한다.
// stdafx.h 로도 많이 사용