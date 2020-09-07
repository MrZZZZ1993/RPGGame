#pragma once
class CMulImg:public CRes
{
public:
	CMulImg();
	~CMulImg();
	void Init();
	void InitPath();
	void Draw();
	void Update();
	void SetCountFrame(WORD);
	void SetCurFrame(WORD);
	void SetPath(TSTRING, WORD);
	WORD GetCountFrame();
	WORD GetCurFrame();
private:
	CPicture**m_pPic;
	WORD m_countFrame;
	WORD m_curFrame;
	TSTRING*m_path;
};

