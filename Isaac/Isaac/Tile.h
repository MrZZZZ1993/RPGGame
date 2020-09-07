#pragma once
class CTile
{
public:
	CTile();
	~CTile();
	void Init(TSTRING);
	void Draw();
	void Update();
	void SetPos(POINT);
	void SetMapIndex(int);
	void UpdateTileRect();
	void SetSpeed(int);
	void Move();
	void SetPoint(POINT,POINT,POINT,POINT);
	void SetVisible(bool);
	void SetDamage(int);
	void ReSet(int,int,int,int,int,int);
	void SetEndPoint(int);
	RECT GetTileRect();
	int GetMapIndex();
	int GetDamage();
	POINT GetPos();
	bool GetVisible();
private:
	CSingleImg*m_pPic;
	POINT m_pos;
	int m_mapIndex;
	RECT m_rc;
	int m_speed;
	POINT aimPoint[4];
	D3DXVECTOR2 endPos;
	D3DXVECTOR2 tilePos;
	int m_countPoint;
	int m_endPoint;
	bool m_visible;
	int m_damage;
};

