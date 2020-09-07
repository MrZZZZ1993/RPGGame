#include "stdafx.h"
#include "Node.h"

CNode::CNode()
{
}

CNode::~CNode()
{

}

void CNode::SetG(int g)
{
	m_G = g;
}

void CNode::SetH(int h)
{
	m_H = h;
}

void CNode::SetF(int f)
{
	m_F = f;
}

void CNode::SetOC(int i)
{
	m_oc = i;
}

void CNode::SetFather(CNode*node)
{
	m_father = node;
}

void CNode::SetX(int x)
{
	m_x = x;
}

void CNode::SetY(int y)
{
	m_y = y;
}

void CNode::SetCON(int con)
{
	m_con = con;
}

int CNode::GetX()
{
	return m_x;
}

int CNode::GetY()
{
	return m_y;
}

int CNode::G(CNode node)
{
	int g = 0;
	CNode *temp;
	temp = &node;
	while (temp->GetFather() != nullptr)
	{
		if (temp->GetX() != (temp->GetFather())->GetX() && temp->GetY() != (temp->GetFather())->GetY())
			g += 14;
		else
			g += 10;
		temp = temp->GetFather();
	}
	return g;
}

int CNode::H(CNode node, CNode endNode)
{
	CNode *temp;
	temp = &node;
	int h = 0;
	h = 10 * fabs((float)(temp->GetX() - endNode.GetX())) + 10 * fabs((float)(temp->GetY() - endNode.GetY()));
	return h;
}

int CNode::GetG()
{
	return m_G;
}

int CNode::GetH()
{
	return m_H;
}

int CNode::GetOC()
{
	return m_oc;
}

int CNode::GetCON()
{
	return m_con;
}

int CNode::GetF()
{
	return m_F;
}

CNode*CNode::GetFather()
{
	return m_father;
}