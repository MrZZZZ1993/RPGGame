#pragma once
class Map
{
public:
	Map();
	~Map();
	void Init(TSTRING);
	void Draw();
	void InitTileMap(const char*);
	void DrawTileMap(POINT);
	void Update();
	void UpdateMAatrix();
	void SetShowWidth(WORD);
	void SetShowHeight(WORD);
	void SetMapDir(int);
	void SetDesPos(POINT);
	void SetSrcPos(POINT);
	void SetMap(int, int, int);
	void SetMapIndex(int);
	void SetMapType(int);
	void SetScale(float, float);
	void SetCenter(int, int);
	void SetMove(int, int);
	void SetAngle(float);
	void SetTransparent(long);
	void SetVisible(bool);
	bool GetVisible();
	int GetMap(int,int);
	int GetMapType();
	int GetMapIndex();
	WORD GetWidth();
	WORD GetHeight();
	POINT GetSrcPos();
	POINT GetDesPos();
private:
	CStaticImg*m_pMap;
	int m_mapDir;
	int m_mapIndex;
	int m_mapType;
	bool m_visible;
};

