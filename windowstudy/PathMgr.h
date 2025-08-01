#pragma once

// Debug vs Release
// 디버그 : 게임 배포하기 전에 개발 단계에서 디버깅 용이한 애고
// 릴리즈 : 배포 버전

class PathMgr
{
	SINGLE(PathMgr);
private:
	wchar_t			contentPath[255];

public:
	void			Init();
	const wchar_t*	GetContentPath() { return contentPath; }
};

