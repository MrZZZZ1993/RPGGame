#pragma once
class CNode
{
public:
	CNode();
	~CNode();
	void SetG(int);
	void SetH(int);
	void SetF(int);
	void SetOC(int);
	void SetFather(CNode*);
	void SetX(int);
	void SetY(int);
	void SetCON(int);
	int GetX();
	int GetY();
	int G(CNode);
	int H(CNode, CNode);
	int GetG();
	int GetH();
	int GetOC();
	int GetCON();
	int GetF();
	CNode*GetFather();
private:
	int m_x;//地图的X坐标
	int m_y;//地图的Y坐标
	int m_F;
	int m_G;//实际值
	int m_H;//行列
	int m_con;//是否是障碍，1代表不是，0代表是
	int m_oc;	//是否在列表中的标记量，1为在列表中  2在关闭列表中
	CNode* m_father;//父节点
};

