#pragma once
class Res
{
	// ���ҽ��� �⺻������ �����ߵǴ� ����
	// File �̶�? : ���� ��� ��ġ�� ����� ���� �ִ� ������ ����
	// ���� : Ʈ�� ���� ���͸�
private:
	//id
	//��� ��� : ���� �����ϴ� ���͸� ���
	wstring		key;					// ���� ID
	wstring		strRelativePath;		// ���ҽ� ��� ��� (���� ���� ���� ������ �ʴ� �κ�)
public:
	Res();
	~Res();

	void			SetKey(const wstring _key) { key = _key; }
	void			SetPath(const wstring& _str) { strRelativePath = _str; }

	const wstring&	GetKey() { return key; }
	const wstring&	Getpath() { return strRelativePath; }
};