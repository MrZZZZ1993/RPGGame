#include "stdafx.h"
#include "Eye.h"


CEye::CEye()
{
}

CEye::~CEye()
{
}

void CEye::Function()
{
	m_isUse = false;
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->SetVisible(false);
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerHead()->SetIsRun(false);
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->SetIsRun(false);
}

void CEye::UpdateRc()
{
	int x = m_pos.x;
	int y = m_pos.y;
	m_rc.left = x;
	m_rc.right = x + 64;
	m_rc.top = y;
	m_rc.bottom = y + 64;
}

void CEye::Move()
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