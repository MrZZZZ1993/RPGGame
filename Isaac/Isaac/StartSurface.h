#pragma once
class CStartSurface:public CKeyListener
{
public:
	CStartSurface();
	~CStartSurface();
	void Init();
	void Draw();
	void Update();
	void OnKeyDown(SEvent);
private:
	CSingleImg *m_pFly;
	CSingleImg*m_pBoy;
	CStaticImg*m_pLogo;
	CStaticImg*m_pBg;
	WORD m_count;
	int m_speed;
	float m_angle;
	float m_preAngle;
	bool dir;
	int count;
	int countAngle1;
	int m_updateRate;
};

