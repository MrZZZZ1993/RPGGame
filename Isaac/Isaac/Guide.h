#pragma once
class CGuide
{
public:
	CGuide();
	~CGuide();
	void Init(TSTRING);
	void DrawFrame();
	void DrawTile();
	void Update();
	void SetDesPos(POINT);
	void SetShowWidth(int);
	void SetShowHeight(int);
	void SetSrcPos(POINT);
	void SetMapIndex(int);
	void SetState(int);
	int GetState();
	int GetMapIndex();
	POINT GetPos();
private:
	CSingleImg*m_pPic;
	CSingleImg*m_pFrame;
	int m_mapIndex;
	POINT m_desPos;
	POINT m_srcPos;
	int m_state;
};

