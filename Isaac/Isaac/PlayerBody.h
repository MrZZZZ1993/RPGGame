#pragma once
class CPlayerBody:public CKeyListener,public CPlayer
{
public:
	CPlayerBody();
	~CPlayerBody();
	void Init(TSTRING);
	void InitShadow(TSTRING);
	void Draw();
	void DrawShadow();
	void Update();
	void OnKeyDown(SEvent);
	void OnKeyUp(SEvent);
	void SetUpdateRate(WORD);
	void UpdateBodyRect();
	void UpdateBodyCollision();
	RECT GetBodyRect();
	RECT GetBodyCollision();
private:
	CStaticImg*m_pPlayerShadow;
	WORD m_updateRate;
	WORD m_count;
	RECT m_bodyRect;
	RECT m_bodyRectCollision;
};

