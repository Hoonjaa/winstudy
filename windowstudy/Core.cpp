#include "pch.h"
#include "Core.h"

#include"TimeMgr.h"
#include"Object.h"

Object obj;

Core::Core()
	:handle(0)
	, ptResoultion{}
	,hDC(0)
	,hBit(0)
	,mDC(0)
{
}

Core::~Core()
{
	ReleaseDC(handle, hDC);	//hDC 해제 하는 부분

	DeleteDC(mDC);
	DeleteObject(hBit);
}



int Core::Init(HWND _handle, POINT _ptResoultion)	//class 객체가 시작할 때 초기화해야 하는 부분
{
	handle = _handle;
	ptResoultion = _ptResoultion;

	RECT rt = { 0,0,ptResoultion.x,ptResoultion.y };
		//해상도 : 0, 0, 0000 , 0000

	//Manager
	TimeMgr::Instance()->Init();


	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW,true);
	//실제로 그릴 수 있는 영역을 계산한다.
	//메뉴바나 윈도우 창 주변으로 생겨있는 테두리 영역을 제외한 영역을 계산한다
	//1.윈도우 크기와 위치를 지정하는 rect 구조체에 대한 포인터	&rt
	//2.윈도우 스타일 (모양/동작 - 테두리, 제목 표시줄, 크기 조정이 가능한지 등등)	WS_OVERLAPPEDWINDOW
	//3.메뉴바	true

	SetWindowPos(handle, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//RECT 구조체를 이용해서 윈도우 크기를 조정하고 있는데, 위 함수는 윈도우의 위치와 크기를 설정한다.
	//1. hWnd : 윈도우 핸들
	//2. hWndlnsertAfter : 새로운 z순서를 설정
	//3. X : 윈도우의 X좌표
	//4. Y : 윈도우의 Y좌표
	//5. cx : 윈도우의 너비
	//6. cy : 윈도우의 높이
	//7. uFlags : 윈도우의 위치와 크기를 설정하는데 사용되는 플래그

	hDC = GetDC(handle);

	//이중 버퍼링 용도의 비트맵과 DC를 만들어야 함.
	hBit = CreateCompatibleBitmap(hDC, ptResoultion.x, ptResoultion.y);	//같은 해상도 크기의 비트맵을 하나 만든거임

	//이 핸들 아이디를 받아서 이 비트맵을 상대로 하는 DC를 만든다
	mDC = CreateCompatibleDC(hDC);

	// 새로 생성된 비트맵을 DC에 선택해서 이 비트맵에 그림을 그리도록 설정
	//-> 이전에 선택된 비트맵을 반환하고 사용이 끝난 후에 메모리 누수를 방지해야 해서 삭제하는 일을 진행
	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	
	obj.setPos(Vec2((float)(ptResoultion.x / 2), (float)(ptResoultion.y / 2)));
	obj.setScale(Vec2(100, 100));

	return S_OK;	//HRESULT 나중에 함 찾아보삼 작업이 성공했단 의미
}

void Core::Progress()
{
	TimeMgr::Instance()->Update();

	Update();
	Render();
}

void Core::Update()
{
	Vec2 vPos = obj.getPos();

	//계산 (물체의 변경된 좌표, 상태 추적하고 업데이트)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		vPos.x -= 200.f * DT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		vPos.x += 200.f * fDT;
	}

	obj.setPos(vPos);
}

void Core::Render()
{
	Rectangle(hDC, -1, -1, ptResoultion.x + 1, ptResoultion.y + 1);

	Vec2 vPos = obj.getPos();
	Vec2 vScale = obj.getScale();
	//그리기
	Rectangle(hDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	//완성된 그림을 복사하는 코드
	BitBlt(hDC, 0, 0, ptResoultion.x, ptResoultion.y,	//목적지, 복사 받을 부위
		mDC, 0, 0, SRCCOPY); // 복사 대상

	// 하나하나 픽셀 이동 -> CPU 부하
	// => 다렉X --- GPU

	//winAPI : 느려, 한 픽셀 단위 복사하는 일을 제외하고 여기서 더 성능 저하? 아니잖아. 그래서 일단 이걸로 만족
}

//가상함수 (virtual) 숙제해라