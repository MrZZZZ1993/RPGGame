#pragma once
class CInputManager:public CSingleton<CInputManager>
{
public:
	CInputManager();
	~CInputManager();
	void AddKeyListener(TSTRING, CKeyListener*);
	void AddMouseListener(TSTRING, CMouseListener*);
	void DeleteKeyListener(TSTRING);
	void DeleteMouseListener(TSTRING);
	void WinProc(UINT, WPARAM, LPARAM);
	CKeyListener*GetKeyListener(TSTRING);
	CMouseListener*GetMouseListener(TSTRING);
private:
	map<TSTRING, CKeyListener*>m_keyListener;
	map<TSTRING, CMouseListener*>m_mouseListener;
	map<TSTRING, CKeyListener*>::iterator m_keyIter;
	map<TSTRING, CMouseListener*>::iterator m_mouseIter;
};

