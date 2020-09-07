#pragma once
class CMask
{
public:
	CMask();
	~CMask();
	void Init(TSTRING);
	void Draw();
	void Update();
	void SetDir(int);
	void SetMapIndex(int);
	void SetVisible(bool);
	void Move();
	void SetPos(POINT);
	void UpdateAim(POINT);
	void UpdateRc();
	void SetDamage(int);
	void SetHp(int);
	void SetNormalSpeed(int);
	void SetPursueSpeed(int);
	void SetIsRed(bool);
	bool GetIsRed();
	POINT GetPos();
	bool GetVisible();
	int GetMapIndex();
	int GetDir();
	int GetDamage();
	int GetHp();
	RECT GetRc();
protected:
	CSingleImg*m_pPic;
	bool m_visible;
	int m_dir;
	int m_mapIndex;
	int m_speedNormal;
	int m_speedPursue;
	int m_aimPos;
	int m_hp;
	int m_damage;
	bool m_isPursue;
	bool m_isUpdate;
	bool m_isRed;
	POINT m_pos;
	RECT m_rc;
};

