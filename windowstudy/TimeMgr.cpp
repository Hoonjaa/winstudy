#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"

TimeMgr::TimeMgr()
	:curCount{}
	,prevCount{}
	,frequency{}
	,dDT(0.)
	,dAcc(0.)
	,iCallCount(0)
{
}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::Init()
{
	QueryPerformanceCounter(&prevCount);
	QueryPerformanceFrequency(&frequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&curCount);

	dDT = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
	prevCount = curCount;

#ifdef _DEBUG
	//디버그 모드에서 중단점 오래 걸면 시간이 말도 안되게 커질 때가 있음
	if (dDT > (1. / 60.))
		dDT = (1. / 60.);

#endif // _DEBUG
}

void TimeMgr::Render()
{
	++iCallCount;
	dAcc += dDT;

	if (dAcc >= 1.) {
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;
	}

	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
	//SetWindowText(Core::Instance()->getMainHandle(), szBuffer);
}
