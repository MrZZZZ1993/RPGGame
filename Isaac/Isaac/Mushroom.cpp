#include "stdafx.h"
#include "Mushroom.h"


CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
}

void CMushroom::Function()
{
	m_isUse = false;
	CGameManager::GetInstance()->GetFirstStage()->GetBulletPool()->SetRate(250);
}

void CMushroom::UpdateRc()
{
	int x = m_pos.x;
	int y = m_pos.y;
	m_rc.left = x;
	m_rc.right = x + 64;
	m_rc.top = y;
	m_rc.bottom = y + 64;
}

void CMushroom::Move()
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