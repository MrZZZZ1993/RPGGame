#include "stdafx.h"
#include "BombExplode.h"


CBombExplode::CBombExplode()
{
	m_pPic=nullptr;
	m_isExplode=false;
	m_curRow=0;
	m_curFrame=0;
	m_pos.x=0;
	m_pos.y=0;
	m_damage=0;
}

CBombExplode::~CBombExplode()
{
	delete m_pPic;
}

void CBombExplode::Init(TSTRING name)
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->UpdateMAatrix();
}

void CBombExplode::Draw()
{
	m_pPic->SetDesPos(m_pos);
	if(m_isExplode)
	{
		POINT pos={m_curFrame*m_pPic->GetFrameWidth(),m_curRow*m_pPic->GetFrameHeight()};
		m_pPic->SetSrcPos(pos);
		m_pPic->Draw();
		m_curFrame++;
		if(m_curFrame==4)
		{
			m_curRow++;
			if(m_curRow==3)
			{
				m_curRow=0;
				m_isExplode=false;
			}
			m_curFrame=0;
		}
	}
}

void CBombExplode::Update()
{
	if(m_isExplode)
	{
		/*m_pPic->Update();
		m_curFrame++;
		if(m_curFrame==4)
		{
			m_curRow++;
			if(m_curRow==3&&m_curFrame==4)
				m_isExplode=false;
			if(m_curRow==3)
				m_curRow=0;
			m_curFrame=0;

		}*/
	}
}

void CBombExplode::ReSet(int curFrame,int curRow,int startFrame,int endFrame,int startRow,int endRow)
{
	m_pPic->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
}

void CBombExplode::SetDesPos(POINT pos)
{
	m_pos=pos;
}

void CBombExplode::SetIsExplode(bool b)
{
	m_isExplode=b;
}

void CBombExplode::UpdateRect()
{
	int x=m_pos.x;
	int y=m_pos.y;
	m_rc.top=y+80;
	m_rc.left=x;
	m_rc.bottom=y+230;
	m_rc.right=x+192;
}

void CBombExplode::SetDamage(int i)
{
	m_damage=i;
}

int CBombExplode::GetDamage()
{
	return m_damage;
}

bool CBombExplode::GetIsExplode()
{
	return m_isExplode;
}

RECT CBombExplode::GetRect()
{
	return m_rc;
}

POINT CBombExplode::GetPos()
{
	return m_pos;
}

int CBombExplode::GetCurFrame()
{
	return m_curFrame;
}

int CBombExplode::GetCurRow()
{
	return m_curRow;
}