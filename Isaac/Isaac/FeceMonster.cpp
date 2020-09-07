#include "stdafx.h"
#include "FeceMonster.h"


CFeceMonster::CFeceMonster()
{
	m_pPic = nullptr;
	m_visible = true;
	m_state = eSTAND;
	m_curRow = 0;
	m_curFrame=0;
	m_isRed = false;
	m_isUpdate = true;
	m_speed = 0;
	m_count = 0;
	m_dir = eRIGHT;
}

CFeceMonster::~CFeceMonster()
{
	delete m_pPic;
}

void CFeceMonster::Init(TSTRING name)
{
	m_pPic = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->SetCenter(m_pPic->GetFrameWidth() / 2, m_pPic->GetFrameHeight() / 2);
	m_pPic->UpdateMAatrix();
}

void CFeceMonster::Draw()
{
	int width = m_pPic->GetFrameWidth();
	int height = m_pPic->GetFrameHeight();
	POINT pos;
	if (m_visible)
	{
		if (m_updateCount%5==0)
		{
			m_updateCount = 0;
			switch (m_state)
			{
			case eSTAND:
				if (m_dir == eLEFT)
				{
					m_curFrame--;
					if (m_curFrame == -1)
						m_curFrame = 2;
					m_curRow = 2;
				}
				else if (m_dir == eRIGHT)
				{
					m_curFrame++;
					if (m_curFrame == 3)
						m_curFrame = 0;
					m_curRow = 0;
				}
				break;
			case eWALK:
				if (m_dir == eLEFT)
				{
					m_curFrame--;
					if (m_curFrame <= 0)
						m_curFrame = 2;
					m_curRow = 3;
				}
				else if (m_dir == eRIGHT)
				{
					m_curFrame++;
					if (m_curFrame >= 2)
						m_curFrame = 0;
					m_curRow = 1;
				}
				break;
			}
		}
		    pos.y = m_curRow*height;
			pos.x = m_curFrame*width;
			m_pPic->SetSrcPos(pos);
			m_pPic->SetDesPos(m_pos);
			if (m_isRed)
				m_pPic->SetAddColor(0xff0000);
			else
				m_pPic->SetAddColor(0xffffff);
			m_pPic->Draw();

			m_updateCount++;
	}
}

void CFeceMonster::Move(Map*pMap)
{
	if (m_state == eSTAND)
	{
		m_count++;
		if (m_count== 40)
		{
			m_isUpdate = true;
			m_count = 0;
		}
	}
	else if (m_state == eWALK)
	{
		D3DXVECTOR2 pos;
		pos.x = m_pos.x;
		pos.y = m_pos.y;
		D3DXVECTOR2 vec = aimPos - pos;
		D3DXVec2Normalize(&vec, &vec);

		float fDist = D3DXVec2Length(&(aimPos - pos));

		D3DXVECTOR2 temp = pos += vec*m_speed;

		if (temp.x < 96 || temp.x > 710 || temp.y < 110 || temp.y > 450)
		{
			if (temp.x < 96)
				m_pos.x = 97;
			if (temp.x > 710)
				m_pos.x = 609;
			if (temp.y < 110)
				m_pos.y = 111;
			if (temp.y > 450)
				m_pos.y = 449;
			m_isUpdate = true;
			return;
		}

		if (pMap->GetMap(temp.y / 64, temp.x / 64) != 32)
		{
			m_isUpdate = true;
			return;
		}

		if (m_speed >= fDist)
		{
			pos = aimPos;
			m_isUpdate = true;
		}
		else
		{
			pos += vec*m_speed;;
		}
		m_pos.x = pos.x;
		m_pos.y = pos.y;
	}
}

void CFeceMonster::UpdateAimPos()
{
	if (m_isUpdate)
	{
		srand(GetTickCount());
		int ii = rand() % 2;
		if (ii == 0)
		{
			m_state = eSTAND;
			m_isUpdate = false;
			return;
		}
		else if (ii == 1)
			m_state=eWALK;
		srand(GetTickCount());
		int x = rand() % 50 + 50;
		Sleep(1);
		srand(GetTickCount());
		int y = rand() % 50 + 50;
		Sleep(1);
		srand(GetTickCount());
		int i = rand() % 4;
		switch (i)
		{
		case 0:
			aimPos.x = x + m_pos.x;
			aimPos.y = y + m_pos.y;
			m_dir = eRIGHT;
			break;
		case 1:
			aimPos.x = m_pos.x - x;
			aimPos.y = m_pos.y - y;
			m_dir = eLEFT;
			break;
		case 2:
			aimPos.x = m_pos.x - x;
			aimPos.y = m_pos.y + y;
			m_dir = eLEFT;
			break;
		case 3:
			aimPos.x = m_pos.x + x;
			aimPos.y = m_pos.y - y;
			m_dir = eRIGHT;
			break;
		}
		m_isUpdate = false;
	}
}

void CFeceMonster::SetVisible(bool b)
{
	m_visible = b;
}

void CFeceMonster::SetHp(int i)
{
	m_hp = i;
}

void CFeceMonster::SetDamage(int i)
{
	m_damage = i;
}

void CFeceMonster::SetPos(POINT pos)
{
	m_pos = pos;
}

void CFeceMonster::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CFeceMonster::SetIsRed(bool b)
{
	m_isRed = b;
}

void CFeceMonster::SetSpeed(int i)
{
	m_speed = i;
}

void CFeceMonster::UpdateRc()
{
	int x = m_pos.x - 13;
	int y = m_pos.y - 15;
	m_rc.top = y;
	m_rc.bottom = y + 30;
	m_rc.left = x;
	m_rc.right = x + 26;
}

int CFeceMonster::GetSpeed()
{
	return m_speed;
}

bool CFeceMonster::GetIsRed()
{
	return m_isRed;
}

bool CFeceMonster::GetVisible()
{
	return m_visible;
}

int CFeceMonster::GetHp()
{
	return m_hp;
}

int CFeceMonster::GetDamage()
{
	return m_damage;
}

POINT CFeceMonster::GetPos()
{
	return m_pos;
}

int CFeceMonster::GetMapIndex()
{
	return m_mapIndex;
}

RECT CFeceMonster::GetRc()
{
	return m_rc;
}