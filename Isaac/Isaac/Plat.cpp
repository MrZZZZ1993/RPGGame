#include "stdafx.h"
#include "Plat.h"


CPlat::CPlat()
{
}

CPlat::~CPlat()
{
}

void CPlat::UpdateRc()
{
	int x = m_pos.x + 9;
	int y = m_pos.y + 10;
	m_rc.top = y;
	m_rc.left = x;
	m_rc.right = x + 47;
	m_rc.bottom = y + 31;
}

void CPlat::Function()
{


}

void CPlat::Move()
{}