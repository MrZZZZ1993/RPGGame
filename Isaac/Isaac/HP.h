#pragma once
class CHP:public CGoods
{
public:
	CHP();
	~CHP();
	void Function();
	void UpdateRc();
	void Move();
	void SetSrcPos(POINT);
private:
	int m_count;
};

