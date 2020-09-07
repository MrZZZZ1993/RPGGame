#pragma once
class CMonsterDead
{
public:
	CMonsterDead();
	~CMonsterDead();
	void Init(TSTRING);
	void Draw();
	void Update();
	void SetIsDead(bool);
	void SetPos(POINT);
	bool GetIsDead();
	POINT GetPos();
private:
	CSingleImg*m_pPic;
	bool m_isDead;
	POINT m_pos;
	int m_curFrame;
	int m_curRow;
};

