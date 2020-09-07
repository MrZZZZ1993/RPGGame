#pragma once
class CHeart
{
public:
	CHeart();
	~CHeart();
	void Init(TSTRING);
	void Draw();
	void Update();
	void SetDesPos(POINT);
	void SetSrcPos(POINT);
	int GetFrameWidth();
private:
	CSingleImg*m_pPic;
	POINT m_desPos;
	POINT m_srcPos;
};

