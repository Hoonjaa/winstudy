#include "pch.h"
#include "Texture.h"

#include "Core.h"

Texture::Texture()
	:hdc(0)
	,bit(0)
	,info{}
{
}

Texture::~Texture()
{
	DeleteDC(hdc);
	DeleteObject(bit);
}

void Texture::Load(const wstring& _str)
{
	bit = (HBITMAP)LoadImage(nullptr, _str.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(bit);

	// 비트맵이랑 열결할 DC
	hdc = CreateCompatibleDC(Core::Instance()->GetMainDC());

	// 비트맵 DC 연결
	HBITMAP preBit = (HBITMAP)SelectObject(hdc, bit);
	DeleteObject(preBit);

	// 가로 세로 길이
	GetObject(bit, sizeof(BITMAP), &info);
}
