#pragma once
class CNewGame:public CKeyListener
{
public:
	CNewGame();
	~CNewGame();
	void Init();
	void Draw();
	void Update();
	void OnKeyDown(SEvent event);
private:
	CStaticImg*m_pNewGame;
	CStaticImg*m_pOption;
	int m_speed;
};

