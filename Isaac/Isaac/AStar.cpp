#include "stdafx.h"
#include "AStar.h"


CAStar::CAStar(void)
{
	m_temp = new CNode;
}

CAStar::~CAStar(void)
{
	for(int i=0;i<m_row;i++)
		delete[] m_node[i];
	delete[] m_node;
	delete m_temp;
	delete[] m_map;
	delete m_pNode;
}

void CAStar::Clear()
{
	for (int i = 0; i<m_row; i++)
		delete[] m_node[i];
	delete[] m_node;
}

void CAStar::Init(const char* filename)
{
	FILE *file;

	int tileWidth, tileCount;
	fopen_s(&file, filename, "rb+");
	fread(&m_row, sizeof(int), 1, file);

	fread(&m_col, sizeof(int), 1, file);

	fread(&tileWidth, sizeof(int), 1, file);

	fread(&tileCount, sizeof(int), 1, file);

	m_map = new int[m_row*m_col];
	fread(&m_map[0], sizeof(int), m_row*m_col, file);
	fclose(file);

	int count = 0;
	m_node = new CNode*[m_row];
	for (int i = 0; i < m_row; i++)
		m_node[i] = new CNode[m_col];
	
	for (int i = 0; i<m_row; i++)
	{
		for (int j = 0; j<m_col; j++)
		{
			m_node[i][j].SetX(i);
			m_node[i][j].SetY(j);
			m_node[i][j].SetCON(m_map[count]);
			m_node[i][j].SetOC(0);
			m_node[i][j].SetF(10000);
			m_node[i][j].SetFather(nullptr);
			count++;
		}
	}
}

void CAStar::Process(int x,int y,CNode*node)
{
	CNode *temp;
	temp = FindNode(x, y);
	if (temp != NULL)
	{
		temp->SetH(temp->H(*temp,*node));
		temp->SetG(temp->G(*temp));
		temp->SetF(temp->GetG()+temp->GetH());
	}
}

void CAStar::Father(int x, int y, CNode* tempCurNode, CNode* tempEnd)
{
	tempCurNode->SetOC(2);//加入关闭列表，开始准备搜索周边节点
	CNode*temp;

	temp = FindNode(x + 1, y);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x + 1, y, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x - 1, y, x, y, tempEnd);
	}

	temp = FindNode(x, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x, y - 1, x, y, tempEnd);
	}

	temp = FindNode(x + 1, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x + 1, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x + 1, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x + 1, y - 1, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x - 1, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//为非障碍，并且不在关闭列表中
	{
		XFather(x - 1, y - 1, x, y, tempEnd);
	}
	//所有邻近块进行逐一判断
}

void CAStar::XFather(int grid_x, int grid_y, int temp_x, int temp_y, CNode* tempEnd)
{
	CNode *g_temp, *temp, *xtemp;
	int g;
	g_temp = FindNode(grid_x, grid_y);
	temp = FindNode(temp_x, temp_y);
	if (g_temp != NULL)
	{
		if (g_temp->GetOC() != 1)//不在判断列表中
		{
			//添加到判断列表中
			g_temp->SetOC(1);
			g_temp->SetFather(temp);
			Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//计算F值
		}
		else if (g_temp->GetOC() == 1)//已经在判断列表当中
		{
			xtemp = g_temp->GetFather();//保存老父节点
			g = g_temp->GetG();//保存到老父节点的G值
			g_temp->SetFather(temp);//把目标节点的父节点赋值为当前节点
			Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//重新计算G/F值
			if (g_temp->GetG()>g)//判断新计算出的G值是否大于原来走老父节点路径的G值
			{
				g_temp->SetFather(xtemp); //如果老父节点的G值更小，则赋值 回原来的老父节点
				Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//G值重新计算
			}
		}
	}
}

void CAStar::FindWay(CNode*tempEnd)
{
	int x, y;
	while (tempEnd->GetOC() != 1)//只要终点节点没在开启列表，则继续寻找
	{
		m_temp->SetF(10000);//临时节点，用于保存所有开启列表中F值最小的节点
		for (int i = 0; i<m_row; i++)
		{
			for (int j = 0; j<m_col; j++)
			{
				if (m_node[i][j].GetOC()==1)//在开启列表中
				{
					if (m_node[i][j].GetF() <= m_temp->GetF())
						m_temp = &m_node[i][j];
				}
			}
		}
		Father(m_temp->GetX(), m_temp->GetY(), m_temp, tempEnd);//扩展周边节点
	}
}

CNode* CAStar::FindNode(int x, int y)
{
	if (x<0 || y<0 || x>m_row-2 || y>m_col-2)
		return nullptr;
	else
		return &m_node[x][y];
}

void CAStar::SetOC(int i,int j)
{
	m_node[i][j].SetOC(1);
}

void CAStar::Show()
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			cout <<m_node[i][j].GetCON() << " ";
		}
		cout << endl;
	}

}

void CAStar::ReSet()
{
	int count=0;
	for (int i = 0; i<m_row; i++)
	{
		for (int j = 0; j<m_col; j++)
		{
			m_node[i][j].SetX(i);
			m_node[i][j].SetY(j);
			m_node[i][j].SetCON(m_map[count]);
			m_node[i][j].SetOC(0);
			m_node[i][j].SetF(10000);
			m_node[i][j].SetFather(nullptr);
			count++;
		}
	}
	m_node[4][6].SetCON(1);
}