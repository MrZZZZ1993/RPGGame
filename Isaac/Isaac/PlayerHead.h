#pragma once
class CPlayerHead:public CKeyListener,public CPlayer
{
public:
	CPlayerHead();
	~CPlayerHead();
	void Init(TSTRING);
	void Draw();
	void DrawOther();
	void DrawHoldGoods();
	void Update();
	void OnKeyDown(SEvent);
	void OnKeyUp(SEvent);
	void UpdateHeadRect();
	void UpdateHeadCollision();
	void SetAddColor(long);
	void SetHp(int);
	void SetCountHp(int);
	void SetIsHold(bool);
	int GetCountHp();
	int GetHp();
	RECT GetHeadRect();
	RECT GetHeadCollision();
	long GetAddColor();
	bool GetIsHold();
private:
	int m_hp;
	int m_countHp;
	WORD m_count;
	int m_bulletDir;
	bool IsFire;
	bool m_isHold;
	RECT m_headRect;
	RECT m_headRectCollision;
	CSingleImg*m_other;
};

