#pragma once
class CBombExplode
{
public:
	CBombExplode();
	~CBombExplode();
	void Init(TSTRING);
	void Draw();
	void Update();
	void ReSet(int,int,int,int,int,int);
	void SetDesPos(POINT);
	void SetIsExplode(bool);
	void UpdateRect();
	void SetDamage(int);
	RECT GetRect();
	bool GetIsExplode();
	POINT GetPos();
	int GetDamage();
	int GetCurFrame();
	int GetCurRow();
private:
	CSingleImg*m_pPic;
	bool m_isExplode;
	int m_curFrame;
	int m_curRow;
	int m_damage;
	POINT m_pos;
	RECT m_rc;
};

