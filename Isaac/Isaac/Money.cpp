#include "stdafx.h"
#include "Money.h"


CMoney::CMoney()
{
	POINT pos = { 100, 100 };
	m_pPic=nullptr;
	m_visible = false;
	m_pos = pos; 
	m_visibleOnMap = true;
	m_visiblePlayer = true;
}

CMoney::~CMoney()
{
	delete m_pPic;
}

void CMoney::Init()
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(_T("money"));
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->UpdateMAatrix();
	m_pPic->ReSet(0, 1, 0, 7, 1, 1);
}

void CMoney::Draw()
{
	if (m_visible&&m_visibleOnMap&&m_visiblePlayer)
	{
		m_pPic->SetDesPos(m_pos);
		m_pPic->Draw();
	}
}

void CMoney::Update()
{
	if(m_visible&&m_pPic->GetCurFrame()!=7&&m_visiblePlayer)
		m_pPic->Update();
}

void CMoney::SetVisible(bool b)
{
	m_visible=b;
}

void CMoney::SetVisiblePlayer(bool b)
{
	m_visiblePlayer = b;
}

void CMoney::UpdateRc()
{
	int x=m_pos.x+46;
	int y=m_pos.y+51;
	m_rc.left=x;
	m_rc.right=x+33;
	m_rc.top=y;
	m_rc.bottom=y+24;
}

void CMoney::SetPos(POINT pos)
{
	m_pos=pos;
}

void CMoney::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CMoney::SetVisibleOnMap(bool b)
{
	m_visibleOnMap = b;
}

void CMoney::SetCurFrame(int i)
{
	m_pPic->SetCurFrame(i);
}

int CMoney::GetMapIndex()
{
	return m_mapIndex;
}

POINT CMoney::GetPoint()
{
	return m_pos;
}

bool CMoney::GetVisible()
{
	return m_visible;
}

bool CMoney::GetVisibleOnMap()
{
	return m_visibleOnMap;
}

bool CMoney::GetVisiblePlayer()
{
	return m_visiblePlayer;
}

RECT CMoney::GetRc()
{
	return m_rc;
}