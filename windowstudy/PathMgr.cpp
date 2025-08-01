#include "pch.h"
#include "PathMgr.h"

#include "Core.h"

PathMgr::PathMgr()
	: contentPath{}
{
}

PathMgr::~PathMgr()
{
}

void PathMgr::Init()
{
	GetCurrentDirectory(255, contentPath);

	int len = wcslen(contentPath);
	for (int i = len - 1; 0 <= i; --i) {
		if ('\\' == contentPath[i]) {
			contentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(contentPath, 255, L"//bin//Content//");
	SetWindowText(Core::Instance()->getMainHandle(), contentPath);
}
