#include "stdafx.h"
#include "BulletPoolManager.h"


CPoolManager::CPoolManager()
{
	m_count = 0;
	m_rate = 500;
	m_dirOnMap = eNONE;
	m_dir=eNONE;
	IsFire=false;
	m_bulletFireCount = 0;
	m_bulletFireCount1 = 0;
	m_isBomb=false;
}

CPoolManager::~CPoolManager()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		delete (*iter);
	}
	m_bulletPool.clear();
}

void CPoolManager::Init(TSTRING name)
{
	m_pBullet = new CBullet;
	for (int i = 0; i < 160; i++)
	{
		m_pBullet = new CBullet;
		m_pBullet->Init(name);
		m_bulletPool.push_back(m_pBullet);
	}
}

void CPoolManager::InitBulletPath1()
{
	D3DXVECTOR2 vec;
	vec.x = 1;
	vec.y = 0;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = 1;
	vec.y = -1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = 0;
	vec.y = -1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = -1;
	vec.y = -1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = -1;
	vec.y = 0;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = -1;
	vec.y = 1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = 0;
	vec.y = 1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);

	vec.x = 1;
	vec.y = 1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath1.push_back(vec);
}

void CPoolManager::InitBulletPath()
{
	D3DXVECTOR2 vec;

	vec.x = 1;
	vec.y = 0;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 1;
	(float)vec.y = (float)tan((float)(D3DX_PI / 180) * 30);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 1;
	(float)vec.y = (float)tan((float)(D3DX_PI / 180) * 60);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 0;
	vec.y = 1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = -1;
	(float)vec.y = (float)tan((float)(D3DX_PI / 180) * 60);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = -1;
	(float)vec.y = (float)tan((float)(D3DX_PI / 180) * 30);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = -1;
	vec.y = 0;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = -1;
	(float)vec.y = -(float)tan((float)(D3DX_PI / 180) * 30);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = -1;
	(float)vec.y = -(float)tan((float)(D3DX_PI / 180) * 60);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 0;
	vec.y = -1;
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 1;
	(float)vec.y = -(float)tan((float)(D3DX_PI / 180) * 60);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

	vec.x = 1;
	(float)vec.y = -(float)tan((float)(D3DX_PI / 180) * 30);
	D3DXVec2Normalize(&vec, &vec);
	m_bulletPath.push_back(vec);

}

void CPoolManager::Render()
{
	vector<CBullet*>::iterator iter=m_bulletPool.begin();
	for(;iter!=m_bulletPool.end();iter++)
	{
		if((*iter)->GetVisible())
			(*iter)->Draw();
	}
}

void CPoolManager::Update()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetIsExplode())
		{
			(*iter)->Update();
		}
	}
}

void CPoolManager::Move(Map*pMap,int tileWidth,int num)
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible())
			(*iter)->Move(pMap,tileWidth,num);
	}
	Refresh();
	if(IsFire)
	{
		if(m_count==0)
		{
			Fire(m_dir);
			m_count++;
		}
		static DWORD preTime = GetTickCount();
		DWORD curTime = GetTickCount();
		if (curTime - preTime > m_rate)
		{
			preTime = curTime;
			Fire(m_dir);
		}
	}
}

void CPoolManager::PathMove()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible())
		{
			(*iter)->PathMove();
		}
	}
	UpdateBullet();
}

void CPoolManager::SetPath()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if (!(*iter)->GetVisible())
		{
			(*iter)->SetVisible(true);
			(*iter)->SetPath(m_bulletPath[m_bulletFireCount]);
			m_bulletFireCount++;
			if (m_bulletFireCount == 12)
			{
				m_bulletFireCount = 0;
			}
			break;
		}
	}
}

void CPoolManager::SetPath1()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if (!(*iter)->GetVisible())
		{
			(*iter)->SetVisible(true);
			(*iter)->SetPath(m_bulletPath1[m_bulletFireCount1]);
			m_bulletFireCount1++;
			if (m_bulletFireCount1 == 8)
			{
				m_bulletFireCount1 = 0;
				break;
			}
		}
	}
}

void CPoolManager::SetSpeed(int i)
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if (!(*iter)->GetVisible())
		{
			(*iter)->SetSpeed(i);
		}
	}
}

void CPoolManager::UpdateBullet()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible())
		{
			if ((*iter)->GetPos().x<0 || (*iter)->GetPos().x>832 || (*iter)->GetPos().y<0 || (*iter)->GetPos().y>576)
			{
				POINT pos = { 370, 140 };
				(*iter)->SetPos(pos);
				(*iter)->SetVisible(false);
			}
		}
	}
}

void CPoolManager::OnKeyDown(SEvent event)
{
	if (event.keyInput.pressedDown)
		switch (event.keyInput.key)
	{
		case VK_UP:
			m_dir|=eUP;
			IsFire=true;
			break;
		case  VK_DOWN:
			m_dir|=eDOWN;
			IsFire=true;
			break;
		case VK_LEFT:
			m_dir|=eLEFT;
			IsFire=true;
			break;
		case VK_RIGHT:
			m_dir|=eRIGHT;
			IsFire=true;
			break;
	}
}

void CPoolManager::OnKeyUp(SEvent event)
{
	if (!event.keyInput.pressedDown)
	{
		switch (event.keyInput.key)
		{
		case VK_UP:
			m_dir-=eUP;
			if(m_dir==eNONE)
				IsFire=false;
			break;
		case VK_DOWN:
			m_dir-=eDOWN;
			if(m_dir==eNONE)
				IsFire=false;
			break;
		case VK_LEFT:
			m_dir-=eLEFT;
			if(m_dir==eNONE)
				IsFire=false;
			break;
		case VK_RIGHT:
			m_dir-=eRIGHT;
			if(m_dir==eNONE)
				IsFire=false;
			break;
		}
	}
}

void CPoolManager::Fire(int dir)
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if (!(*iter)->GetVisible())
		{
			CAudio4Bass::GetInstance()->ChannelPlay(8, false);
			(*iter)->SetVisible(true);
			(*iter)->SetBulletDir(dir);
			(*iter)->SetPos(CGameManager::GetInstance()->GetFirstStage()->GetPlayerHead()->GetPlayerPos());
			break;
		}
	}
}

void CPoolManager::SetFalse()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible())
		{
			(*iter)->SetVisible(false);
		}
	}
}

void CPoolManager::Refresh()
{
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible() && (!(*iter)->GetBottom() || !(*iter)->GetTop() || !(*iter)->GetRight() || !(*iter)->GetLeft()))
		{
			if(!m_isBomb)
			{
				(*iter)->SetIsExplode(true);
				CAudio4Bass::GetInstance()->ChannelPlay(10, false);
			}
			else if(m_isBomb)
			{
				(*iter)->SetVisible(false);
				CGameManager::GetInstance()->GetFirstStage()->BombExplode((*iter)->GetPos(),60,130);
			}
		}
	}
}

void CPoolManager::SetRate(int rate)
{
	m_rate = rate;
}

void CPoolManager::MoveOnMap()
{
	POINT pos = { 0, 0 };
	WORD speed = CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody()->GetPlayerSpeed();
	vector<CBullet*>::iterator iter = m_bulletPool.begin();
	for (; iter != m_bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible())
		{
			switch (m_dirOnMap)
			{
			case eNONE:
				pos.x = (*iter)->GetPos().x;
				pos.y = (*iter)->GetPos().y;
				break;
			case eUP:
				pos.y = (*iter)->GetPos().y - speed;
				pos.x = (*iter)->GetPos().x;
				break;
			case eDOWN:
				pos.y = (*iter)->GetPos().y + speed;
				pos.x = (*iter)->GetPos().x;
				break;
			case eLEFT:
				pos.x = (*iter)->GetPos().x - speed;
				pos.y = (*iter)->GetPos().y;
				break;
			case eRIGHT:
				pos.x = (*iter)->GetPos().x + speed;
				pos.y = (*iter)->GetPos().y;
				break;
			case eUP | eLEFT:
				pos.y = (*iter)->GetPos().y - speed;
				pos.x = (*iter)->GetPos().x - speed;
				break;
			case eDOWN | eLEFT:
				pos.y = (*iter)->GetPos().y + speed;
				pos.x = (*iter)->GetPos().x - speed;
				break;
			case eUP | eRIGHT:
				pos.y = (*iter)->GetPos().y - speed;
				pos.x = (*iter)->GetPos().x + speed;
				break;
			case eDOWN | eRIGHT:
				pos.y = (*iter)->GetPos().y + speed;
				pos.x = (*iter)->GetPos().x + speed;
				break;
			}
			(*iter)->SetPos(pos);
		}
	}
}

void CPoolManager::SetDirOnMap(int dir)
{
	m_dirOnMap = dir;
}

void CPoolManager::SetDamage(int m)
{
	m_damage=m;
}

void CPoolManager::SetIsBomb(bool b)
{
	m_isBomb=b;
}

bool CPoolManager::GetIsBomb()
{
	return m_isBomb;
}

int CPoolManager::GetDamage()
{
	return m_damage;
}

DWORD CPoolManager::GetColorValue(POINT pos)
{
	return m_bulletPool[1]->GetColorValue(pos);
}

vector<CBullet*>::iterator CPoolManager::GetBulletPoolBegin()
{
	vector<CBullet*>::iterator it= m_bulletPool.begin();
	return it;
}

vector<CBullet*>::iterator CPoolManager::GetBulletPoolEnd()
{
	vector<CBullet*>::iterator it = m_bulletPool.end();
	return it;
}

vector<CBullet*>CPoolManager::GetBulletPool()
{
	return m_bulletPool;
}