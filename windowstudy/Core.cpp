#include "pch.h"
#include "Core.h"

#include"TimeMgr.h"
#include"Object.h"
#include"KeyMgr.h"
#include"SceneMgr.h"
#include"PathMgr.h"

Core::Core()
	:handle(0)
	,ptResolution{}
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
	ptResolution = _ptResoultion;

	RECT rt = { 0,0,ptResolution.x,ptResolution.y };
		//�ػ� : 0, 0, 0000 , 0000

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
	hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);	//���� �ػ� ũ���� ��Ʈ���� �ϳ� �������

	//�� �ڵ� ���̵� �޾Ƽ� �� ��Ʈ���� ���� �ϴ� DC�� �����
	mDC = CreateCompatibleDC(hDC);

	// ���� ������ ��Ʈ���� DC�� �����ؼ� �� ��Ʈ�ʿ� �׸��� �׸����� ����
	//-> ������ ���õ� ��Ʈ���� ��ȯ�ϰ� ����� ���� �Ŀ� �޸� ������ �����ؾ� �ؼ� �����ϴ� ���� ����
	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	//Manager
	PathMgr::Instance()->Init();
	TimeMgr::Instance()->Init();
	KeyMgr::Instance()->Init();
	SceneMgr::Instance()->Init();
	
	return S_OK;	//HRESULT ���߿� �� ã�ƺ��� �۾��� �����ߴ� �ǹ�
}

void Core::Progress()
{
	TimeMgr::Instance()->Update();
	KeyMgr::Instance()->Update();
	SceneMgr::Instance()->Update();
	

	Rectangle(mDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	SceneMgr::Instance()->Render(mDC);

	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y,	//������, ���� ���� ����
		mDC, 0, 0, SRCCOPY); // ���� ���

	TimeMgr::Instance()->Render();
}


//�����Լ� (virtual) �����ض�
//Key Manager
//1. a�� b��ü�� �̵��ϴ� �����̴�. Ű �Ŵ����� ������ �ڽ��� Ű �Է��� ���������� ó���ϰ� �ȴ�.
//	�� ����� ��Ȳ�߿� a��ü�� ���� ������(�ð�)�� �̵��� ó��������, b�� ���� �����ӿ��� �̵��� ó���� �� �ִ�.
//2. �츮�� ������ �ϴ� �����̾�. ����ŷ. ª�� ������ ���� ��� ������ ���� ���󰡴� ���� �ٸ� �����̴�. �̸� ��� ����?


//�츮�� �۾��ϴ� ���� : �� ���� UPDATE Ȯ���ϰ� ���� -> ������Ʈ ������ �� �������� �ݿ��ؼ� ����(Render)
//�츮�� �� ������ �ð�(DT)�� ���� ���� ������� �� �� �ִ�. ���ε��� �̵��ϴ� ���� �� �� ����.
//���� ������ ������ A -> B �������� ġ��, ���� �����̴� �ɷ� ���δ�.
//�� �����ӿ��� ����Ǵ� Ű�� ���� �̺�Ʈ�� ó���Ǿ�� �Ѵ� (��Ģ)

//�ϴ���
//1. ������ ����ȭ : ���� ������ ������ �Ͼ ���� ���� Ű�� ���� ������ �̺�Ʈ�� ó���Ѵ�.
//2. Ű �Է��� ���� �̺�Ʈ�� ���� ó���� �� �ִ�. : TAP, HOLD, AWAY, NONE