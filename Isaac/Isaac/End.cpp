#include "stdafx.h"
#include "End.h"


CEnd::CEnd()
{
	m_visible=false;
	m_pPic=nullptr;
	POINT pos={350,-1088};
	m_pos=pos;
	m_isUpdate=false;
	m_visibleOnMap=false;
	m_mapIndex=6;
	m_pLost = nullptr;
	m_isdead = false;
	count = 0;
}

CEnd::~CEnd()
{
	delete m_pPic;
	delete m_pLost;
}

void CEnd::Init()
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(_T("goldenBox"));
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->ReSet(3,0,3,0,0,0);
	POINT pos={m_pPic->GetFrameWidth()*3+20,0};
	m_pPic->SetSrcPos(pos);
	m_pPic->UpdateMAatrix();

	m_pLost = (CStaticImg*)CResManager::GetInstance()->GetRes(_T("lost"));
	m_pLost->Init();
	m_pLost->SetShowWidth(m_pLost->GetPicWidth());
	m_pLost->SetShowHeight(m_pLost->GetPicHeight());
	m_pLost->UpdateMAatrix();
}

void CEnd::Draw()
{
	if(m_visible&&m_visibleOnMap)
		m_pPic->Draw();
}

void CEnd::DrawLost()
{
	if (m_isdead)
		m_pLost->Draw();
}

void CEnd::Update()
{
	if(m_visible&&m_pPic->GetCurFrame()!=0&&m_isUpdate)
		m_pPic->Update();
}

void CEnd::SetVisible(bool b)
{
	m_visible=b;
}

void CEnd::Move()
{
	if(m_visible)
	{
		if(m_pos.y<128)
		{
			m_pos.y+=64;
			m_pPic->SetDesPos(m_pos);
		}
		else if(m_pos.y==128)
		{
			m_isUpdate=true;
		}
	}
}

void CEnd::SetMapIndex(int i)
{
	m_mapIndex=i;
}

void CEnd::UpdateRc()
{
	int x=m_pos.x+9;
	int y=m_pos.y+81;
	m_rc.left=x;
	m_rc.right=x+108;
	m_rc.top=y;
	m_rc.bottom=y+78;
}

void CEnd::End()
{
	if (count == 0)
	{
		CInputManager::GetInstance()->DeleteKeyListener(_T("PlayerHead"));
		CInputManager::GetInstance()->DeleteKeyListener(_T("PlayerBody"));
		CInputManager::GetInstance()->DeleteKeyListener(_T("BulletPool"));
		m_isdead = true;
		CAudio4Bass::GetInstance()->ChannelPlay(4, true);
		CAudio4Bass::GetInstance()->ChannelStop(1);
		CAudio4Bass::GetInstance()->ChannelStop(2);
		CAudio4Bass::GetInstance()->ChannelPlay(0, true);
		count++;
	}
}

void CEnd::SetVisibleOmMap(bool b)
{
	m_visibleOnMap=b;
}

int CEnd::GetMapIndex()
{
	return m_mapIndex;
}

bool CEnd::GetVisible()
{
	return m_visible;
}

RECT CEnd::GetRc()
{
	return m_rc;
}

bool CEnd::GetVisibleOnMap()
{
	return m_visibleOnMap;
}

POINT CEnd::GetPos()
{
	return m_pos;
}

int CEnd::GetCurFrame()
{
	return m_pPic->GetCurFrame();
}

bool CEnd::GetIsdead()
{
	return m_isdead;
}