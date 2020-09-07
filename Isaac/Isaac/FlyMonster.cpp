#include "stdafx.h"
#include "FlyMonster.h"


CFlyMonster::CFlyMonster(void)
{
	m_pPic=nullptr;
	speed=5;
	m_fHalfWidth=15;
	m_dir = 0;
	m_mapIndex=0;
	m_visible = true;
	m_damage = 0;
	m_isRed = false; 
	m_curFrame = 0;
}

CFlyMonster::~CFlyMonster(void)
{
	delete m_pPic;
}

void CFlyMonster::Init(TSTRING name)
{
	m_pPic = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	POINT pos = { 110, 110 };
	m_pPic->SetDesPos(pos);
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->ReSet(0, 0, 0, 1, 0, 0);
	m_pPic->SetCenter(m_pPic->GetFrameWidth()/2,m_pPic->GetFrameHeight()/2);
	m_pPic->UpdateMAatrix();


	dir.x = 1.0f;
	dir.y = 0.5f;

	m_pos.x=110;
	m_pos.y=110;
}

void CFlyMonster::Draw()
{
	POINT pos;
	if (m_visible)
	{
		if (m_isRed)
			m_pPic->SetAddColor(0xff0000);
		else
			m_pPic->SetAddColor(0xffffff);
		pos.x = m_pos.x;
		pos.y = m_pos.y;
		m_pPic->SetDesPos(pos);
		m_pPic->Draw();
	}
}

void CFlyMonster::Update()
{
	if (m_visible)
	{
		m_pPic->SetCurFrame(m_curFrame);
		m_pPic->Update();
		m_curFrame++;
		if (m_curFrame == 2)
			m_curFrame = 0;
	}
}

void CFlyMonster::Move(Map*pMap)
{
	if (m_visible)
	{
		int x = pMap->GetSrcPos().x;
		int y = pMap->GetSrcPos().y;
		point[0].x = 64.0f - x;
		point[0].y = 64.0f - y;
		point[1].x = pMap->GetWidth() - 64 - x;
		point[1].y = 64.0f - y;
		point[2].x = pMap->GetWidth() - 64 - x;
		point[2].y = pMap->GetHeight() - 64 - y;
		point[3].x = 64.0f - x;
		point[3].y = pMap->GetHeight() - 64 - y;
		point[4].x = 64.0f - x;
		point[4].y = 64.0f - y;

		for (int i = 0; i < 4; i++)
		{
			CTool::ComputeLine(&line[i], point[i], point[i + 1]);
		}

		D3DXVECTOR2 vNextPos = m_pos;
		vNextPos += dir * speed;

		for (int i = 0; i < 4; i++)
		{
			D3DXVECTOR2 pointMinDistAtLine;
			pointMinDistAtLine = CTool::MinDistancePointToLine(&vNextPos, &line[i]);

			if (CTool::DistancePointToLine(&vNextPos, &line[i])>0 && CTool::DistancePointToLine(&vNextPos, &line[i]) < m_fHalfWidth /*&&
																													  DistancePointToLine(&pos, &line[i]) < m_fHalfWidth*/)
			{
				CTool::Vector2Reflect(&dir, &line[i].vNormal, &dir);
				return;
			}
			else if (CTool::DistancePointToLine(&vNextPos, &line[i])<0 && CTool::DistancePointToLine(&vNextPos, &line[i]) > -m_fHalfWidth /* &&
																															DistancePointToLine(&pos, &line[i]) < -m_fHalfWidth*/)//±³Ãæ·´µ¯
			{
				CTool::Vector2Reflect(&dir, &line[i].vNormal, &dir);
				return;
			}

		}
		m_pos = vNextPos;
	}
}

void CFlyMonster::MoveOnMap()
{
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	switch (m_dir)
	{
	case eNONE:
		m_pos.x = m_pos.x;
		m_pos.y = m_pos.y;
		break;
	case eUP:
		m_pos.y = m_pos.y - speed;
		break;
	case eDOWN:
		m_pos.y = m_pos.y + speed;
		break;
	case eLEFT:
		m_pos.x = m_pos.x - speed;
		break;
	case eRIGHT:
		m_pos.x = m_pos.x + speed;
		break;
	case eUP | eLEFT:
		m_pos.y = m_pos.y - speed;
		m_pos.x = m_pos.x - speed;
		break;
	case eDOWN | eLEFT:
		m_pos.y = m_pos.y + speed;
		m_pos.x = m_pos.x - speed;
		break;
	case eUP | eRIGHT:
		m_pos.y = m_pos.y - speed;
		m_pos.x = m_pos.x + speed;
		break;
	case eDOWN | eRIGHT:
		m_pos.y = m_pos.y + speed;
		m_pos.x = m_pos.x + speed;
		break;
	}
}

void CFlyMonster::SetDir(int dir)
{
	m_dir = dir;
}

void CFlyMonster::SetDesPos(POINT pos)
{
	m_pPic->SetDesPos(pos);
}

void CFlyMonster::SetPos(POINT pos)
{
	m_pos.x=pos.x;
	m_pos.y=pos.y;
}

void CFlyMonster::SetSpeed(int s)
{
	speed=s;
}

void CFlyMonster::SetHalfWidth(int s)
{
	m_fHalfWidth=s;
}

void CFlyMonster::SetAngleDir(D3DXVECTOR2 d)
{
	dir=d;
}

void CFlyMonster::SetMapIndex(int a)
{
	m_mapIndex=a;
}

void CFlyMonster::SetVisible(bool b)
{
	m_visible = b;
}

void CFlyMonster::SetAddColor(long color)
{
	m_pPic->SetAddColor(color);
}

void CFlyMonster::SetHP(int hp)
{
	m_hp=hp;
}

void CFlyMonster::SetDamage(int d)
{
	m_damage = d;
}

void CFlyMonster::UpdateFlyMonsterRect()
{
	int x = m_pos.x - 15;
	int y = m_pos.y - 15;
	rc.top = y;
	rc.left = x;
	rc.bottom = y + 30;
	rc.right = x + 30;
}

void CFlyMonster::SetIsRed(bool b)
{
	m_isRed = b;
}

int CFlyMonster::GetDamage()
{
	return m_damage;
}

int CFlyMonster::GetHP()
{
	return m_hp;
}

bool CFlyMonster::GetVisible()
{
	return m_visible;
}

int CFlyMonster::GetMapIndex()
{
	return m_mapIndex;
}

int CFlyMonster::GetWidth()
{
	return m_pPic->GetPicWidth();
}

int CFlyMonster::GetFrameWidth()
{
	return m_pPic->GetFrameWidth();
}

long CFlyMonster::GetAddColor()
{
	return m_pPic->GetAddColor();
}

RECT CFlyMonster::GetFlyMonsterRect()
{
	return rc;
}

bool CFlyMonster::GetIsRed()
{
	return m_isRed;
}

int CFlyMonster::GetPosX()
{
	return m_pos.x;
}

int CFlyMonster::GetPosY()
{
	return m_pos.y;
}