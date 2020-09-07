#include "stdafx.h"
#include "PlayerHead.h"


CPlayerHead::CPlayerHead()
{
	POINT pos={100,100};
	m_playerPos=pos;
	m_pPlayer = nullptr;
	m_playerDir=eNONE;
	m_bulletDir = eNONE;
	m_playerSpeed=0;
	IsFire = false;
	m_bIsReset = true;
	m_count = 0;
	m_isHold = false;
	m_isRun=true;
}

CPlayerHead::~CPlayerHead(void)
{
	delete m_pPlayer;
}

void CPlayerHead::Init(TSTRING name)
{
	m_pPlayer = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPlayer->Init();
	m_pPlayer->SetShowWidth(m_pPlayer->GetFrameWidth());
	m_pPlayer->SetShowHeight(m_pPlayer->GetFrameHeight());

	m_other = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("others"));
	m_other->Init();
	m_other->SetShowWidth(m_other->GetFrameWidth());
	m_other->SetShowHeight(m_other->GetFrameHeight());
	m_other->UpdateMAatrix();
	m_other->ReSet(2,1,2,2,1,1);
	POINT pos={m_other->GetCurFrame()*m_other->GetFrameWidth(),m_other->GetCurRow()*m_other->GetFrameHeight()};
	m_other->SetSrcPos(pos);
}

void CPlayerHead::Draw()
{
	m_pPlayer->SetDesPos(m_playerPos);
	if(m_visible)
		m_pPlayer->Draw();

	DrawOther();
	DrawHoldGoods();
}

void CPlayerHead::DrawOther()
{
	POINT pos = m_playerPos;
	POINT srcPos = { 258, 113 };
	pos.x=m_playerPos.x-35;
	pos.y=m_playerPos.y-12;
	m_other->SetDesPos(pos);
	m_other->SetSrcPos(srcPos);
	if (!m_visible&&!m_isHold)
	{
		m_other->SetAddColor(0xff0000);
		m_other->Draw();
	}
}

void CPlayerHead::DrawHoldGoods()
{
	POINT pos = m_playerPos;
	POINT srcPos = { 129, 113 };
	pos.x = m_playerPos.x - 35;
	pos.y = m_playerPos.y - 12;
	m_other->SetDesPos(pos);
	m_other->SetSrcPos(srcPos);
	if (!m_visible&&m_isHold)
	{
		m_other->SetAddColor(0xffffff);
		m_other->Draw();
	}
}

void CPlayerHead::Update()
{
	m_pPlayer->UpdateMAatrix();
	if (!IsFire)
		switch (m_playerDir)
	{
		case eNONE:
			m_pPlayer->UpdateSrcPos(0, 0);
			break;
		case eUP:
			m_pPlayer->UpdateSrcPos(4, 0);
			break;
		case eDOWN:
			m_pPlayer->UpdateSrcPos(0, 0);
			break;
		case eLEFT:
			m_pPlayer->UpdateSrcPos(3, 1);
			break;
		case eRIGHT:
			m_pPlayer->UpdateSrcPos(2, 0);
			break;
	}
	else 
	{
		switch (m_bulletDir)
		{
		case eNONE:
			ReSet(0, 0, 0, 0, 0, 0);
			m_pPlayer->UpdateSrcPos(0, 0);
			break;
		case eUP:
			if (m_bIsReset)
			{
				m_bIsReset = false;
				ReSet(5, 0, 5, 4, 0, 0);
			}
			break;
		case eDOWN:
			if (m_bIsReset)
			{
				m_bIsReset = false;
				ReSet(1, 0, 1, 0, 0, 0);
			}
			break;
		case eLEFT:
			if (m_bIsReset)
			{
				m_bIsReset = false;
				ReSet(2, 1, 2, 3, 1, 1);
			}
			break;
		case eRIGHT:
			if (m_bIsReset)
			{
				m_bIsReset = false;
				ReSet(3, 0, 3, 2, 0, 0);
			}
			break;
		}
		if (m_count % 5 == 0)
			m_pPlayer->Update();
		m_count++;
	}
}

void CPlayerHead::SetIsHold(bool b)
{
	m_isHold = b;
}

void CPlayerHead::OnKeyDown(SEvent event)
{
	if(event.keyInput.pressedDown)
	{
		switch (event.keyInput.key)
		{
		case 'W':
			m_playerDir|=eUP;
			break;
		case  'S':
			m_playerDir|=eDOWN;
			break;
		case 'A' :
			m_playerDir|=eLEFT;
			break;
		case 'D':
			m_playerDir|=eRIGHT;
			break;
		case VK_UP:
			IsFire = true;
			m_bulletDir |= eUP;
			break;
		case  VK_DOWN:
			IsFire = true;
			m_bulletDir |= eDOWN;
			break;
		case VK_LEFT:
			IsFire = true;
			m_bulletDir |= eLEFT;
			break;
		case VK_RIGHT:
			IsFire = true;
			m_bulletDir |= eRIGHT;
			break;
		}
	}
}

void CPlayerHead::OnKeyUp(SEvent event)
{
	if (!event.keyInput.pressedDown)
	{
		switch(event.keyInput.key)
		{
		case 'W':
			m_playerDir-=eUP;
			break;
		case 'S':
			m_playerDir-=eDOWN;
			break;
		case 'A':
			m_playerDir-=eLEFT;
			break;
		case 'D':
			m_playerDir-=eRIGHT;
			break;
		case VK_UP:
			IsFire = false;
			m_bIsReset = true;
			m_bulletDir -= eUP;
			m_count = 0;
			break;
		case  VK_DOWN:
			IsFire = false;
			m_bIsReset = true;
			m_bulletDir -= eDOWN;
			m_count = 0;
			break;
		case VK_LEFT:
			IsFire = false;
			m_bIsReset = true;
			m_bulletDir -= eLEFT;
			m_count = 0;
			break;
		case VK_RIGHT:
			IsFire = false;
			m_bIsReset = true;
			m_bulletDir -= eRIGHT;
			m_count = 0;
			break;
		}
	}
}

void CPlayerHead::UpdateHeadRect()
{
	int x = m_pPlayer->GetDesPos().x + 6;
	int y = m_pPlayer->GetDesPos().y + 4;
	m_headRect.top=y;
	m_headRect.left = x;
	m_headRect.right = x+53;
	m_headRect.bottom = y+49;
}

void CPlayerHead::UpdateHeadCollision()
{
	int x = m_playerPos.x;
	int y = m_playerPos.y;
	m_headRectCollision.top = y;
	m_headRectCollision.left = x;
	m_headRectCollision.right = x + m_pPlayer->GetFrameWidth();
	m_headRectCollision.bottom = y + m_pPlayer->GetFrameHeight();
}

void CPlayerHead::SetAddColor(long a)
{
	m_other->SetAddColor(a);
}

void CPlayerHead::SetHp(int hp)
{
	m_hp=hp;
}

void CPlayerHead::SetCountHp(int hp)
{
	m_countHp=hp;
}

bool CPlayerHead::GetIsHold()
{
	return m_isHold;
}

int CPlayerHead::GetCountHp()
{
	return m_countHp;
}

int CPlayerHead::GetHp()
{
	return m_hp;
}

RECT CPlayerHead::GetHeadRect()
{
	return m_headRect;
}

RECT CPlayerHead::GetHeadCollision()
{
	return m_headRectCollision;
}

long CPlayerHead::GetAddColor()
{
	return m_other->GetAddColor();
}