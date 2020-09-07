#include "stdafx.h"
#include "Leg.h"


CLeg::CLeg()
{
	m_pLeg=nullptr;
	m_legVisible=false;
	m_isMove=false;
	m_dir=eUP;
	m_count=0;
}


CLeg::~CLeg()
{
	delete m_pLeg;
}


void CLeg::InitLeg()
{
	m_pLeg=(CStaticImg*)CResManager::GetInstance()->GetRes(_T("leg"));
	m_pLeg->Init();
	m_pLeg->SetShowWidth(90);
	m_pLeg->SetShowHeight(540);
	m_pLeg->SetCenter(67,540);
	POINT pos={0,0};
	m_legPos=pos;
	m_pLeg->SetDesPos(pos);
	m_pLeg->UpdateMAatrix();
	POINT pos1={100,400};
	m_aimPos=pos1;
}

void CLeg::Function()
{
	if(m_isUse)
	{
		m_legVisible=true;
		m_isUse=false;
	}
	if(m_legVisible&&m_isMove)
	{
		m_legPos.x=m_aimPos.x;
		if(m_dir==eDOWN)
		{
			if(m_legPos.y+m_legSpeed>=m_aimPos.y)
			{
				m_legPos.y=m_aimPos.y;
				m_count++;
				if(m_count==30)
				{
					m_dir=eUP;
					m_count=0;
				}
			}
			else
				m_legPos.y+=m_legSpeed;
		}
		else if(m_dir==eUP)
		{
			if(m_legPos.y-m_legSpeed<=0)
			{
				m_legPos.y=0;
				m_count++;
				if(m_count==30)
				{
					m_dir=eDOWN;
					m_count=0;
					m_isMove=false;
				}
			}
			else
				m_legPos.y-=m_legSpeed;
		}
		m_pLeg->SetDesPos(m_legPos);
		m_pLeg->Draw();
	}
}

void CLeg::UpdateRc()
{
	int x = m_pos.x;
	int y = m_pos.y;
	m_rc.left = x;
	m_rc.right = x + 64;
	m_rc.top = y;
	m_rc.bottom = y + 64;
}

void CLeg::SetLegSpeed(int i)
{
	m_legSpeed=i;
}

void CLeg::UpdateLegRc()
{
	int x=m_legPos.x;
	int y=m_legPos.y;
	m_legRc.left=x-30;
	m_legRc.right=x+30;
	m_legRc.top=y-40;
	m_legRc.bottom=y;
}

void CLeg::SetIsMove(bool b)
{
	m_isMove=b;
}

void CLeg::SetAimPos(POINT pos)
{
	m_aimPos=pos;
}

void CLeg::SetDamage(int i)
{
	m_damage=i;
}

void CLeg::SetDirOnMap(int i)
{
	m_dirOnMap=i;
}

void CLeg::MoveOnMap()
{
	POINT pos = { 0, 0 };
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	if (m_legVisible)
	{
		switch (m_dirOnMap)
		{
		case eNONE:
			pos.x = m_legPos.x;
			pos.y = m_legPos.y;
			break;
		case eUP:
			pos.y = m_legPos.y - speed;
			pos.x = m_legPos.x;
			break;
		case eDOWN:
			pos.y = m_legPos.y + speed;
			pos.x = m_legPos.x;
			break;
		case eLEFT:
			pos.x = m_legPos.x - speed;
			pos.y = m_legPos.y;
			break;
		case eRIGHT:
			pos.x = m_legPos.x + speed;
			pos.y = m_legPos.y;
			break;
		case eUP | eLEFT:
			pos.y = m_legPos.y - speed;
			pos.x = m_legPos.x - speed;
			break;
		case eDOWN | eLEFT:
			pos.y = m_legPos.y + speed;
			pos.x = m_legPos.x - speed;
			break;
		case eUP | eRIGHT:
			pos.y = m_legPos.y - speed;
			pos.x = m_legPos.x + speed;
			break;
		case eDOWN | eRIGHT:
			pos.y = m_legPos.y + speed;
			pos.x = m_legPos.x + speed;
			break;
		}
		m_legPos=pos;
	}
}

int CLeg::GetDamage()
{
	return m_damage;
}

bool CLeg::GetIsMove()
{
	return m_isMove;
}

bool CLeg::GetLegVisible()
{
	return m_legVisible;
}

RECT CLeg::GetLegRc()
{

	return m_legRc;
}

void CLeg::Move()
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