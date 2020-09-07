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
	tempCurNode->SetOC(2);//����ر��б���ʼ׼�������ܱ߽ڵ�
	CNode*temp;

	temp = FindNode(x + 1, y);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x + 1, y, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x - 1, y, x, y, tempEnd);
	}

	temp = FindNode(x, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x, y - 1, x, y, tempEnd);
	}

	temp = FindNode(x + 1, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x + 1, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x + 1, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x + 1, y - 1, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y + 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x - 1, y + 1, x, y, tempEnd);
	}

	temp = FindNode(x - 1, y - 1);
	if (temp != nullptr && temp->GetCON() == 32 && temp->GetOC() != 2)//Ϊ���ϰ������Ҳ��ڹر��б���
	{
		XFather(x - 1, y - 1, x, y, tempEnd);
	}
	//�����ڽ��������һ�ж�
}

void CAStar::XFather(int grid_x, int grid_y, int temp_x, int temp_y, CNode* tempEnd)
{
	CNode *g_temp, *temp, *xtemp;
	int g;
	g_temp = FindNode(grid_x, grid_y);
	temp = FindNode(temp_x, temp_y);
	if (g_temp != NULL)
	{
		if (g_temp->GetOC() != 1)//�����ж��б���
		{
			//��ӵ��ж��б���
			g_temp->SetOC(1);
			g_temp->SetFather(temp);
			Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//����Fֵ
		}
		else if (g_temp->GetOC() == 1)//�Ѿ����ж��б���
		{
			xtemp = g_temp->GetFather();//�����ϸ��ڵ�
			g = g_temp->GetG();//���浽�ϸ��ڵ��Gֵ
			g_temp->SetFather(temp);//��Ŀ��ڵ�ĸ��ڵ㸳ֵΪ��ǰ�ڵ�
			Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//���¼���G/Fֵ
			if (g_temp->GetG()>g)//�ж��¼������Gֵ�Ƿ����ԭ�����ϸ��ڵ�·����Gֵ
			{
				g_temp->SetFather(xtemp); //����ϸ��ڵ��Gֵ��С����ֵ ��ԭ�����ϸ��ڵ�
				Process(g_temp->GetX(), g_temp->GetY(), tempEnd);//Gֵ���¼���
			}
		}
	}
}

void CAStar::FindWay(CNode*tempEnd)
{
	int x, y;
	while (tempEnd->GetOC() != 1)//ֻҪ�յ�ڵ�û�ڿ����б������Ѱ��
	{
		m_temp->SetF(10000);//��ʱ�ڵ㣬���ڱ������п����б���Fֵ��С�Ľڵ�
		for (int i = 0; i<m_row; i++)
		{
			for (int j = 0; j<m_col; j++)
			{
				if (m_node[i][j].GetOC()==1)//�ڿ����б���
				{
					if (m_node[i][j].GetF() <= m_temp->GetF())
						m_temp = &m_node[i][j];
				}
			}
		}
		Father(m_temp->GetX(), m_temp->GetY(), m_temp, tempEnd);//��չ�ܱ߽ڵ�
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