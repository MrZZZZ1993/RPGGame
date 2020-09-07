#pragma once
class CResManager:public CSingleton<CResManager>
{
public:
	CResManager();
	~CResManager();
	void LoadResFromFile(TSTRING);
	void AddRes(TSTRING, CRes*);
	CRes*GetRes(TSTRING);
private:
	map<TSTRING, CRes*>m_res;
};

