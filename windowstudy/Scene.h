#pragma once

class Object;		//전방선언

class Scene{
private:
	wstring	strName;
	vector<Object*> arrObj[(UINT)GROUP_TYPE::END];

public:
	Scene();
	~Scene();

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	void Update();
	void Render(HDC _hdc);

	virtual void Enter()=0;
	virtual void Exit()=0;

protected:
	void AddObject(Object* obj, GROUP_TYPE type)
	{
		arrObj[(UINT)type].push_back(obj);
	}
};

