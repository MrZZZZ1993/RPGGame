#pragma once
class CFlyDuke:public CFlyMonster
{
public:
	CFlyDuke();
	~CFlyDuke();
	void InitFlyDuke();
	void UpdateDuke();
	void SetFireTime(int);
	void UpdateFlyDukeRect();
	void Dead();
	void SetIsDead(bool);
	int GetCurFrame();
	int GetCurRow();
	int GetPicWidth();
	int GetPicHeight();
	POINT GetPos();
	RECT GetDukeRect();
	DWORD GetColorValue(POINT);
	bool GetIsDead();
private:
	int m_deadcount;
	int m_countRate;
	int m_curFrame;
	int m_curRow;
	int m_UpdateCount;
	int m_fireTime;
	bool m_fire;
	bool m_isDead;
	RECT m_rectDuke;
};

