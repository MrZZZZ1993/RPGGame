#pragma once
class CTransition
{
public:
	CTransition();
	~CTransition();
	void Init();
	void Draw();
	void Update();
	void SetStart(bool);
public:
	CStaticImg*m_pTransition;
	CStaticImg*m_pBlack;
	long m_transparent;
	bool m_start;
	int m_count;
	int m_startCount;
	int m_endCount;
};

