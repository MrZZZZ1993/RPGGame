#include "stdafx.h"
#include "Shoe.h"


CShoe::CShoe()
{
}

CShoe::~CShoe()
{
}

void CShoe::Function()
{
	m_isUse = false;
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerHead()->SetPlayerSpeed(15);
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->SetPlayerSpeed(15);
}
void CShoe::UpdateRc()
{
	int x = m_pos.x;
	int y = m_pos.y;
	m_rc.left = x;
	m_rc.right = x + 64;
	m_rc.top = y;
	m_rc.bottom = y + 64;
}

void CShoe::Move()
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