#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
	POINT pos={370,140};
	m_pos=pos;
	m_bVisible=false;
	m_distance=100;
	m_damage=0;
	m_speed=10;
	m_bIsExplode = false;
	top = false;
	bottom = false;
	left = false;
	right = false;
	m_curFrame=0;
	m_curRow=0;
	m_pBullet = nullptr;
}

CBullet::~CBullet()
{
	delete m_pBullet;
}

void CBullet::Init(TSTRING name)
{
	m_pBullet=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pBullet->Init();
	m_pBullet->SetShowWidth(m_pBullet->GetFrameWidth());
	m_pBullet->SetShowHeight(m_pBullet->GetFrameHeight());
	m_pBullet->ReSet(0,0,0,3,0,3);
	m_pBullet->UpdateMAatrix();
}

void CBullet::Draw()
{
	if (!m_bIsExplode)
	{
		POINT pos = { 0, 0 };
		m_pBullet->SetSrcPos(pos);
	}
	else
	{
		POINT pos={0,0};
		pos.x=m_curFrame*m_pBullet->GetFrameWidth();
		pos.y=m_curRow*m_pBullet->GetFrameHeight();
		m_pBullet->SetSrcPos(pos);
	}
	m_pBullet->SetDesPos(m_pos);
	m_pBullet->Draw();
}

void CBullet::Update()
{
	if(m_bIsExplode)
	{
		m_pBullet->SetCurFrame(m_curFrame);
		m_pBullet->SetCurRow(m_curRow);
		m_pBullet->Update();

		m_curFrame++;
		if(m_curFrame==3&&m_curRow!=3)
		{
			m_curFrame=0;
			m_curRow++;
			if(m_curRow==4)
				m_curRow=0;
		}


		if(m_curRow==3&&m_curFrame==3)
		{
			m_bIsExplode=false;
			m_bVisible=false;
			m_curFrame=0;
			m_curRow=0;
		}
	}
}

void CBullet::UpdateMAatrix()
{
	m_pBullet->UpdateMAatrix();
}

void CBullet::Move(Map*pMap,int tileWidth,int num)
{
	SetTop(pMap, tileWidth,num);
	SetBottom(pMap, tileWidth, num);
	SetLeft(pMap, tileWidth, num);
	SetRight(pMap, tileWidth, num);

	UpdateBulletRect();
	if (m_bVisible&&!m_bIsExplode)
	{
		switch (m_bulletDir)
		{
		case eNONE:
			break;
		case eUP:
			if (top)
			{
				m_pos.y -= m_speed;
				m_distance -= m_speed;
			}
			break;
		case eDOWN:
			if (bottom)
			{
				m_pos.y += m_speed;
				m_distance -= m_speed;
			}
			break;
		case eLEFT:
			if (left)
			{
				m_pos.x -= m_speed;
				m_distance -= m_speed;
			}
			break;
		case eRIGHT:
			if (right)
			{
				m_pos.x += m_speed;
				m_distance -= m_speed;
			}
			break;
		case eUP|eLEFT:
			if (top)
			m_pos.y -= m_speed;
			if (left)
			m_pos.x -= m_speed;
			m_distance -= m_speed;
			break;
		case eUP|eRIGHT:
			if (top)
			m_pos.y -= m_speed;
			if (right)
			m_pos.x += m_speed;
			m_distance -= m_speed;
			break;
		case eDOWN|eLEFT:
			if (bottom)
			m_pos.y += m_speed;
			if (left)
			m_pos.x -= m_speed;
			m_distance -= m_speed;
			break;
		case eDOWN|eRIGHT:
			if (bottom)
			m_pos.y += m_speed;
			if (right)
			m_pos.x += m_speed;
			m_distance -= m_speed;
			break;
		case eDOWN|eUP:
			if (bottom)
				m_pos.y += m_speed;
			break;
		case eLEFT|eRIGHT:
			if (right)
				m_pos.x += m_speed;
			break;
		}
	}
}

void CBullet::PathMove()
{
	if (m_bVisible&&!m_bIsExplode)
	{
		D3DXVECTOR2 pos;
		pos.x = m_pos.x;
		pos.y = m_pos.y;
		pos += m_vec*m_speed;
		m_pos.x = pos.x;
		m_pos.y = pos.y;
	}
}

void CBullet::SetPath(D3DXVECTOR2 vec)
{
	m_vec = vec;
}

void CBullet::SetDamage(WORD damage)
{
	m_damage=damage;
}

void CBullet::SetDistance(WORD distance)
{
	m_distance=distance;
}

void CBullet::SetPos(POINT pos)
{
	m_pos=pos;
}

void CBullet::SetTop(Map*pMap,int tileWidth,int num)
{
	POINT pos = pMap->GetSrcPos();
	UpdateBulletRect();

	for (int i = m_bulletRect.left; i <= m_bulletRect.right; i++)
	{
		int x = (m_bulletRect.top + pos.y ) / tileWidth;
		int y = (i + pos.x) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y) == 24)
		{
			top = true;
			break;
		}
		else
		{
			top = false;
		}
	}
}

void CBullet::SetBottom(Map*pMap, int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	UpdateBulletRect();

	for (int i = m_bulletRect.left; i <= m_bulletRect.right; i++)
	{
		int x = (m_bulletRect.bottom + pos.y) / tileWidth;
		int y = (i + pos.x) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y) == 24)
		{
 			bottom = true;
			break;
		}
		else
		{
			bottom = false;
		}
	}
}

void CBullet::SetLeft(Map*pMap, int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	UpdateBulletRect();

	for (int i = m_bulletRect.top; i <= m_bulletRect.bottom; i++)
	{
		int x = (i + pos.y) / tileWidth;
		int y = (m_bulletRect.left + pos.x ) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y) == 24)
		{
			left = true;
			break;
		}
		else
		{
			left = false;
		}
	}
}

void CBullet::SetRight(Map*pMap,int tileWidth,int num)
{
	POINT pos = pMap->GetSrcPos();
	UpdateBulletRect();

	for (int i = m_bulletRect.top; i <= m_bulletRect.bottom; i++)
	{
		int x = (i + pos.y) / tileWidth;
		int y = (m_bulletRect.right + pos.x ) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y) == 24)
		{
			right = true;
			break;
		}
		else
		{
			right = false;
		}
	}
}

void CBullet::SetVisible(BOOL visible)
{
	m_bVisible=visible;
}

void CBullet::SetSpeed(WORD speed)
{
	m_speed = speed;
}

void CBullet::SetBulletDir(int dir)
{
	m_bulletDir = dir;
}

void CBullet::SetKeyUpDir(int dir)
{
	m_bulletDir -= dir;
}

void CBullet::UpdateBulletRect()
{
	int x = m_pos.x + 37;
	int y = m_pos.y + 35;
	m_bulletRect.top=y;
	m_bulletRect.left = x;
	m_bulletRect.right = x+14;
	m_bulletRect.bottom = y+14;
}

void CBullet::UpdateBigRc()
{
	int x = m_pos.x + 55;
	int y = m_pos.y + 51;
	m_bulletRect.top = y;
	m_bulletRect.left = x;
	m_bulletRect.right = x + 20;
	m_bulletRect.bottom = y + 20;
}

void CBullet::Refresh(WORD curFrame, WORD curRow, WORD startFrame, WORD endFrame, WORD startRow, WORD endRow)
{
	m_pBullet->ReSet(curFrame, curRow, startFrame, endFrame, startRow, endRow);
}

void CBullet::SetIsExplode(bool b)
{
	m_bIsExplode = b;
}

void CBullet::SetDesPos(POINT pos)
{
	m_pBullet->SetDesPos(pos);
}

bool CBullet::GetIsExplode()
{
	return m_bIsExplode;
}

bool CBullet::StopExplode()
{
	if (m_pBullet->GetCurFrame() == 3 && m_pBullet->GetCurRow() == 3)
		return true;
	else
		return false;
}

void CBullet::SetCurRow(WORD row)
{
	m_pBullet->SetCurRow(row);
}

DWORD CBullet::GetColorValue(POINT pos)
{
	return m_pBullet->GetColorValue(pos);
}

WORD CBullet::GetCurFrame()
{
	return m_pBullet->GetCurFrame();
}

WORD CBullet::GetCurRow()
{
	return m_pBullet->GetCurRow();
}

WORD CBullet::GetSpeed()
{
	return m_speed;
}

POINT CBullet::GetPos()
{
	return m_pos;
}

WORD CBullet::GetDamage()
{
	return m_damage;
}

WORD CBullet::GetDistance()
{
	return m_distance;
}

BOOL CBullet::GetVisible()
{
	return m_bVisible;
}

RECT CBullet::GetBulletRect()
{
	return m_bulletRect;
}

bool CBullet::GetBottom()
{
	return bottom;
}

bool CBullet::GetTop()
{
	return top;
}

bool CBullet::GetLeft()
{
	return left;
}

bool CBullet::GetRight()
{
	return right;
}

int CBullet::GetDir()
{
	return m_bulletDir;
}