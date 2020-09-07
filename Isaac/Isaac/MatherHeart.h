#pragma once
class CMatherHeart
{
public:
	CMatherHeart();
	~CMatherHeart();
	void Init(TSTRING);
	void Draw();
	void Update();
	void SetVisible(bool);
	void SetMapIndex(int);
	void SetHp(int);
	void SetIsRed(bool);
	void SetDamage(int);
	void SetPos(POINT);
	void UpdateMahterRc();
	void ReSet(int,int,int,int,int,int);
	RECT GetMatherRc();
	POINT GetPos();
	int GetDamage();
	bool GetIsRed();
	int GetHp();
	int GetMapIndex();
	int GetCurFrame();
	int GetCurRow();
	bool GetVisible();
private:
	CSingleImg*m_pPic;
	bool m_visible;
	int m_mapIndex;
	int m_hp;
	int m_damage;
	int m_updateCount;
	bool m_isRed;
	POINT m_pos;
	RECT m_rc;
	int m_dir;
};

