#include "stdafx.h"
#include "FlyDuke.h"


CFlyDuke::CFlyDuke()
{
	m_UpdateCount = 0;
	m_countRate = 0;
	m_fire = false;
	m_fireTime = 0;
	m_curFrame = 0;
	m_curRow = 0;
	m_deadcount = 0;
	m_isDead = false;
}

CFlyDuke::~CFlyDuke()
{
}

void CFlyDuke::InitFlyDuke()
{
	m_pPic->ReSet(0, 0, 0, 1, 0, 1);
}

void CFlyDuke::UpdateDuke()
{
	static DWORD preTime = GetTickCount();
	DWORD curTime = GetTickCount();
	if (curTime - preTime > m_fireTime)
	{
		preTime = curTime;
		m_fire = true;
	}

	if (m_fire)
	{
		m_countRate++;
		if (m_countRate == 18)
		{
			m_pPic->Update();
			m_countRate = 0;
			m_UpdateCount++;
		}
		if (m_UpdateCount == 3)
		{
			m_fire = false;
			m_UpdateCount = 0;
			m_pPic->SetCurFrame(1);
			m_pPic->SetCurRow(1);
			m_pPic->Update();
		}
	}
}

void CFlyDuke::SetFireTime(int fireTime)
{
	m_fireTime = fireTime;
}

void CFlyDuke::UpdateFlyDukeRect()
{
	int x = m_pos.x-m_pPic->GetFrameWidth()/2;
	int y = m_pos.y-m_pPic->GetFrameHeight()/2;
	m_rectDuke.top = y;
	m_rectDuke.left = x;
	m_rectDuke.right = x + m_pPic->GetFrameWidth();
	m_rectDuke.bottom = y + m_pPic->GetFrameHeight();
}

void CFlyDuke::Dead()
{
	POINT pos = {0,0};
	if (m_hp <= 0&&m_visible)
	{
		m_pPic->SetSrcPos(pos);
		m_deadcount++;
		if (m_deadcount % 2 == 0)
			m_pos.x += 4;
		else
			m_pos.x -= 4;
		if (m_deadcount==40)
			m_visible = false;
	}
}

void CFlyDuke::SetIsDead(bool b)
{
	m_isDead = b;
}

DWORD CFlyDuke::GetColorValue(POINT pos)
{
	return m_pPic->GetColorValue(pos);
}

int CFlyDuke::GetCurFrame()
{
	return m_pPic->GetCurFrame();
}

int CFlyDuke::GetCurRow()
{
	return m_pPic->GetCurRow();
}

int CFlyDuke::GetPicHeight()
{
	return m_pPic->GetPicHeight();
}

int CFlyDuke::GetPicWidth()
{
	return m_pPic->GetPicWidth();
}

POINT CFlyDuke::GetPos()
{
	POINT pos = {m_pos.x,m_pos.y};
	return pos;
}

RECT CFlyDuke::GetDukeRect()
{
	return m_rectDuke;
}

bool CFlyDuke::GetIsDead()
{
	return m_isDead;
}
