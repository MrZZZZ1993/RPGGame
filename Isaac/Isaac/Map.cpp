#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	m_pMap=nullptr;
	m_mapDir = eNONE;
	m_mapIndex = 0;
	m_visible = true;
}

Map::~Map()
{
	delete m_pMap;
}

void Map::Init(TSTRING name)
{
	m_pMap=(CStaticImg*)CResManager::GetInstance()->GetRes(name);
	m_pMap->Init();
}

void Map::Draw()
{
	m_pMap->Draw();
}

void Map::InitTileMap(const char* name)
{
	m_pMap->ReadTileMap(name);
}

void Map::DrawTileMap(POINT picSrcPos)
{
	if (m_visible)
		m_pMap->DrawTileMap(picSrcPos);
}

void Map::SetShowWidth(WORD width)
{
	m_pMap->SetShowWidth(width);
}

void Map::SetShowHeight(WORD height)
{
	m_pMap->SetShowHeight(height);
}

void Map::Update()
{
	POINT pos = { 0, 0 };
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	switch (m_mapDir)
	{
	case eNONE:
		pos.x = m_pMap->GetSrcPos().x;
		pos.y = m_pMap->GetSrcPos().y;
		break;
	case eUP:
		pos.y = m_pMap->GetSrcPos().y - speed;
		pos.x = m_pMap->GetSrcPos().x;
		break;
	case eDOWN:
		pos.y = m_pMap->GetSrcPos().y + speed;
		pos.x = m_pMap->GetSrcPos().x;
		break;
	case eLEFT:
		pos.x = m_pMap->GetSrcPos().x - speed;
		pos.y = m_pMap->GetSrcPos().y;
		break;
	case eRIGHT:
		pos.x = m_pMap->GetSrcPos().x + speed;
		pos.y = m_pMap->GetSrcPos().y;
		break;
	case eUP | eLEFT:
		pos.y = m_pMap->GetSrcPos().y - speed;
		pos.x = m_pMap->GetSrcPos().x - speed;
		break;
	case eDOWN | eLEFT:
		pos.y = m_pMap->GetSrcPos().y + speed;
		pos.x = m_pMap->GetSrcPos().x - speed;
		break;
	case eUP | eRIGHT:
		pos.y = m_pMap->GetSrcPos().y - speed;
		pos.x = m_pMap->GetSrcPos().x + speed;
		break;
	case eDOWN | eRIGHT:
		pos.y = m_pMap->GetSrcPos().y + speed;
		pos.x = m_pMap->GetSrcPos().x + speed;
		break;
	}
	m_pMap->SetSrcPos(pos);
}

void Map::UpdateMAatrix()
{
	m_pMap->UpdateMAatrix();
}

void Map::SetMapDir(int dir)
{
	m_mapDir = dir;
}

void Map::SetDesPos(POINT desPos)
{
	m_pMap->SetDesPos(desPos);
}

void Map::SetSrcPos(POINT srcPos)
{
	m_pMap->SetSrcPos(srcPos);
}

void Map::SetMap(int row, int col, int num)
{
	m_pMap->SetTile(row, col, num);
}

void Map::SetMapIndex(int index)
{
	m_mapIndex = index;
}

void Map::SetMapType(int a)
{
	m_mapType=a;
}

void Map::SetScale(float x, float y)
{
	m_pMap->SetXScale(x);
	m_pMap->SetYScale(y);
}

void Map::SetCenter(int x, int y)
{
	m_pMap->SetCenter(x, y);
}

void Map::SetMove(int x, int y)
{
	m_pMap->SetMove(x, y);
}

void Map::SetAngle(float angle)
{
	m_pMap->SetAngle(angle);
}

void Map::SetTransparent(long a)
{
	m_pMap->SetTrasparent(a);
}

void Map::SetVisible(bool b)
{
	m_visible = b;
}

bool Map::GetVisible()
{
	return m_visible;
}

WORD Map::GetWidth()
{
	return m_pMap->GetPicWidth();
}

WORD Map::GetHeight()
{
	return m_pMap->GetPicHeight();
}

POINT Map::GetDesPos()
{
	return m_pMap->GetDesPos();
}

POINT Map::GetSrcPos()
{
	return m_pMap->GetSrcPos();
}

int Map::GetMap(int row,int col)
{
	return m_pMap->GetTile(row,col);
}

int Map::GetMapType()
{
	return m_mapType;
}

int Map::GetMapIndex()
{
	return m_mapIndex;
}