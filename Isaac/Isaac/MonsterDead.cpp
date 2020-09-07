#include "stdafx.h"
#include "MonsterDead.h"


CMonsterDead::CMonsterDead(void)
{
	m_pPic=nullptr;
	m_curFrame=0;
	m_curRow=0;
	m_isDead=false;
}

CMonsterDead::~CMonsterDead(void)
{
	delete m_pPic;
}

void CMonsterDead::Init(TSTRING name)
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->ReSet(0,0,0,3,0,3);
	m_pPic->UpdateMAatrix();
}

void CMonsterDead::Draw()
{
	if(m_isDead)
	{
		m_pPic->SetDesPos(m_pos);
		m_pPic->Draw();
	}
}

void CMonsterDead::Update()
{
	if(m_isDead)
	{
		m_pPic->SetCurFrame(m_curFrame);
		m_pPic->SetCurRow(m_curRow);
		m_pPic->Update();
		m_curFrame++;
		if(m_curFrame==3)
		{
			m_curFrame=0;
			m_curRow++;
			if(m_curRow==3)
				m_curRow=0;
		}
		if(m_pPic->GetCurFrame()==3&&m_pPic->GetCurRow())
		{
			m_isDead=false;
			m_curRow=0;
			m_curFrame=0;
		}
	}
}

void CMonsterDead::SetIsDead(bool b)
{
	m_isDead=b;
}

void CMonsterDead::SetPos(POINT pos)
{
	m_pos=pos;
}

POINT CMonsterDead::GetPos()
{
	return m_pos;
}

bool CMonsterDead::GetIsDead()
{
	return m_isDead;
}