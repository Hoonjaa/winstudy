#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	Object* obj = new Object;

	obj->setPos(Vec2(604.f, 348.f));
	obj->setScale(Vec2(100.f, 100.f));

	AddObject(obj, GROUP_TYPE::DEFAULT);
}

void Scene_Start::Exit()
{
}
