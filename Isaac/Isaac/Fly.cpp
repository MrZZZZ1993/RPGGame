#include "stdafx.h"
#include "Fly.h"


CFly::CFly()
{
	m_pFly = nullptr;
	m_pFlyDead = nullptr;
	m_targetAngle = 0;
	m_angle = 0;
	speed=5;
	m_visible=true;
	m_curFrame=0;
	m_curRow=0;
	m_hp=0;
	m_isDead = false;
	m_curDeadFrame=0;
	m_curDeadRow=1;
	m_damage = 0;
}

CFly::~CFly()
{
	delete m_pFly;
	delete m_pFlyDead;
}

void CFly::Init(TSTRING name)
{
	m_pFly = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pFly->Init();
	m_pFly->SetShowWidth(m_pFly->GetFrameWidth());
	m_pFly->SetShowHeight(m_pFly->GetFrameHeight());
	m_pFly->ReSet(0, 0, 0, 3, 0, 1);
	m_pFly->UpdateMAatrix();

	m_pFlyDead = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("Fly1"));
	m_pFlyDead->Init();
	m_pFlyDead->SetShowWidth(m_pFlyDead->GetFrameWidth());
	m_pFlyDead->SetShowHeight(m_pFlyDead->GetFrameHeight());
	m_pFlyDead->ReSet(0, 1, 0, 3, 1, 3);
	POINT pos = { m_pFlyDead->GetCurFrame()*m_pFlyDead->GetFrameWidth(), m_pFlyDead->GetCurRow()*m_pFlyDead->GetFrameHeight() };
	m_pFlyDead->SetSrcPos(pos);
	m_pFlyDead->UpdateMAatrix();


	star.Init("Stone1.bin");
	
	AStarCount=0;
	
	//int endX = 4;
	//int endY = 8;

	//int startX=3;
	//int startY=3;


	//star.SetOC(endX,endY);
	//star.Process(endX,endY, star.FindNode(startX, startY));
	//star.FindWay(star.FindNode(startX, startY));
	//temp = star.FindNode(startX, startY);//从终点节点起
}

void CFly::Draw()
{
	if(m_visible)
	{
		if (!m_isDead)
		{
			m_pFly->SetDesPos(m_pos);
			m_pFly->Draw();
		}
		else
		{
			m_pFlyDead->SetDesPos(m_deadPos);
			m_pFlyDead->Draw();
		}
	}
}

void CFly::Update()
{
	if(m_visible&&!m_isDead)
	{
		Move();
		//AStarMove();
		m_pFly->SetCurRow(m_curRow);
		m_pFly->SetCurFrame(m_curFrame);
		m_pFly->Update();

		m_curFrame++;
		if(m_curFrame==3)
		{
			m_curFrame=0;
			m_curRow++;
			if(m_curRow==2)
				m_curRow=0;
		}
	}
	else if (m_visible&&m_isDead)
	{
		m_pFlyDead->SetCurRow(m_curDeadRow);
		m_pFlyDead->SetCurFrame(m_curDeadFrame);
		m_pFlyDead->Update();

		m_curDeadFrame++;
		if (m_curDeadFrame == 3)
		{
			m_curDeadFrame = 0;
			m_curDeadRow++;
		}
		if (m_pFlyDead->GetCurFrame() == 3 && m_pFlyDead->GetCurRow() == 3)
		{
			m_visible = false;
			m_isDead=false;
			m_curDeadFrame = 0;
			m_curDeadRow = 1;
		}
	}
}

void CFly::Move()
{
	POINT playerPos = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerPos();
	int x = playerPos.x;
	int y = playerPos.y;
	D3DXVECTOR2 vecPlayer;
	D3DXVECTOR2 vecFly;
	vecPlayer.x = x;
	vecPlayer.y = y;
	vecFly.x = m_pos.x;
	vecFly.y = m_pos.y;
	D3DXVECTOR2 vec = vecPlayer - vecFly;
	D3DXVec2Normalize(&vec, &vec);

	if (vec.y == 0.f)
	{
		if (vec.x > 0.f)
			m_targetAngle = 0.0f;
		else
			m_targetAngle = D3DX_PI;
	}
	else if (vec.y > 0.f)
		m_targetAngle = acosf(vec.x);
	else
		m_targetAngle = acosf(-vec.x) + D3DX_PI;

	float turnSpeed = 0.05;
	if (m_targetAngle != m_angle)
	{
		float fFacing = m_targetAngle;
		if (m_targetAngle > m_angle)
			fFacing -= 2 * D3DX_PI;

		float fDiff = m_angle - fFacing;
		if (fDiff < D3DX_PI)
		{
			if (m_angle - turnSpeed <= fFacing)
				m_angle = m_targetAngle;
			else
				m_angle = float(m_angle - turnSpeed);
		}
		else
		{
			if (m_angle + turnSpeed - 2 * D3DX_PI >= fFacing)
				m_angle = m_targetAngle;
			else
				m_angle = float(m_angle + turnSpeed);
		}
	}

	float fDist = D3DXVec2Length(&(vecPlayer - vecFly));

	if (5 >= fDist)
	{
		vecFly=vecPlayer;
	}
	else
	{
		D3DXMATRIX m;
		D3DXVECTOR2 pv = D3DXVECTOR2(1.0f, 0.0f);
		D3DXVec2TransformCoord(&pv, &pv, D3DXMatrixRotationZ(&m, m_angle));
		vecFly += pv*speed;;
	}
	m_pos.x = vecFly.x;
	m_pos.y = vecFly.y;


	m_deadPos.x = m_pos.x - 40;
	m_deadPos.y = m_pos.y - 40;
	m_pFlyDead->SetDesPos(m_deadPos);
}

void CFly::MoveOnMap()
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

void CFly::SetDir(int dir)
{
	m_dir = dir;
}

void CFly::SetPos(POINT pos)
{
	m_pos=pos;
}

void CFly::SetDesPos(POINT pos)
{
	m_pFly->SetDesPos(pos);
}
 
void CFly::SetSpeed(int s)
{
	speed=s;
}

void CFly::SetMapIndex(int a)
{
	m_mapIndex=a;
}

void CFly::SetVisible(bool b)
{
	m_visible = b;
}

void CFly::UpdateFlyRect()
{
	int x = m_pos.x + 23;
	int y = m_pos.y + 18;
	m_flyRect.top = y;
	m_flyRect.left = x;
	m_flyRect.right = x + 22;
	m_flyRect.bottom = y + 22;
}

void CFly::ReSet(WORD curFrame, WORD curRow, WORD startFrame, WORD endFrame, WORD startRow, WORD endRow)
{
	m_pFly->ReSet(curFrame, curRow, startFrame, endFrame, startRow, endRow);
}

void CFly::SetHP(int hp)
{
	m_hp=hp;
}

void CFly::SetIsDead(bool b)
{
	m_isDead = b;
}

void CFly::SetDamage(int d)
{
	m_damage = d;
}

int CFly::GetDamage()
{
	return m_damage;
}

int CFly::GetHP()
{
	return m_hp;
}

bool CFly::GetVisible()
{
	return m_visible;
}

int CFly::GetMapIndex()
{
	return m_mapIndex;
}

RECT CFly::GetFlyRect()
{
	return m_flyRect;
}

POINT CFly::GetPos()
{
	return m_pos;
}

void CFly::AStarMove()
{
	int startX;
	int startY;
	int endX;
	int endY;
	CNode*node;
	node = star.FindNode(m_pos.y / 64, m_pos.x / 64);//从终点节点起
	if (AStarCount  %30== 0&&node->GetCON()==32)
	{
		if (AStarCount > 0)
		{
			star.ReSet();
		}

		POINT playerPos = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerPos();

		endX = playerPos.y / 64;
		endY = playerPos.x / 64;

		startX = m_pos.y / 64;
		startY = m_pos.x / 64;

		star.SetOC(endX,endY);
		star.Process(endX,endY, star.FindNode(startX, startY));
		star.FindWay(star.FindNode(startX, startY));
		temp = star.FindNode(startX, startY);//从终点节点起
		temp = temp->GetFather();
	}

	AStarCount++;

	vecFly.x = m_pos.x;
	vecFly.y = m_pos.y;

	if (temp != nullptr)
	{
		vecPlayer.x = temp->GetY() * 64+32;
		vecPlayer.y = temp->GetX() * 64+32;
	}

	D3DXVECTOR2 vec = vecPlayer - vecFly;
	
	float fDist = D3DXVec2LengthSq(&vec);
	
	if (5 >= fDist)
	{
		vecFly=vecPlayer;
		if (temp != nullptr)
		{
			temp1=temp;
			temp = temp->GetFather();
		}
	}
	else
	{
		D3DXVec2Normalize(&vec, &vec);
		vecFly += vec*speed;
	}
	m_pos.x = vecFly.x;
	m_pos.y = vecFly.y;
}