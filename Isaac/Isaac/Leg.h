#pragma once
class CLeg:public CGoods
{
public:
	CLeg();
	~CLeg();
	void InitLeg();
	void Function();
	void UpdateRc();
	void Move();
	void SetLegSpeed(int);
	void UpdateLegRc();
	void SetIsMove(bool);
	void SetAimPos(POINT);
	void SetDamage(int);
	void MoveOnMap();
	void SetDirOnMap(int);
	int GetDamage();
	RECT GetLegRc();
	bool GetLegVisible();
	bool GetIsMove();
private:
	CStaticImg*m_pLeg;
	bool m_legVisible;
	bool m_isMove;
	POINT m_aimPos;
	POINT m_legPos;
	int m_legSpeed;
	int m_dir;
	int m_count;
	int m_damage;
	int m_dirOnMap;
	RECT m_legRc;
};

