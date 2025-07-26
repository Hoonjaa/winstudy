#pragma once

class Scene;

class SceneMgr{
	SINGLE(SceneMgr);

private:
	Scene* arrScene[(UINT)SCENE_TYPE::END];
	Scene* currScene;

public:
	void Init();
	void Update();
	void Render(HDC _hdc);

	Scene* GetCurScene() { return currScene; }
};

