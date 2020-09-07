#include "stdafx.h"
#include "Feces.h"


CFeces::CFeces()
{
	m_count = 2;
}

CFeces::~CFeces()
{
}

void CFeces::IsShoot(vector<CBullet*>bulletPool,Map*pMap,int tileWidth,int num,int change)
{
	vector<CBullet*>::iterator iter = bulletPool.begin();
	for (; iter != bulletPool.end(); iter++)
	{
		if ((*iter)->GetVisible()&&(*iter)->GetCurRow()==0)
		{
			(*iter)->SetBottom(pMap, tileWidth, num);
			(*iter)->SetTop(pMap, tileWidth, num);
			(*iter)->SetLeft(pMap, tileWidth, num);
			(*iter)->SetRight(pMap, tileWidth, num);
			if ((*iter)->GetBottom() || (*iter)->GetTop() || (*iter)->GetRight() || (*iter)->GetLeft())
			{
				if ((*iter)->GetTop())
				{
					for (int i = (*iter)->GetBulletRect().left; i <= (*iter)->GetBulletRect().right; i++)
					{
						int x = ((*iter)->GetBulletRect().top + pMap->GetSrcPos().y) / tileWidth;
						int y = (i + pMap->GetSrcPos().x) / tileWidth;
						if (pMap->GetMap(x, y) == num)
						{
							pMap->SetMap(x, y, change);
							break;
						}
					}
				}
				else if ((*iter)->GetBottom())
				{
					for (int i = (*iter)->GetBulletRect().left; i <= (*iter)->GetBulletRect().right; i++)
					{
						int x = ((*iter)->GetBulletRect().bottom + pMap->GetSrcPos().y) / tileWidth;
						int y = (i + pMap->GetSrcPos().x) / tileWidth;
						if (pMap->GetMap(x, y) == num)
						{
							pMap->SetMap(x, y, change);
							break;
						}
					}
				}
				else if ((*iter)->GetLeft())
				{
					for (int i = (*iter)->GetBulletRect().top; i <= (*iter)->GetBulletRect().bottom; i++)
					{
						int y = ((*iter)->GetBulletRect().left + pMap->GetSrcPos().x) / tileWidth;
						int x = (i + pMap->GetSrcPos().y) / tileWidth;
						if (pMap->GetMap(x, y) == num)
						{
							pMap->SetMap(x, y, change);
							break;
						}
					}
				}
				else if ((*iter)->GetRight())
				{
					for (int i = (*iter)->GetBulletRect().top; i <= (*iter)->GetBulletRect().bottom; i++)
					{
						int y = ((*iter)->GetBulletRect().right + pMap->GetSrcPos().x) / tileWidth;
						int x = (i + pMap->GetSrcPos().y) / tileWidth;
						if (pMap->GetMap(x, y) == num)
						{
							pMap->SetMap(x, y, change);
							break;
						}
					}
				}
				break;
			}
		}
	}
}
