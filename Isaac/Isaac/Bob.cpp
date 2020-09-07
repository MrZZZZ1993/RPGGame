#include "stdafx.h"
#include "Bob.h"


CBob::CBob()
{
	m_pHead = nullptr;
	m_pBody = nullptr;
	AStarCount=0;
	m_dir=eLEFT;
	m_leftCount=0;
	m_rightCount=0;
	m_isRed=false;
	m_updateCount=0;
}

CBob::~CBob()
{
	delete m_pHead;
	delete m_pBody;
}

void CBob::Init(TSTRING name)
{
	m_pHead = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pHead->Init();
	m_pHead->SetShowWidth(m_pHead->GetFrameWidth());
	m_pHead->SetShowHeight(m_pHead->GetFrameHeight());
	m_pHead->SetCenter(m_pHead->GetFrameWidth() / 2, m_pHead->GetFrameHeight() / 2);
	m_pHead->UpdateMAatrix();

	m_pBody = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("BobBody"));
	m_pBody->Init();
	m_pBody->SetShowWidth(m_pBody->GetFrameWidth());
	m_pBody->SetShowHeight(m_pBody->GetFrameHeight());
	m_pBody->SetCenter(m_pBody->GetFrameWidth() / 2, m_pBody->GetFrameHeight() / 2);
	m_pBody->UpdateMAatrix();

}

void CBob::InitAStar(const char*c)
{
	star.Init(c);
}

void CBob::Draw()
{
	if (m_visible)
	{
		if (m_isRed)
		{
			m_pHead->SetAddColor(0xff0000);
			m_pBody->SetAddColor(0xff0000);
		}
		else
		{
			m_pHead->SetAddColor(0xffffff);
			m_pBody->SetAddColor(0xffffff);
		}
		m_pBody->SetDesPos(m_pos);
		m_headPos.x=m_pos.x;
		m_headPos.y=m_pos.y-29;
		m_pHead->SetDesPos(m_headPos);
		m_pBody->Draw();
		m_pHead->Draw();
	}
}

void CBob::Update()
{
	m_updateCount++;
	if (m_visible&&m_updateCount==5)
	{
		m_updateCount=0;
		switch (m_dir)
		{
		case eLEFT:
			if(m_leftCount==0)
			{
				m_pBody->ReSet(0,3,0,3,3,4);
				m_leftCount++;
			}
			break;
		case eRIGHT:
			if(m_rightCount==0)
			{
				m_pBody->ReSet(7,3,7,4,3,4);
				m_rightCount++;
			}
			break;
		}
		m_pBody->Update();
		m_pHead->Update();
	}
}

void CBob::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CBob::SetPos(POINT pos)
{
	m_pos = pos;
}

void CBob::SetSpeed(int i)
{
	m_speed = i;
}

void CBob::SetVisible(bool b)
{ 
	m_visible = b;
}

void CBob::SetDamage(int i)
{
	m_damage=i;
}

void CBob::AStarMove(Map*stone)
{
	int startX=0;
	int startY=0;
	int endX=0;
	int endY=0;
	int x=stone->GetSrcPos().x;
	int y=stone->GetSrcPos().y;
	CNode*node;
	node = star.FindNode((m_pos.y+y) / 64, (m_pos.x+x) / 64);
	playerPos.x = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerPos().x+30;
	playerPos.y = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerPos().y+35;
	if (AStarCount  %20== 0&&node->GetCON()==32)
	{
		if (AStarCount > 0)
		{
			star.ReSet();
		}

		startX = (m_pos.y + y) / 64;
		startY = (m_pos.x + x) / 64;

		endX = (playerPos.y + y) / 64;
		endY = (playerPos.x + x) / 64;

		

		if(playerPos.x>m_pos.x)
		{
			m_dir=eLEFT;
			m_rightCount=0;
		}
		else
		{
			m_dir=eRIGHT;
			m_leftCount=0;
		}

		if(fabs(float(playerPos.x-m_pos.x))<=200&&fabs(float(playerPos.y-m_pos.y))<=200)
		{
			m_pHead->ReSet(1,1,1,1,1,1);
		}

		star.SetOC(endX,endY);
		star.Process(endX,endY, star.FindNode(startX, startY));
		star.FindWay(star.FindNode(startX, startY));
		temp = star.FindNode(startX, startY);
		temp = temp->GetFather();
	}

	AStarCount++;


	vecFly.x = m_pos.x;
	vecFly.y = m_pos.y;

	if (temp != nullptr)
	{
		vecPlayer.x = temp->GetY() * 64-x+32;
		vecPlayer.y = temp->GetX() * 64-y+32;
	}

	D3DXVECTOR2 vec = vecPlayer - vecFly;

	float fDist = D3DXVec2Length(&vec);

	if (m_speed >= fDist)
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
		vecFly += vec*m_speed;
	}
	m_pos.x = vecFly.x;
	m_pos.y = vecFly.y;
}

void CBob::ReSet(int curFrame,int curRow,int startFrame,int endFrame,int startRow,int endRow)
{
	m_pBody->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
}

void CBob::SetDir(int i)
{
	m_dirOnMap=i;
}

void CBob::MoveOnMap()
{
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	switch (m_dirOnMap)
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

void CBob::SetAnddColor(long l)
{
	m_pHead->SetAddColor(l);
	m_pBody->SetAddColor(l);
}

void CBob::SetHP(int i)
{
	m_hp=i;
}

void CBob::UpdateRect()
{
	int x=m_headPos.x-25;
	int y=m_headPos.y-26;
	m_headRc.left=x;
	m_headRc.top=y;
	m_headRc.bottom=y+52;
	m_headRc.right=x+50;

	int x1=m_pos.x-17;
	int y1=m_pos.y-10;
	m_bodyRc.left=x1;
	m_bodyRc.right=x1+34;
	m_bodyRc.top=y1;
	m_bodyRc.bottom=y1+20;
}

void CBob::SetIsRed(bool b)
{
	m_isRed=b;
}

bool CBob::GetIsRed()
{
	return m_isRed;
}

int CBob::GetSpeed()
{
	return m_speed;
}

int CBob::GetMapIndex()
{
	return m_mapIndex;
}

bool CBob::GetVisible()
{
	return m_visible;
}

POINT CBob::GetPos()
{
	return m_pos;
}

int CBob::GetDamage()
{
	return m_damage;
}

int CBob::GetHp()
{
	return m_hp;
}

long CBob::GetAddColor()
{
	return m_pHead->GetAddColor();
}

RECT CBob::GetHeadRect()
{
	return m_headRc;
}

RECT CBob::GetBodyRect()
{
	return m_bodyRc;
}