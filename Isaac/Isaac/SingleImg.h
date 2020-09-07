#pragma once
class CSingleImg:public CRes
{
public:
	CSingleImg();
	~CSingleImg();
	void Init();
	void Draw();
	void Update();
	void SetCountRow(WORD);
	void SetCurRow(WORD);
	void SetCountFrame(WORD);
	void SetCurFrame(WORD);
	void UpdateSrcPos(WORD,WORD);
	void SetStartRow(WORD);
	void SetStartFrame(WORD);
	void SetEndFrame(WORD);
	void SetEndRow(WORD);
	void ReSet(WORD, WORD, WORD, WORD, WORD, WORD);
	DWORD GetColorValue(POINT);
	WORD GetCountRow();
	WORD GetCurRow();
	WORD GetCountFame();
	WORD GetCurFrame();
	WORD GetFrameHeight();
	WORD GetFrameWidth();
	WORD GetPicWidth();
	WORD GetPicHeight();
private:
	CPicture*m_pPic;
	WORD m_countRow;
	WORD m_curRow;
	WORD m_countFrame;
	WORD m_curFrame;
	WORD m_frameHeight;
	WORD m_frameWidth;
	WORD m_startFrame;
	WORD m_startRow;
	WORD m_endFrame;
	WORD m_endRow;
};

