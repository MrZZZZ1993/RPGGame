#include "stdafx.h"
#include "PlayerBody.h"


CPlayerBody::CPlayerBody()
{
	POINT pos={0,0};
	m_playerPos=pos;
	m_pPlayer = nullptr;
	m_playerDir=eNONE;
	m_playerSpeed=0;
	m_bIsReset=true;
	m_count = 0;
	m_updateRate = 3;
	m_pPlayerShadow = nullptr;
	m_isRun=true;
}

CPlayerBody::~CPlayerBody()
{
	delete m_pPlayer;
	delete m_pPlayerShadow;
}

void CPlayerBody::Init(TSTRING name)
{
	m_pPlayer = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPlayer->Init();
	POINT pos = { 101, 122 };
	m_pPlayer->SetDesPos(pos);
	m_playerPos = pos;
	m_pPlayer->SetShowWidth(m_pPlayer->GetFrameWidth());
	m_pPlayer->SetShowHeight(m_pPlayer->GetFrameHeight());
}

void CPlayerBody::InitShadow(TSTRING name)
{
	m_pPlayerShadow = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
	m_pPlayerShadow->Init();
	POINT pos = { 114, 160 };
	m_pPlayerShadow->SetDesPos(pos);
	m_pPlayerShadow->SetShowHeight(14);
	m_pPlayerShadow->SetShowWidth(36);
}

void CPlayerBody::Draw()
{
	m_pPlayer->SetDesPos(m_playerPos);
	if(m_visible)
		m_pPlayer->Draw();
}

void CPlayerBody::DrawShadow()
{
	POINT pos = m_playerPos;
	pos.x += 13;
	pos.y += 38;
	m_pPlayerShadow->SetDesPos(pos);
	m_pPlayerShadow->Draw();
}

void CPlayerBody::Update()
{
	m_pPlayer->UpdateMAatrix();
	m_pPlayerShadow->UpdateMAatrix();
	switch (m_playerDir)
	{
	case eNONE:
		m_pPlayer->UpdateSrcPos(0, 0);
		ReSet(0, 0, 0, 0, 0, 0);
		break;
	case eUP:
		if (m_bIsReset)
		{
			m_bIsReset = false;
			ReSet(1, 0, 0, 3, 0, 1);
		}
		break;
	case eDOWN:
		if (m_bIsReset)
		{
			m_bIsReset=false;
			ReSet(1, 0, 0, 3, 0, 1);
		}
		break;
	case eLEFT:
		if (m_bIsReset)
		{
			m_bIsReset=false;
			ReSet(7, 3, 7, 4, 3, 4);
		}
		break;
	case eRIGHT:
		if (m_bIsReset)
		{
			m_bIsReset=false;
			ReSet(0, 3, 0, 3, 3, 4);
		}
		break;
	}
	m_count++;
	if (m_count%m_updateRate == 0)
		m_pPlayer->Update();
}

void CPlayerBody::SetUpdateRate(WORD rate)
{
	m_updateRate = rate;
}

void CPlayerBody::OnKeyDown(SEvent event)
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
		}
	}
}

void CPlayerBody::OnKeyUp(SEvent event)
{
	if (!event.keyInput.pressedDown)
	{
		switch(event.keyInput.key)
		{
		case 'W':
			m_playerDir-=eUP;
			m_bIsReset = true;
			break;
		case 'S':
			m_playerDir-=eDOWN;
			m_bIsReset = true;
			break;
		case 'A':
			m_playerDir-=eLEFT;
			m_bIsReset = true;
			break;
		case 'D':
			m_playerDir-=eRIGHT;
			m_bIsReset = true;
			break;
		}
	}
}

void CPlayerBody::UpdateBodyRect()
{
	int x = m_pPlayer->GetDesPos().x + 20;
	int y = m_pPlayer->GetDesPos().y + 25;
	m_bodyRect.top=y;
	m_bodyRect.left = x;
	m_bodyRect.right = x+24;
	m_bodyRect.bottom = y+25;
}

void CPlayerBody::UpdateBodyCollision()
{
	int x = m_playerPos.x;
	int y = m_playerPos.y;
	m_bodyRectCollision.top = y;
	m_bodyRectCollision.left = x;
	m_bodyRectCollision.right = x + m_pPlayer->GetFrameWidth();
	m_bodyRectCollision.bottom = y + m_pPlayer->GetFrameHeight();
}

RECT CPlayerBody::GetBodyRect()
{
	return m_bodyRect;
}

RECT CPlayerBody::GetBodyCollision()
{
	return m_bodyRectCollision;
}