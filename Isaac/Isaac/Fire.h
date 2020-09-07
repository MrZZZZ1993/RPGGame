#pragma once
class CFire
{
public:
	CFire();
	~CFire();
	void Init();
	void Draw();
	void Update();
	void SetPos(POINT);
	void SetVisible(bool);
	void SetDir(int);
	void MoveOnMap();
	void SetMapIndex(int);
	void UpdateFireRect();
	void SetDamage(int);
	void SetVisibleOnMap(bool);
	int GetDamage();
	bool GetVisible();
	bool GetVisibleOnMap();
	POINT GetPos();
	int GetMapIndex();
	RECT GetFireRect();
private:
	CSingleImg*m_pUnder;
	CSingleImg*m_pFire;
	POINT m_pos;
	POINT m_underPos;
	int m_count;
	bool m_visible;
	bool m_visibleOnMap;
	RECT rc;
	int m_dirOnMap;
	int m_mapIndex;
	int m_damage;
	int m_curFrame;
};

