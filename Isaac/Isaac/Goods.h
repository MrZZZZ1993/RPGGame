#pragma once
class CGoods
{
public:
	CGoods();
	~CGoods();
	void Init(TSTRING);
	void Draw();
    virtual void Move();
	void SetPos(POINT);
	void SetVisible(bool);
	void SetShowWidth(int);
	void SetShowHeight(int);
	void SetMapIndex(int);
	void SetVisibleOnMap(bool);
	void SetIsUse(bool);
	bool GetIsUse();
	virtual void UpdateRc()=0;
	virtual void Function() = 0;
	int GetMapIndex();
	bool GetVisible();
	bool GetVisibleOnMap();
	POINT GetPos();
	RECT GetRc();
protected:
	int m_mapIndex;
	CStaticImg*m_pPic;
	bool m_visible;
	bool m_visibleOnMap;
	bool m_isUse;
	POINT m_pos;
	int m_dir;
	RECT m_rc;
};

