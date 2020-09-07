#include "stdafx.h"
#include "Fire.h"


CFire::CFire()
{
	m_pUnder = nullptr;
	m_pFire = nullptr;
	m_count = 0;
	m_visible = true;
	POINT pos = { 0, 0 };
	m_underPos=m_pos = pos;
	m_dirOnMap=0;
	m_mapIndex=0;
	m_visibleOnMap = true;
	m_curFrame=0;
}

CFire::~CFire()
{
	delete m_pUnder;
	delete m_pFire;
}

void CFire::Init()
{
	m_pUnder = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("underFire"));
	m_pUnder -> Init();
	m_pUnder->SetShowWidth(m_pUnder->GetFrameWidth());
	m_pUnder->SetShowHeight(m_pUnder->GetFrameHeight());
	m_pUnder->UpdateMAatrix();

	m_pFire = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("fire"));
	m_pFire->Init();
	m_pFire->SetShowWidth(m_pFire->GetFrameWidth());
	m_pFire->SetShowHeight(m_pFire->GetFrameHeight());
	m_pFire->UpdateMAatrix();
	m_pFire->ReSet(0, 0, 0, 5, 0, 0);
	m_pFire->SetTrasparent(0xcc000000);
}

void CFire::Draw()
{
	if (m_visibleOnMap)
	{
		m_underPos.x = m_pos.x + 14;
		m_underPos.y = m_pos.y + 50;
		m_pUnder->SetDesPos(m_underPos);
		m_pUnder->Draw();
		if (m_visible)
		{
			m_pFire->SetDesPos(m_pos);
			m_pFire->Draw();
		}
	}
}

void CFire::Update()
{
	if (m_visible)
	{
		m_count++;
		if (m_count % 3 == 0)
		{
			m_pFire->SetCurFrame(m_curFrame);
			m_pFire->Update();
			m_count = 0;
			m_curFrame++;
			if(m_curFrame==6)
				m_curFrame=0;
		}
	}
}

void CFire::SetPos(POINT pos)
{
	m_pos = pos;
}

void CFire::SetVisible(bool b)
{
	m_visible = b;
}

void CFire::MoveOnMap()
{
	POINT pos = { 0, 0 };
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	if (m_visible)
	{
		switch (m_dirOnMap)
		{
		case eNONE:
			pos.x = m_pos.x;
			pos.y = m_pos.y;
			break;
		case eUP:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x;
			break;
		case eDOWN:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x;
			break;
		case eLEFT:
			pos.x = m_pos.x - speed;
			pos.y = m_pos.y;
			break;
		case eRIGHT:
			pos.x = m_pos.x + speed;
			pos.y = m_pos.y;
			break;
		case eUP | eLEFT:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x - speed;
			break;
		case eDOWN | eLEFT:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x - speed;
			break;
		case eUP | eRIGHT:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x + speed;
			break;
		case eDOWN | eRIGHT:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x + speed;
			break;
		}
		m_pos=pos;
	}
}

void CFire::SetDir(int dir)
{
	m_dirOnMap=dir;
}

void CFire::SetMapIndex(int a)
{
	m_mapIndex=a;
}

void CFire::UpdateFireRect()
{
	int x = m_pos.x + 30;
	int y = m_pos.y + 30;
	rc.top = y;
	rc.bottom = y + 54;
	rc.left = x;
	rc.right = x + 42;
}

void CFire::SetDamage(int d)
{
	m_damage = d;
}

void CFire::SetVisibleOnMap(bool b)
{
	m_visibleOnMap = b;
}

int CFire::GetDamage()
{
	return m_damage;
}

int CFire::GetMapIndex()
{
	return m_mapIndex;
}

bool CFire::GetVisible()
{
	return m_visible;
}

bool CFire::GetVisibleOnMap()
{
	return m_visibleOnMap;
}

POINT CFire::GetPos()
{
	return m_pos;
}

RECT CFire::GetFireRect()
{
	return rc;
}