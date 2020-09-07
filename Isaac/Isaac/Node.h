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
	int m_x;//��ͼ��X����
	int m_y;//��ͼ��Y����
	int m_F;
	int m_G;//ʵ��ֵ
	int m_H;//����
	int m_con;//�Ƿ����ϰ���1�����ǣ�0������
	int m_oc;	//�Ƿ����б��еı������1Ϊ���б���  2�ڹر��б���
	CNode* m_father;//���ڵ�
};

