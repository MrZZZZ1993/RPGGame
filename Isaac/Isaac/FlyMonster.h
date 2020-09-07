#pragma once
class CFlyMonster
{
public:
	CFlyMonster();
	~CFlyMonster();
	void Init(TSTRING);
	void Draw();
	void Update();
	void Move(Map*);
	void MoveOnMap();
	void SetDir(int);
	void SetPos(POINT);
	void SetDesPos(POINT);
	void SetSpeed(int);
	void SetHalfWidth(int);
	void SetAngleDir(D3DXVECTOR2);
	void SetMapIndex(int);
	void SetVisible(bool);
	void SetAddColor(long);
	void SetHP(int);
	void SetDamage(int);
	void UpdateFlyMonsterRect();
	void SetIsRed(bool);
	int GetDamage();
	int GetHP();
	int GetWidth();
	int GetFrameWidth();
	int GetMapIndex();
	bool GetVisible();
	long GetAddColor();
	bool GetIsRed();
	RECT GetFlyMonsterRect();
	int GetPosX();
	int GetPosY();
protected:
	CSingleImg*m_pPic;
	D3DXVECTOR2 m_pos;
	Line line[4];
	D3DXVECTOR2 point[5];
	D3DXVECTOR2 dir;
	int m_hp;
	float speed;
	float m_fHalfWidth;
	int m_dir;
	int m_mapIndex;
	bool m_visible;
	int m_damage;
private:
	RECT rc;
	bool m_isRed;
	int m_curFrame;
};

