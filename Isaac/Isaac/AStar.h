#pragma once
class CAStar
{
public:
	CAStar();
	~CAStar();
	void Init(const char*);
	void Process(int,int,CNode*);
	void FindWay(CNode*);
	void Father(int, int, CNode*, CNode*);
	void XFather(int,int,int,int, CNode*);
	void SetOC(int i,int j);
	void Show();
	void Clear();
	void ReSet();
	CNode* FindNode(int, int);
private:
	int m_row;
	int m_col;
	CNode**m_node;
	int *m_map;
	CNode*m_pNode;
	CNode*m_temp;
};

