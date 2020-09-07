#pragma once
class CPlatform:public CSingleton<CPlatform>
{
public:
	CPlatform();
	~CPlatform();
	void AddPlatData(TSTRING, void*);
	void*GetPlatData(TSTRING);
private:
	map<TSTRING, void*>m_plat;
};

