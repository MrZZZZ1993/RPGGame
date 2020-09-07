#pragma once
class CEnd
{
public:
	CEnd();
	~CEnd();
	void Init();
	void Draw();
	void DrawLost();
	void Update();
	void SetVisible(bool);
	void Move();
	void SetMapIndex(int);
	void UpdateRc();
	void End();
	void SetVisibleOmMap(bool);
	RECT GetRc();
	int GetMapIndex();
	int GetCurFrame();
	bool GetVisible();
	bool GetVisibleOnMap();
	bool GetIsdead();
	POINT GetPos();
private:
	CSingleImg*m_pPic;
	CStaticImg*m_pLost;
	bool m_visible;
	bool m_isUpdate;
	bool m_visibleOnMap;
	bool m_isdead;
	int m_mapIndex;
	int count;
	POINT m_pos;
	RECT m_rc;
};

