#include "pch.h"
#include "Player.h"

#include "Missile.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Core.h"

#include "KeyMgr.h"
#include "TimeMgr.h"

#include "Texture.h"
#include "PathMgr.h"

Player::Player()
	:tex(nullptr)
{
	// Texture Loading
	tex = new Texture;
	wstring strPath = PathMgr::Instance()->GetContentPath();
	strPath += L"Texture\\Player.bmp";
	tex->Load(strPath);
}

Player::~Player()
{
	if (nullptr != tex)
		delete tex;
}

void Player::Update()
{
	Vec2 vPos = getPos();

	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * DT;
	}
	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * DT;
	}
	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * DT;
	}
	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * DT;
	}
	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}
	setPos(vPos);
}

void Player::Render(HDC _hdc)
{
	int width = (int)tex->Width();
	int height = (int)tex->Height();

	Vec2 vPos = getPos();

	vPos.x - (float)(width / 2);
	vPos.y - (float)(height / 2);

	TransparentBlt(_hdc
		, int(vPos.x - (float)(width / 2))
		, int(vPos.y - (float)(height / 2))
		, width
		, height
		, tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));
}

void Player::CreateMissile()
{
	Vec2 missilePos = getPos();
	missilePos.y -= getScale().y / 2.f;

	Missile* missile = new Missile;
	missile->setPos(missilePos);
	missile->setScale(Vec2(25.f, 25.f));
	missile->SetDir(Vec2(-1.f, -7.f));	//여기서 지정이 가능하다

	//현재 씬을 얻어와
	Scene* curScenes = SceneMgr::Instance()->GetCurScene();
	curScenes->AddObject(missile, GROUP_TYPE::DEFAULT);
}