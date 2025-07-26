#pragma once
class Object{
private:
	Vec2	vPos;
	Vec2	vScale;

public:
	Object();
	virtual ~Object();

	// interface함수
	//-> set, get
	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale() { return vScale; }

public:
	virtual void Update()=0;		//자식 클래스에서 재정의 = 0
	virtual void Render(HDC _hdc);
};