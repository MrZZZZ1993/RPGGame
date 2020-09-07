#pragma once
class CFeceMonster
{
public:
	CFeceMonster();
	~CFeceMonster();
	void Init(TSTRING);
	void Draw();
	void Update();
	void Move(Map*);
	void UpdateAim();
	void SetVisible(bool);
	void SetHp(int);
	void SetDamage(int);
	void SetPos(POINT);
	void SetMapIndex(int);
	void SetIsRed(bool);
	void UpdateAimPos();
	void SetSpeed(int);
	void UpdateRc();
	int GetSpeed();
	bool GetIsRed();
	POINT GetPos();
	int GetHp();
	int GetDamage();
	bool GetVisible();
	int GetMapIndex();
	RECT GetRc();
private:
	CSingleImg*m_pPic;
	int m_hp;
	int m_damage;
	int m_state;
	int m_curFrame;
	int m_curRow;
	int m_dir;
	int m_mapIndex;
	int m_updateCount;
	int m_speed;
	D3DXVECTOR2 aimPos;
	bool m_visible;
	bool m_isRed;
	POINT m_pos;
	bool m_isUpdate;
	int m_count;
	RECT m_rc;
};

