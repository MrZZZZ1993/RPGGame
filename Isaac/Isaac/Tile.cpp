#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
	m_pPic = nullptr;
	m_mapIndex = 0;
	m_speed = 0;
	m_countPoint=0;
	m_endPoint=0;
}

CTile::~CTile()
{
	delete m_pPic;
}

void CTile::Init(TSTRING name)
{
	m_pPic = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->UpdateMAatrix();
}

void CTile::Draw()
{
	if(m_visible)
	{
		m_pPic->SetDesPos(m_pos);
		m_pPic->Draw();
	}
}

void CTile::Update()
{
	m_pPic->Update();
}

void CTile::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CTile::SetPos(POINT pos)
{
	m_pos = pos;
}

void CTile::UpdateTileRect()
{
	int x = m_pos.x + 16;
	int y = m_pos.y + 13;
	m_rc.left = x;
	m_rc.top = y;
	m_rc.right = x + 64;
	m_rc.bottom = y + 60;
}

void CTile::SetSpeed(int speed)
{
	m_speed = speed;
}

void CTile::Move()
{
	
	endPos.x = aimPoint[m_countPoint].x;
	endPos.y = aimPoint[m_countPoint].y;
	tilePos.x = m_pos.x;
	tilePos.y = m_pos.y;
	D3DXVECTOR2 vec = endPos - tilePos;
	D3DXVec2Normalize(&vec, &vec);

	float fDist = D3DXVec2Length(&(endPos - tilePos));

	if (m_speed >= fDist)
	{
		tilePos = endPos;
		m_countPoint++;
		if(m_countPoint==m_endPoint)
			m_countPoint=0;
	}
	else
	{
		tilePos += vec*m_speed;
	}
	m_pos.x = tilePos.x;
	m_pos.y = tilePos.y;
}

void CTile::SetPoint(POINT pos1,POINT pos2,POINT pos3,POINT pos4)
{
	aimPoint[0]=pos1;
	aimPoint[1]=pos2;
	aimPoint[2]=pos3;
	aimPoint[3]=pos4;
}

void CTile::SetVisible(bool b)
{
	m_visible=b;
}

void CTile::SetDamage(int i)
{
	m_damage=i;
}

void CTile::ReSet(int curFrame,int curRow,int startFrame,int endFrame,int startRow,int endRow)
{
	m_pPic->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
}

void CTile::SetEndPoint(int i)
{
	m_endPoint=i;
}

int CTile::GetDamage()
{
	return m_damage;
}

int CTile::GetMapIndex()
{
	return m_mapIndex;
}

RECT CTile::GetTileRect()
{
	return m_rc;
}

POINT CTile::GetPos()
{
	return m_pos;
}

bool CTile::GetVisible()
{
	return m_visible;
}