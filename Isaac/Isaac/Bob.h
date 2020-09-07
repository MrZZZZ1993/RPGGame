#pragma once
class CBob
{
public:
	CBob();
	~CBob();
	void Init(TSTRING);
	void InitAStar(const char*);
	void Draw();
	void Update();
	void SetMapIndex(int);
	void SetSpeed(int);
	void SetVisible(bool);
	void SetPos(POINT);
	void SetDamage(int);
	void AStarMove(Map*);
	void ReSet(int,int,int,int,int,int);
	void MoveOnMap();
	void SetDir(int);
	void SetAnddColor(long);
	void SetHP(int);
	void UpdateRect();
	void SetIsRed(bool);
	bool GetIsRed();
	POINT GetPos();
	bool GetVisible();
	int GetSpeed();
	int GetMapIndex();
	int GetDamage();
	int GetHp();
	long GetAddColor();
	RECT GetHeadRect();
	RECT GetBodyRect();
private:
	CSingleImg*m_pHead;
	CSingleImg*m_pBody;
	int m_mapIndex;
	int m_speed;
	POINT m_pos;
	POINT m_headPos;
	bool m_visible;
	int m_damage;
	int m_dirOnMap;
	CAStar star;
	CNode*temp;
	CNode*temp1;
	D3DXVECTOR2 vecPlayer;
	D3DXVECTOR2 vecFly;
	POINT playerPos;
	int AStarCount;
	int m_dir;
	int m_leftCount;
	int m_rightCount;
	int m_hp;
	RECT m_headRc;
	RECT m_bodyRc;
	bool m_isRed;
	int m_updateCount;
};

