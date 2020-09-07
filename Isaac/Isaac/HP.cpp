#include "stdafx.h"
#include "HP.h"


CHP::CHP()
{
	m_count=0;
}


CHP::~CHP()
{
}

void CHP::Function()
{
	m_isUse = false;
	CPlayerHead *m_pPlayer=CGameManager::GetInstance()->GetFirstStage()->GetPlayerHead();
	if(m_pPlayer->GetHp()<m_pPlayer->GetCountHp()&&m_count==0)
	{
		m_count++;
		m_pPlayer->SetHp(m_pPlayer->GetHp()+1);
	}
}

void CHP::Move()
{

}

void CHP::UpdateRc()
{
	int x = m_pos.x;
	int y = m_pos.y;
	m_rc.left = x;
	m_rc.right = x + 64;
	m_rc.top = y;
	m_rc.bottom = y + 64;
}

void CHP::SetSrcPos(POINT pos)
{
	m_pPic->SetSrcPos(pos);
}