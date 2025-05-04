#include "pch.h"
#include "Scene.h"

#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++i) {
			delete arrObj[i][j];
		}
	}
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++i) {
			arrObj[i][j]->Update();
		}
	}
}

void Scene::Render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++i) {
			arrObj[i][j]->Render(_hdc);
		}
	}
}

void Scene::Enter()
{
}

void Scene::Exit()
{
}
