#pragma once
class CFly
{
public:
	CFly();
	~CFly();
	void Init(TSTRING);
	void Draw();
	void Update();
	void Move();
	void MoveOnMap();
	void SetDir(int);
	void SetPos(POINT);
	void SetDesPos(POINT);
	void SetSpeed(int);
	void SetMapIndex(int);
	void SetVisible(bool);
	void UpdateFlyRect();
	void ReSet(WORD, WORD, WORD, WORD, WORD, WORD);
	void SetHP(int);
	void SetIsDead(bool);
	void SetDamage(int);
	void AStarMove();
	int GetDamage();
	int GetHP();
	bool GetVisible();
	int GetMapIndex();
	RECT GetFlyRect();
	POINT GetPos();
private:
	CSingleImg*m_pFly;
	CSingleImg*m_pFlyDead;
	POINT m_pos;
	POINT m_deadPos;
	float m_targetAngle;
	float m_angle;
	int m_dir;
	int speed;
	int m_curFrame;
	int m_curRow;
	int m_curDeadFrame;
	int m_curDeadRow;
	bool m_visible;
	bool m_isDead;
	int m_mapIndex;
	int m_hp;
	int m_damage;
	RECT m_flyRect;


	CAStar star;
	CNode*temp;
	CNode*temp1;
	D3DXVECTOR2 vecPlayer;
	D3DXVECTOR2 vecFly;
	int AStarCount;
};

