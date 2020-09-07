#pragma once
class CStaticImg:public CRes
{
public:
	CStaticImg();
	~CStaticImg();
	void Init();
	void Draw();
	void ReadTileMap(const char*);
	void DrawTileMap(POINT);
	void SetTile(int, int, int);
	WORD GetPicWidth();
	WORD GetPicHeight();
	int GetTile(int,int);
private:
	CPicture*m_pPic;
	int** m_pMap;
	int *m_map;
	int m_row;
	int m_col;
	int m_tileWidth;
	int m_tileCount;
};

