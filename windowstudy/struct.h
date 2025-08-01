#pragma once

struct Vec2 {
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float len = Length();

		// 에러 검출용 분모가 0이 안되도록 (디버깅 창에서 뜸 오류가)
		assert(len != 0.f);

		x /= len;
		y /= len;

		return *this;
	}

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2() : x(0.f)
			,y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		:x((float)_x)
		,y((float)_y)
	{}

	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};