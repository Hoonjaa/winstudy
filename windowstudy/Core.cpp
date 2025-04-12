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
	ReleaseDC(handle, hDC);	//hDC ���� �ϴ� �κ�

	DeleteDC(mDC);
	DeleteObject(hBit);
}



int Core::Init(HWND _handle, POINT _ptResoultion)	//class ��ü�� ������ �� �ʱ�ȭ�ؾ� �ϴ� �κ�
{
	handle = _handle;
	ptResoultion = _ptResoultion;

	RECT rt = { 0,0,ptResoultion.x,ptResoultion.y };
		//�ػ� : 0, 0, 0000 , 0000

	//Manager
	TimeMgr::Instance()->Init();


	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW,true);
	//������ �׸� �� �ִ� ������ ����Ѵ�.
	//�޴��ٳ� ������ â �ֺ����� �����ִ� �׵θ� ������ ������ ������ ����Ѵ�
	//1.������ ũ��� ��ġ�� �����ϴ� rect ����ü�� ���� ������	&rt
	//2.������ ��Ÿ�� (���/���� - �׵θ�, ���� ǥ����, ũ�� ������ �������� ���)	WS_OVERLAPPEDWINDOW
	//3.�޴���	true

	SetWindowPos(handle, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//RECT ����ü�� �̿��ؼ� ������ ũ�⸦ �����ϰ� �ִµ�, �� �Լ��� �������� ��ġ�� ũ�⸦ �����Ѵ�.
	//1. hWnd : ������ �ڵ�
	//2. hWndlnsertAfter : ���ο� z������ ����
	//3. X : �������� X��ǥ
	//4. Y : �������� Y��ǥ
	//5. cx : �������� �ʺ�
	//6. cy : �������� ����
	//7. uFlags : �������� ��ġ�� ũ�⸦ �����ϴµ� ���Ǵ� �÷���

	hDC = GetDC(handle);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ������ ��.
	hBit = CreateCompatibleBitmap(hDC, ptResoultion.x, ptResoultion.y);	//���� �ػ� ũ���� ��Ʈ���� �ϳ� �������

	//�� �ڵ� ���̵� �޾Ƽ� �� ��Ʈ���� ���� �ϴ� DC�� �����
	mDC = CreateCompatibleDC(hDC);

	// ���� ������ ��Ʈ���� DC�� �����ؼ� �� ��Ʈ�ʿ� �׸��� �׸����� ����
	//-> ������ ���õ� ��Ʈ���� ��ȯ�ϰ� ����� ���� �Ŀ� �޸� ������ �����ؾ� �ؼ� �����ϴ� ���� ����
	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	
	obj.setPos(Vec2((float)(ptResoultion.x / 2), (float)(ptResoultion.y / 2)));
	obj.setScale(Vec2(100, 100));

	return S_OK;	//HRESULT ���߿� �� ã�ƺ��� �۾��� �����ߴ� �ǹ�
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

	//��� (��ü�� ����� ��ǥ, ���� �����ϰ� ������Ʈ)
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
	//�׸���
	Rectangle(hDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	//�ϼ��� �׸��� �����ϴ� �ڵ�
	BitBlt(hDC, 0, 0, ptResoultion.x, ptResoultion.y,	//������, ���� ���� ����
		mDC, 0, 0, SRCCOPY); // ���� ���

	// �ϳ��ϳ� �ȼ� �̵� -> CPU ����
	// => �ٷ�X --- GPU

	//winAPI : ����, �� �ȼ� ���� �����ϴ� ���� �����ϰ� ���⼭ �� ���� ����? �ƴ��ݾ�. �׷��� �ϴ� �̰ɷ� ����
}

//�����Լ� (virtual) �����ض�