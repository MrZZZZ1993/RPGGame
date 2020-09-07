#pragma once
class CBullet
{
public:
	CBullet();
	~CBullet();
	void Init(TSTRING);
	void Draw();
	void Update();
	void UpdateMAatrix();
	void Move(Map*,int,int);
	void PathMove();
	void SetPath(D3DXVECTOR2);
	void SetPos(POINT);
	void SetVisible(BOOL);
	void SetDistance(WORD);
	void SetDamage(WORD);
	void SetSpeed(WORD);
	void SetBulletDir(int);
	void SetKeyUpDir(int);
	void UpdateBulletRect();
	void UpdateBigRc();
	void Refresh(WORD, WORD, WORD, WORD, WORD, WORD );
	void SetIsExplode(bool);
	void SetDesPos(POINT);
	bool StopExplode();
	bool GetIsExplode();
	void SetTop(Map*,int,int);
	void SetBottom(Map*,int,int);
	void SetLeft(Map*,int,int);
	void SetRight(Map*,int,int);
	void SetCurRow(WORD);
	DWORD GetColorValue(POINT);
	WORD GetCurFrame();
	WORD GetCurRow();
	WORD GetSpeed();
	POINT GetPos();
	BOOL GetVisible();
	WORD GetDistance();
	WORD GetDamage();
	RECT GetBulletRect();
	bool GetBottom();
	bool GetTop();
	bool GetLeft();
	bool GetRight();
	int GetDir();
private:
	CSingleImg*m_pBullet;
	POINT m_pos;
	BOOL m_bVisible;
	bool m_bIsExplode;
	WORD m_distance;
	WORD m_damage;
	WORD m_speed;
	int m_bulletDir;
	RECT m_bulletRect;
	bool top;
	bool bottom;
	bool left;
	bool right;
	int m_curFrame;
	int m_curRow;
	D3DXVECTOR2 m_vec;
};

