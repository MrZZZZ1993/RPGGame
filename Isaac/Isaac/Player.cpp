#include "stdafx.h"
#include "Player.h"
#include "PlayerBody.h"

CPlayer::CPlayer()
{
	m_playerDir=eNONE;
	top=true;
	bottom=false;
	left=true;
	right=true;
	m_visible=true;
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetPlayerSpeed(WORD speed)
{
	m_playerSpeed = speed;
}

void CPlayer::SetTop(Map*pMap,int tileWidth,int num)
{
	POINT pos = pMap->GetSrcPos();
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->UpdateBodyRect();
	RECT rect = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetBodyRect();

	for (int i = rect.left; i <= rect.right; i++)
	{
		int x = (rect.top + pos.y - m_playerSpeed) / tileWidth;
		int y = (i + pos.x) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y)==24||!m_isRun)
			top = true;
		else
		{
			top = false;
			break;
		}
	}
}

void CPlayer::SetBottom(Map*pMap,int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->UpdateBodyRect();
	RECT rect = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetBodyRect();

	for (int i = rect.left; i <= rect.right; i++)
	{
		int x = (rect.bottom + pos.y + m_playerSpeed) / tileWidth;
		int y = (i + pos.x) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y)==24||!m_isRun)
			bottom = true;
		else
		{
			bottom = false;
			break;
		}
	}
}

void CPlayer::SetLeft(Map*pMap, int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->UpdateBodyRect();
	RECT rect = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetBodyRect();

	for (int i = rect.top; i <= rect.bottom; i++)
	{
		int x = (i + pos.y) / tileWidth;
		int y = (rect.left + pos.x - m_playerSpeed) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y)==24||!m_isRun)
			left = true;
		else
		{
			left = false;
			break;
		}
	}
}

void CPlayer::SetRight(Map*pMap, int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->UpdateBodyRect();
	RECT rect = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetBodyRect();

	for (int i = rect.top; i <= rect.bottom; i++)
	{
		int x = (i + pos.y) / tileWidth;
		int y = (rect.right + pos.x + m_playerSpeed) / tileWidth;
		if (pMap->GetMap(x, y) == num||pMap->GetMap(x, y)==24||!m_isRun)
			right = true;
		else
		{
			right = false;
			break;
		}
	}
}

void CPlayer::Move(Map*pMap, int tileWidth, int num)
{
	POINT pos = pMap->GetSrcPos();
	CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->UpdateBodyRect();
	RECT rect = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetBodyRect();
	
	
	SetTop(pMap, tileWidth,num);
	SetBottom(pMap, tileWidth, num);
	SetLeft(pMap, tileWidth, num);
	SetRight(pMap, tileWidth, num);

	switch (m_playerDir)
	{
	case eNONE:
		break;
	case eUP:
		if (rect.top>96&&top)
		m_playerPos.y -= m_playerSpeed;
		break;
	case eDOWN:
		if (rect.bottom<480&&bottom)
		m_playerPos.y += m_playerSpeed;
		bottom=false;
		break;
	case eLEFT:
		if (rect.left>96&&left)
		m_playerPos.x -= m_playerSpeed;
		break;
	case eRIGHT:
		if (rect.right<739&&right)
		m_playerPos.x += m_playerSpeed;
		break;
	case eUP | eLEFT:
		if (rect.top>96)
		m_playerPos.y -= m_playerSpeed;
		if (rect.left>96)
		m_playerPos.x -= m_playerSpeed;
		break;
	case eDOWN | eLEFT:
		if (rect.bottom<480)
		m_playerPos.y += m_playerSpeed;
		if (rect.left>96)
		m_playerPos.x -= m_playerSpeed;
		break;
	case eUP | eRIGHT:
		if (rect.top>96)
		m_playerPos.y -= m_playerSpeed;
		if (rect.right<739)
		m_playerPos.x += m_playerSpeed;
		break;
	case eDOWN | eRIGHT:
		if (rect.bottom<480)
		m_playerPos.y += m_playerSpeed;
		if (rect.right<736)
		m_playerPos.x += m_playerSpeed;
		break;
	}
}

void CPlayer::SetIsRun(bool b)
{

	m_isRun=b;
}

void CPlayer::ReSet(WORD curFrame, WORD curRow, WORD startFrame, WORD endFrame, WORD startRow, WORD endRow)
{
	m_pPlayer->SetCurFrame(curFrame);
	m_pPlayer->SetCurRow(curRow);
	m_pPlayer->SetStartFrame(startFrame);
	m_pPlayer->SetEndFrame(endFrame);
	m_pPlayer->SetStartRow(startRow);
	m_pPlayer->SetEndRow(endRow);
}

void CPlayer::SetDir(int dir)
{
	m_playerDir = dir;
}

void CPlayer::SetPos(POINT pos)
{
	m_playerPos=pos;
}

void CPlayer::SetDesPos(POINT pos)
{
	m_pPlayer->SetDesPos(pos);
}

void CPlayer::SetVisible(bool b)
{
	m_visible=b;
}

bool CPlayer::GetVisible()
{
	return m_visible;
}

bool CPlayer::GetIsRun()
{
	return m_isRun;
}

POINT CPlayer::GetPlayerPos()
{
	return m_playerPos;
}

int CPlayer::GetPlayerDir()
{
	return m_playerDir;
}

WORD CPlayer::GetPlayerSpeed()
{
	return m_playerSpeed;
}

bool CPlayer::GetBottom()
{
	return bottom;
}

bool CPlayer::GetTop()
{
	return top;
}

bool CPlayer::GetLeft()
{
	return left;
}

bool CPlayer::GetRight()
{
	return right;
}

int CPlayer::GetPicHeight()
{
	return m_pPlayer->GetPicHeight();
}

int CPlayer::GetPicWidth()
{
	return m_pPlayer->GetPicWidth();
}

DWORD CPlayer::GetColorValue(POINT pos)
{
	return m_pPlayer->GetColorValue(pos);
}
