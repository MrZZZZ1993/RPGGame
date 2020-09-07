#include "stdafx.h"
#include "MatherHeart.h"


CMatherHeart::CMatherHeart()
{
	m_pPic=nullptr;
	m_updateCount=0;
	m_dir = eLEFT;
	m_isRed=false;
}

CMatherHeart::~CMatherHeart()
{
	delete m_pPic;
}

void CMatherHeart::Init(TSTRING name)
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->ReSet(0,0,0,1,0,0);
	m_pPic->UpdateMAatrix();
}

void CMatherHeart::Draw()
{
    if(m_visible)
	{
		m_pPic->SetDesPos(m_pos);
		if (m_isRed)
			m_pPic->SetAddColor(0xff0000);
		else if (!m_isRed)
			m_pPic->SetAddColor(0xffffff);
		m_pPic->Draw();
	}
}

void CMatherHeart::Update()
{
	m_updateCount++;
	if(m_visible&&m_updateCount==8)
	{
		m_pPic->Update();
		m_updateCount=0;
	}
}

void CMatherHeart::SetVisible(bool b)
{
	m_visible=b;
}

void CMatherHeart::SetIsRed(bool b)
{
	m_isRed=b;
}

void CMatherHeart::SetDamage(int i)
{
	m_damage=i;
}

void CMatherHeart::SetHp(int i)
{
	m_hp=i;
}

void CMatherHeart::SetMapIndex(int i)
{
	m_mapIndex=i;
}

void CMatherHeart::SetPos(POINT pos)
{
	m_pos=pos;
}

void CMatherHeart::ReSet(int curFrame,int curRow,int startFrame,int endFrame,int startRow,int endRow)
{
	m_pPic->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
}

void CMatherHeart::UpdateMahterRc()
{
	int x = m_pos.x + 62;
	int y = m_pos.y;
	m_rc.top = y;
	m_rc.bottom = y + 207;
	m_rc.left = x;
	m_rc.right = x + 100;
}

RECT CMatherHeart::GetMatherRc()
{
	return m_rc;
}

POINT CMatherHeart::GetPos()
{
	return m_pos;
}

int CMatherHeart::GetMapIndex()
{
	return m_mapIndex;
}

int CMatherHeart::GetHp()
{
	return m_hp;
}

int CMatherHeart::GetDamage()
{
	return m_damage;
}

int CMatherHeart::GetCurFrame()
{
	return m_pPic->GetCurFrame();
}

int CMatherHeart::GetCurRow()
{
	return m_pPic->GetCurRow();
}

bool CMatherHeart::GetIsRed()
{
	return m_isRed;
}

bool CMatherHeart::GetVisible()
{
	return m_visible;
}

