#include "stdafx.h"
#include "Goods.h"


CGoods::CGoods()
{
	m_pPic = nullptr;
	m_dir = eUP;
	m_visibleOnMap = true;
	m_isUse = false;
}

CGoods::~CGoods()
{
	delete m_pPic;
}

void CGoods::Init(TSTRING name)
{
	m_pPic = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->UpdateMAatrix();
}

void CGoods::Draw()
{
	if (m_visible&&m_visibleOnMap)
	{
		m_pPic->SetDesPos(m_pos);
		m_pPic->Draw();
	}
}

void CGoods::SetPos(POINT pos)
{
	m_pos = pos;
}

void CGoods::SetVisibleOnMap(bool b)
{
	m_visibleOnMap = b;
}

void CGoods::SetVisible(bool b)
{
	m_visible = b;
}

void CGoods::Move()
{
	if (m_visible)
	{
		if (m_dir == eUP)
		{
			m_pos.y -= 1;
			if (m_pos.y == 200)
				m_dir = eDOWN;
		}
		else if (m_dir == eDOWN)
		{
			m_pos.y += 1;
			if (m_pos.y == 210)
				m_dir = eUP;
		}
	}
}

void CGoods::SetShowWidth(int i)
{
	m_pPic->SetShowWidth(i);
}

void CGoods::SetShowHeight(int i)
{
	m_pPic->SetShowHeight(i);
}

void CGoods::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CGoods::SetIsUse(bool b)
{
	m_isUse = b;
}

bool CGoods::GetIsUse()
{
	return m_isUse;
}

int CGoods::GetMapIndex()
{
	return m_mapIndex;
}

bool CGoods::GetVisible()
{
	return m_visible;
}

bool CGoods::GetVisibleOnMap()
{
	return m_visibleOnMap;
}

POINT CGoods::GetPos()
{
	return m_pos;
}

RECT CGoods::GetRc()
{
	return m_rc;
}