#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
{
	m_door=nullptr;
	m_doorType = 0;
	m_visible = true;
}

CDoor::~CDoor()
{
	delete m_door;
}

void CDoor::Init(TSTRING name)
{
	m_door=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_door->Init();
	m_door->SetShowWidth(m_door->GetFrameWidth());
	m_door->SetShowHeight(m_door->GetFrameHeight());
	m_door->UpdateMAatrix();
}

void CDoor::Draw()
{
	m_door->SetDesPos(m_pos);
	if (m_visible)
		m_door->Draw();
}

void CDoor::Update()
{
	m_door->Update();
}

void CDoor::ReSet(WORD curFrame, WORD curRow, WORD startFrame, WORD endFrame, WORD startRow, WORD endRow)
{
	m_door->ReSet( curFrame,curRow,startFrame,endFrame,startRow,endRow);
}

void CDoor::SetDesPos(POINT pos)
{
	m_door->SetDesPos(pos);
}

void CDoor::SetDoorIndex(int i)
{
	m_doorIndex=i;
}

void CDoor::SetSrcPos(POINT pos)
{
	m_door->SetSrcPos(pos);
}

void CDoor::SetPos(POINT pos)
{
	m_pos=pos;
}

void CDoor::MoveOnMap()
{
	POINT pos = { 0, 0 };
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	if (m_visible)
	{
		switch (m_dirOnMap)
		{
		case eNONE:
			pos.x = m_pos.x;
			pos.y = m_pos.y;
			break;
		case eUP:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x;
			break;
		case eDOWN:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x;
			break;
		case eLEFT:
			pos.x = m_pos.x - speed;
			pos.y = m_pos.y;
			break;
		case eRIGHT:
			pos.x = m_pos.x + speed;
			pos.y = m_pos.y;
			break;
		case eUP | eLEFT:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x - speed;
			break;
		case eDOWN | eLEFT:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x - speed;
			break;
		case eUP | eRIGHT:
			pos.y = m_pos.y - speed;
			pos.x = m_pos.x + speed;
			break;
		case eDOWN | eRIGHT:
			pos.y = m_pos.y + speed;
			pos.x = m_pos.x + speed;
			break;
		}
		m_pos = pos;
	}
}

void CDoor::SetDir(int i)
{
	m_dirOnMap = i;
}

void CDoor::SetVisible(bool b)
{
	m_visible = b;
}

void CDoor::SetDoorType(int i)
{
	m_doorType = i;
}

int CDoor::GetFrameWidth()
{
	return m_door->GetFrameWidth();
}

int CDoor::GetFrameHeight()
{
	return m_door->GetFrameHeight();
}

int CDoor::GetDoorType()
{
	return m_doorType;
}

int CDoor::GetDoorIndex()
{
	return m_doorIndex;
}

int CDoor::GetCurFrame()
{
	return m_door->GetCurFrame();
}

int CDoor::GetCurRow()
{
	return m_door->GetCurRow();
}

POINT CDoor::GetDesPos()
{
	return m_door->GetDesPos();
}

bool CDoor::GetVisible()
{
	return m_visible;
}