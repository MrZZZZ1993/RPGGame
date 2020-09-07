#include "stdafx.h"
#include "Mask.h"


CMask::CMask()
{
	m_pPic=nullptr;
	m_speedPursue=0;
	m_speedNormal=0;
	m_isPursue=0;
	m_aimPos=0;
	m_isUpdate=true;
	m_isRed=false;
	m_dir=eRIGHT;
	m_visible = true;
}

CMask::~CMask()
{
	delete m_pPic;
}

void CMask::Init(TSTRING name)
{
	m_pPic = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->SetCenter(m_pPic->GetFrameWidth()/2,m_pPic->GetFrameHeight()/2);
	m_pPic->UpdateMAatrix();
}

void CMask::Draw()
{
	if (m_visible)
	{
		POINT pos;
		int width=m_pPic->GetFrameWidth();
		int height=m_pPic->GetFrameHeight();
		switch (m_dir)
		{
		case eUP:
			pos.x=0;
			pos.y=height;
			m_pPic->SetSrcPos(pos);
			break;
		case eDOWN:
			pos.x=0;
			pos.y=0;
			m_pPic->SetSrcPos(pos);
			break;
		case eLEFT:
			pos.x=width;
			pos.y=height;
			m_pPic->SetSrcPos(pos);
			break;
		case eRIGHT:
			pos.x=width;
			pos.y=0;
			m_pPic->SetSrcPos(pos);
			break;
		}
		m_pPic->SetDesPos(m_pos);
		if(m_isRed)
			m_pPic->SetAddColor(0xff0000);
		else
			m_pPic->SetAddColor(0xffffff);
		m_pPic->Draw();
	}
}

void CMask::Update()
{
	POINT pos;
	int width=m_pPic->GetFrameWidth();
	int height=m_pPic->GetFrameHeight();
	if(m_visible)
	{
		switch (m_dir)
		{
		case eUP:
			pos.x=0;
			pos.y=height;
			m_pPic->SetSrcPos(pos);
			break;
		case eDOWN:
			pos.x=0;
			pos.y=0;
			m_pPic->SetSrcPos(pos);
			break;
		case eLEFT:
			pos.x=width;
			pos.y=height;
			m_pPic->SetSrcPos(pos);
			break;
		case eRIGHT:
			pos.x=width;
			pos.y=0;
			m_pPic->SetSrcPos(pos);
			break;
		}
	}
}

void CMask::SetDir(int i)
{
	m_dir = i;
}

void CMask::SetMapIndex(int i)
{
	m_mapIndex = i;
}

void CMask::SetVisible(bool b)
{
	m_visible = b;
}

void CMask::Move()
{
	int speed;
	if(m_visible)
	{
		if(!m_isPursue)
			speed=m_speedNormal;
		else
			speed=m_speedPursue;
		switch (m_dir)
		{
		case eUP:
			m_pos.y-=speed;
			if(m_pos.y-m_aimPos<=speed||m_pos.y<=110)
			{
				if(m_pos.y-m_aimPos<=speed)
					m_pos.y=m_aimPos;
				m_isUpdate=true;
			}
			break;
		case eDOWN:
			m_pos.y+=speed;
			if(m_aimPos-m_pos.y<=speed||m_pos.y>=450)
			{
				if(m_aimPos-m_pos.y<=speed)
					m_pos.y=m_aimPos;
				m_isUpdate=true;
			}
			break;
		case eLEFT:
			m_pos.x-=speed;
			if(m_pos.x-m_aimPos<=speed||m_pos.x<=96)
			{
				if(m_pos.x-m_aimPos<=speed)
					m_pos.x=m_aimPos;
				m_isUpdate=true;
			}
			break;
		case eRIGHT:
			m_pos.x+=speed;
			if(m_aimPos-m_pos.x<=speed||m_pos.x>=710)
			{
				if(m_aimPos-m_pos.x<=speed)
					m_pos.x=m_aimPos;
				m_isUpdate=true;
			}
			break;
		}
	}
}

void CMask::UpdateAim(POINT playerPos)
{
	if(m_isUpdate)
	{
		int x=playerPos.x+30;
		int y=playerPos.y+35;
		if(x>=m_rc.left&&x<=m_rc.right&&y>m_pos.y)
		{
			m_dir=eDOWN;
			m_aimPos=y;
			m_isPursue=true;
		}
		else if(x>=m_rc.left&&x<=m_rc.right&&y<m_pos.y)
		{
			m_dir=eUP;
			m_aimPos=y;
			m_isPursue=true;
		}
		else if(y>=m_rc.top&&y<=m_rc.bottom&&x<m_pos.x)
		{
			m_dir=eLEFT;
			m_aimPos=x;
			m_isPursue=true;
		}
		else if(y>=m_rc.top&&y<=m_rc.bottom&&x>m_pos.x)
		{
			m_dir=eRIGHT;
			m_aimPos=x;
			m_isPursue=true;
		}
		else
		{
			srand(GetTickCount());
			int length=rand()%200+200;
			bool b=true;
			int i;
			while(b)
			{
				srand(GetTickCount());
				i=rand()%4;
				if(i==0&&m_pos.y<=110)
					b=true;
				else if(i==1&&m_pos.y>=450)
					b=true;
				else if(i==2&&m_pos.x<=96)
					b=true;
				else if(i==3&&m_pos.x>=710)
					b=true;
				else 
					b=false;
			}
	
			switch(i)
			{
			case 0:
				m_dir=eUP;
				m_aimPos=m_pos.y-length;
				break;
			case 1:
				m_dir=eDOWN;
				m_aimPos=m_pos.y+length;
				break;
			case 2:
				m_dir=eLEFT;
				m_aimPos=m_pos.x-length;
				break;
			case 3:
				m_dir=eRIGHT;
				m_aimPos=m_pos.x+length;
				break;
			}
			m_isPursue=false;
		}
		m_isUpdate=false;
	}
}

void CMask::SetPos(POINT pos)
{
	m_pos=pos;
}

void CMask::UpdateRc()
{
	int x=m_pos.x-25;
	int y=m_pos.y-23;
	m_rc.left=x;
	m_rc.right=x+50;
	m_rc.top=y;
	m_rc.bottom=y+46;
}

void CMask::SetDamage(int i)
{
	m_damage=i;
}

void CMask::SetHp(int i)
{
	m_hp=i;
}

void CMask::SetNormalSpeed(int i)
{
	m_speedNormal=i;
}

void CMask::SetPursueSpeed(int i)
{
	m_speedPursue=i;
}

void CMask::SetIsRed(bool b)
{
	m_isRed=b;
}

POINT CMask::GetPos()
{
	return m_pos;
}

int CMask::GetDir()
{
	return m_dir;
}

int CMask::GetMapIndex()
{
	return m_mapIndex;
}

int CMask::GetDamage()
{
	return m_damage;
}

int CMask::GetHp()
{
	return m_hp;
}

bool CMask::GetVisible()
{
	return m_visible;
}

bool CMask::GetIsRed()
{
	return m_isRed;
}

RECT CMask::GetRc()
{
	return m_rc;
}