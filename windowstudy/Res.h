#pragma once
class Res
{
	// 리소스가 기본적으로 가져야되는 정보
	// File 이란? : 보조 기억 장치에 저장된 관련 있는 정보의 집합
	// 폴더 : 트리 구조 디렉터리
private:
	//id
	//상대 경로 : 현재 시작하는 디렉터리 경로
	wstring		key;					// 고유 ID
	wstring		strRelativePath;		// 리소스 상대 경로 (실행 파일 기준 변하지 않는 부분)
public:
	Res();
	~Res();

	void			SetKey(const wstring _key) { key = _key; }
	void			SetPath(const wstring& _str) { strRelativePath = _str; }

	const wstring&	GetKey() { return key; }
	const wstring&	Getpath() { return strRelativePath; }
};