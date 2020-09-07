#pragma once
class CDoor
{
public:
	CDoor();
	~CDoor();
	void Init(TSTRING);
	void Draw();
	void Update();
	void ReSet(WORD,WORD,WORD,WORD,WORD,WORD);
	void SetDesPos(POINT);
	void SetDoorIndex(int);
	void SetSrcPos(POINT);
	void SetPos(POINT);
	void SetDoorType(int);
	void MoveOnMap();
	void UpdateRect();
	void SetVisible(bool);
	void SetDir(int);
	int GetFrameWidth();
	int GetFrameHeight();
	int GetDoorType();
	int GetDoorIndex();
	int GetCurFrame();
	int GetCurRow();
	POINT GetDesPos();
	bool GetVisible();
private:
	CSingleImg*m_door;
	int m_doorIndex;
	int m_doorType;
	POINT m_pos;
	bool m_visible;
	int m_dirOnMap;
};

