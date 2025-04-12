#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
private:
	LARGE_INTEGER	curCount;
	LARGE_INTEGER	prevCount;
	LARGE_INTEGER	frequency;

	double			dDT;
	double			dAcc;
	UINT			iCallCount;
	UINT			iFPS;

public:
	void			Init();
	void			Update();

	double			getDT() { return dDT; }
	float			getfDT() { return (float)dDT; }
};

//보통 게임은 시간이 fps로 표현된다
//1초에 2프레임이야, 1 프레임 0.5초
//1초에 10프레임이야, 1 프레임 0.1초
//=> 프레임의 역수 = 한 프레임당 걸리는 시간

//LARGE_INTEGER : 64비트 정수
//1.curCount : 현재시간
//2.prevCount : 이전 시간
//3.frequency : 성능 카운터가 초당 몇 번 됐니?(주기)

//dDT : 두 프레임 사이의 시간 값( 현재 시간과 이전시간의 차이를 구함 -> 시스템 성능 카운터 주파수로 나누면 됨 )
//dAcc : 누적 경과 시간 (1초를 초과하면 FPS를 계산하고 초기화)
//iCallCount : Update 함수의 호출 횟수 저장
//iFPS : 프레임 속도(1초당 Update 호출 횟수)