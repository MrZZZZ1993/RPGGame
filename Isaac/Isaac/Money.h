#pragma once
class CMoney
{
public:
	CMoney();
	~CMoney();
	void Init();
	void Draw();
	void Update();
	void SetVisible(bool);
	void UpdateRc();
	void SetPos(POINT);
	void SetMapIndex(int);
	void SetVisibleOnMap(bool);
	void SetVisiblePlayer(bool);
	void SetCurFrame(int);
	bool GetVisible();
	bool GetVisibleOnMap();
	bool GetVisiblePlayer();
	int GetMapIndex();
	RECT GetRc();
	POINT GetPoint();
private:
	CSingleImg*m_pPic;
	bool m_visible;
	bool m_visibleOnMap;
	bool m_visiblePlayer;
	RECT m_rc;
	POINT m_pos;
	int m_mapIndex;
};

