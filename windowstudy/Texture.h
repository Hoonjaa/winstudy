#pragma once
#include"Res.h"

class Texture : public Res
{
private:
	HDC			hdc;
	HBITMAP		bit;
	BITMAP		info;

public:
	Texture();
	~Texture();

	void		Load(const wstring& _str);
	UINT		Width() { return info.bmWidth; }
	UINT		Height() { return info.bmHeight; }

	HDC			GetDC() { return hdc; }
};

