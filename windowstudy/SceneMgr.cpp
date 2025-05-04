#include "pch.h"
#include "SceneMgr.h"
#include "Scene_Start.h"

SceneMgr::SceneMgr()
	:arrScene()
	,currScene(nullptr)
{

}

SceneMgr::~SceneMgr()
{

}

void SceneMgr::Init()
{
	//Scene 생성
	arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	//arrScene[(UINT)SCENE_TYPE::STAGE_O1] = new Scene_Start;
	//arrScene[(UINT)SCENE_TYPE::STAGE_O2] = new Scene_Start;

	//현재 씬 지정
	currScene = arrScene[(UINT)SCENE_TYPE::START];
	currScene->Enter();
}

void SceneMgr::Update()
{
	currScene->Update();
}

void SceneMgr::Render(HDC _hdc)
{
	currScene->Render(_hdc);
}
