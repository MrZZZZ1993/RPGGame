#include "stdafx.h"
#include "MaskHeart.h"


CMaskHeart::CMaskHeart()
{
	m_isUpdate = true;
}

CMaskHeart::~CMaskHeart()
{
}

void CMaskHeart::DrawMaskHeart()
{
	if (m_visible)
	{
		POINT pos;
		int width = m_pPic->GetFrameWidth();
		int height = m_pPic->GetFrameHeight();
		switch (m_dir)
		{
		case eUP:
			pos.x = width;
			pos.y = 0;
			m_pPic->SetSrcPos(pos);
			break;
		case eDOWN:
			pos.x = width;
			pos.y = height;
			m_pPic->SetSrcPos(pos);
			break;
		case eLEFT:
			pos.x = 0;
			pos.y = 0;
			m_pPic->SetSrcPos(pos);
			break;
		case eRIGHT:
			pos.x = 0;
			pos.y = height;
			m_pPic->SetSrcPos(pos);
			break;
		}
		m_pPic->SetDesPos(m_pos);
		if (m_isRed)
			m_pPic->SetAddColor(0xff0000);
		else
			m_pPic->SetAddColor(0xffffff);
		m_pPic->Draw();
	}
}

void CMaskHeart::DrawHeart()
{
	if (m_visible)
	{
		POINT pos = { 128, 0 };
		m_pPic->SetDesPos(m_pos);
		m_pPic->SetSrcPos(pos);
		if (m_isRed)
			m_pPic->SetAddColor(0xff0000);
		else
			m_pPic->SetAddColor(0xffffff);
		m_pPic->Draw();
	}
}

void CMaskHeart::HeartMove()
{
	if (m_visible)
	{
		switch (m_dir)
		{
		case eUP:
			m_pos.y -= m_speedNormal;
			if (m_pos.y - m_aimPos <= m_speedNormal || m_pos.y <= 110)
			{
				if (m_pos.y - m_aimPos <= m_speedNormal)
					m_pos.y = m_aimPos;
				m_isUpdate = true;
			}
			break;
		case eDOWN:
			m_pos.y += m_speedNormal;
			if (m_aimPos - m_pos.y <= m_speedNormal || m_pos.y >= 450)
			{
				if (m_aimPos - m_pos.y <= m_speedNormal)
					m_pos.y = m_aimPos;
				m_isUpdate = true;
			}
			break;
		case eLEFT:
			m_pos.x -= m_speedNormal;
			if (m_pos.x - m_aimPos <= m_speedNormal || m_pos.x <= 96)
			{
				if (m_pos.x - m_aimPos <= m_speedNormal)
					m_pos.x = m_aimPos;
				m_isUpdate = true;
			}
			break;
		case eRIGHT:
			m_pos.x += m_speedNormal;
			if (m_aimPos - m_pos.x <= m_speedNormal || m_pos.x >= 710)
			{
				if (m_aimPos - m_pos.x <= m_speedNormal)
					m_pos.x = m_aimPos;
				m_isUpdate = true;
			}
			break;
		}
	}
}

void CMaskHeart::HeartUpdate()
{
	if (m_isUpdate)
	{
		srand(GetTickCount());
		int length = rand() % 200 + 200;
		bool b = true;
		int i;
		while (b)
		{
			srand(GetTickCount());
			i = rand() % 4;
			if (i == 0 && m_pos.y <= 110)
				b = true;
			else if (i == 1 && m_pos.y >= 450)
				b = true;
			else if (i == 2 && m_pos.x <= 96)
				b = true;
			else if (i == 3 && m_pos.x >= 710)
				b = true;
			else
				b = false;
		}
		switch (i)
		{
		case 0:
			m_dir = eUP;
			m_aimPos = m_pos.y - length;
			break;
		case 1:
			m_dir = eDOWN;
			m_aimPos = m_pos.y + length;
			break;
		case 2:
			m_dir = eLEFT;
			m_aimPos = m_pos.x - length;
			break;
		case 3:
			m_dir = eRIGHT;
			m_aimPos = m_pos.x + length;
			break;
		}
		m_isPursue = false;
	}
	m_isUpdate = false;
}

void CMaskHeart::UpdateHeartRc()
{
	int x = m_pos.x - 45;
	int y = m_pos.y - 40;
	m_heartRc.left = x;
	m_heartRc.right = x + 50;
	m_heartRc.top = y;
	m_heartRc.bottom = y + 50;
}

void CMaskHeart::UpdateMaskRc()
{
	int x = m_pos.x - 20;
	int y = m_pos.y - 32;
	m_maskRc.left = x;
	m_maskRc.right = x + 40;
	m_maskRc.top = y;
	m_maskRc.bottom = y + 64;
}

void CMaskHeart::SetIsMask(int i)
{
	m_isMask = i;
}

void CMaskHeart::SetNum(int i)
{
	m_num = i;
}

void CMaskHeart::MaskHeartUpdateAim(POINT playerPos)
{
	if (m_isUpdate)
	{
		int x = playerPos.x + 30;
		int y = playerPos.y + 35;
		if (x >= m_maskRc.left&&x <= m_maskRc.right&&y>m_pos.y)
		{
			m_dir = eDOWN;
			m_aimPos = y;
			m_isPursue = true;
		}
		else if (x >= m_maskRc.left&&x <= m_maskRc.right&&y<m_pos.y)
		{
			m_dir = eUP;
			m_aimPos = y;
			m_isPursue = true;
		}
		else if (y >= m_maskRc.top&&y <= m_maskRc.bottom&&x<m_pos.x)
		{
			m_dir = eLEFT;
			m_aimPos = x;
			m_isPursue = true;
		}
		else if (y >= m_maskRc.top&&y <= m_maskRc.bottom&&x>m_pos.x)
		{
			m_dir = eRIGHT;
			m_aimPos = x;
			m_isPursue = true;
		}
		else
		{
			srand(GetTickCount());
			int length = rand() % 200 + 200;
			bool b = true;
			int i;
			while (b)
			{
				srand(GetTickCount());
				i = rand() % 4;
				if (i == 0 && m_pos.y <= 110)
					b = true;
				else if (i == 1 && m_pos.y >= 450)
					b = true;
				else if (i == 2 && m_pos.x <= 96)
					b = true;
				else if (i == 3 && m_pos.x >= 710)
					b = true;
				else
					b = false;
			}

			switch (i)
			{
			case 0:
				m_dir = eUP;
				m_aimPos = m_pos.y - length;
				break;
			case 1:
				m_dir = eDOWN;
				m_aimPos = m_pos.y + length;
				break;
			case 2:
				m_dir = eLEFT;
				m_aimPos = m_pos.x - length;
				break;
			case 3:
				m_dir = eRIGHT;
				m_aimPos = m_pos.x + length;
				break;
			}
			m_isPursue = false;
		}
		m_isUpdate = false;
	}
}

int CMaskHeart::GetNum()
{
	return m_num;
}

int CMaskHeart::GetIsMask()
{
	return m_isMask;
}

RECT CMaskHeart::GetHeartRc()
{
	return m_heartRc;
}

RECT CMaskHeart::GetMaskRc()
{
	return m_maskRc;
}