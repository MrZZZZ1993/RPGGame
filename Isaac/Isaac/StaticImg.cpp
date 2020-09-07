#include "stdafx.h"
#include "StaticImg.h"


CStaticImg::CStaticImg()
{
	m_pPic = nullptr;
}

CStaticImg::~CStaticImg()
{
	delete m_pPic;
	for(int i=0;i<m_row;i++)
		delete m_pMap[i];
	delete [] m_pMap;
	delete[] m_map;
}

void CStaticImg::Init()
{
	m_pPic = new CPicture;
	SetColRef(NULL);
	m_pPic->Init(GetPath(), GetColRef());
}

void CStaticImg::Draw()
{
	m_pPic->Draw(GetSrcPos(), GetDesPos(), GetShowWidth(), GetShowHeight(), matMatrix, m_center,m_transparent,m_addColor);
}

void CStaticImg::ReadTileMap(const char*filename)
{
	FILE *file;

	fopen_s(&file, filename, "rb+");
	fread(&m_row, sizeof(int), 1, file);

	fread(&m_col, sizeof(int), 1, file);

	fread(&m_tileWidth, sizeof(int), 1, file);
	
	fread(&m_tileCount, sizeof(int), 1, file);
	
	m_map = new int[m_row*m_col];
	fread(&m_map[0], sizeof(int), m_row*m_col, file);
	fclose(file);

	m_pMap = new int*[m_row];
	for (int i = 0; i<m_row; i++)
		m_pMap[i] = new int[m_col];

	int count=0;
	for (int i = 0; i<m_row; i++)
	{
		for (int j = 0; j<m_col; j++)
		{
			m_pMap[i][j]=m_map[count];
			count++;
		}
	}
}

void CStaticImg::DrawTileMap(POINT picSrcPos)
{
	for (int i = 0; i < m_row; i++)
	for (int j = 0; j < m_col; j++)
	{
		POINT desPos;
		desPos.x = j * m_tileWidth - picSrcPos.x;
		desPos.y = i * m_tileWidth - picSrcPos.y;
		POINT srcPos;
		srcPos.x = (m_pMap[i][j] - 1) % m_tileCount * m_tileWidth;
		srcPos.y = (m_pMap[i][j] - 1) / m_tileCount * m_tileWidth;
		m_pPic->Draw(srcPos, desPos, m_tileWidth, m_tileWidth, matMatrix, m_center,m_transparent,m_addColor);
	}
	m_pPic->SetPicWidth(m_col*m_tileWidth);
	m_pPic->SetPicHeight(m_row*m_tileWidth);
}

void CStaticImg::SetTile(int row, int col, int num)
{
	m_pMap[row][col] = num;
}

WORD CStaticImg::GetPicWidth()
{
	return m_pPic->GetPicWidth();
}

WORD CStaticImg::GetPicHeight()
{
	return m_pPic->GetPicHeight();
}

int CStaticImg::GetTile(int row,int col)
{
	return m_pMap[row][col];
}