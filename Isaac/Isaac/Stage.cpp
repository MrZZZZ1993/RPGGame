#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
	m_pMap=nullptr;
	m_pFire=nullptr;
	m_pFly=nullptr;
	m_pFlyMonster=nullptr;
	m_pDoor=nullptr;
	m_curMapIndex=0;
	m_doorIndex = 0;
	m_left = false;
	m_right = false;
	m_up = false;
	m_down = false;
	m_mapSpeed = 0;
	m_doorUpdateCount = 0;
	m_pFlyDuke = nullptr;
	m_isFireFly = true;
	m_bossRoomNum=0;
	m_isStart = false;
	m_VSScale = 3.0f;
	m_angle = 0.0f;
	m_VSVisible = true;
	m_angle1 = 0.1f;
	m_startReturnCount = 0;
	m_addRedCount = 0;
	m_pBlood=nullptr;
	m_bossHP=0;
	m_bossHPSum=0;
	m_bloodVisible=true;
	m_pExplodeBlood = nullptr;
	m_explodeBloodCount = 0;
	m_ExplodeVisible = false;
	m_pGuide=nullptr;
	m_guideCount=0;
	m_pHeart=nullptr;
	m_invincibleCount=0;
	m_isInvincible=false;
	m_pBombExplode=nullptr;
	m_pMonsterDead=nullptr;
	m_pMask=nullptr;
	m_pPathBullet = nullptr;
	m_pMatherHeart=nullptr;
	m_pLost = nullptr;
	m_isStartMusic = 0;
	m_bobMusicCount = 0;
	m_pMushroom = nullptr;
	m_pShoe=nullptr;
	m_scissor=nullptr;
	m_pBomb=nullptr;
	m_pLeg=nullptr;
	m_goodsCount = 2;
	m_pAngel = nullptr;
	m_pPlayerHP=nullptr;
	m_pMoney=nullptr;
	m_pNumber = nullptr;
	m_moneyCount = 0;
	m_pNumber1 = nullptr;
}

CStage::~CStage()
{
	map<int,Map*>::iterator it=m_map.begin();
	for(;it!=m_map.end();it++)
	{
		delete it->second;
	}
	m_map.clear();
	delete m_pMap;

	vector<CFire*>::iterator iter= m_fire.begin();
	for (; iter != m_fire.end(); iter++)
	{
		delete *iter;
	}
	m_fire.clear();
	delete m_pFire;

	vector<CFly*>::iterator iter1= m_fly.begin();
	for (; iter1 != m_fly.end(); iter1++)
	{
		delete *iter1;
	}
	m_fly.clear();
	delete m_pFly;

	vector<CFlyMonster*>::iterator iter2= m_flyMonster.begin();
	for (; iter2 != m_flyMonster.end(); iter2++)
	{
		delete *iter2;
	}
	m_fly.clear();
	delete m_pFlyMonster;

	map<int,CDoor*>::iterator iter3=m_door.begin();
	for(;iter3!=m_door.end();iter3++)
	{
		delete iter3->second;
	}
	m_door.clear();
	delete m_pDoor;

	delete m_pFlyDuke;

	vector<Map*>::iterator iter4 = m_startSurface.begin();
	for (; iter4 != m_startSurface.end(); iter4++)
	{
		delete *iter4;
	}
	m_startSurface.clear();

	delete m_pBlood;
	delete m_pExplodeBlood;

	delete[] m_pPPixelBullet;
	delete[] m_pPPixelBoss;
	delete[] m_pPPixelBody;
	delete[] m_pPPixelHead;

	map<int,CGuide*>::iterator iter5 = m_guide.begin();
	for (; iter5 != m_guide.end(); iter5++)
	{
		delete iter5->second;
	}
	m_guide.clear();


	delete m_pGuide;
	delete m_pHeart;

	vector<CHeart*>::iterator iter6 = m_heart.begin();
	for (; iter6 != m_heart.end(); iter6++)
	{
		delete *iter6;
	}
	m_heart.clear();

	delete m_pPlayerHeart;


	vector<CBombExplode*>::iterator iter7 = m_bombExplode.begin();
	for (; iter7 != m_bombExplode.end(); iter7++)
	{
		delete *iter7;
	}
	m_bombExplode.clear();

	delete m_pBombExplode;

	vector<CTile*>::iterator iter8 = m_tile.begin();
	for (; iter8 != m_tile.end(); iter8++)
	{
		delete *iter8;
	}
	m_tile.clear();

	delete m_pTile;

	vector<CBob*>::iterator iter9=m_bob.begin();
	for(;iter9!=m_bob.end();iter9++)
	{
		delete *iter9;
	}
	m_bob.clear();

	delete m_pBob;

	vector<CMonsterDead*>::iterator iter10=m_monsterDead.begin();
	for(;iter10!=m_monsterDead.end();iter10++)
	{
		delete *iter10;
	}
	m_monsterDead.clear();

	delete m_pMonsterDead;

	vector<CMask*>::iterator iter11=m_mask.begin();
	for(;iter11!=m_mask.end();iter11++)
	{
		delete *iter11;
	}
	m_mask.clear();

	map<int,CMaskHeart*>::iterator iter12 = m_maskHeart.begin();
	for (; iter12 != m_maskHeart.end(); iter12++)
	{
		delete iter12->second;
	}
	m_maskHeart.clear();

	map<int, CMaskHeart*>::iterator iter13 = m_HEART.begin();
	for (; iter13 != m_HEART.end(); iter13++)
	{
		delete iter13->second;
	}
	m_HEART.clear();

	delete m_pMaskHeart;

	vector<CFeceMonster*>::iterator iter14 = m_feceMonster.begin();
	for (; iter14 != m_feceMonster.end(); iter14++)
	{
		delete *iter14;
	}
	m_feceMonster.clear();

	delete m_pFeceMonster;

	delete m_pPathBullet;

	delete m_pMatherHeart;

	delete m_pEnd;

	delete m_pLost;

	vector<CGoods*>::iterator iter15 = m_goods.begin();
	for (; iter15 != m_goods.end(); iter15++)
	{
		delete *iter15;
	}

	vector<CMoney*>::iterator iter16 = m_money.begin();
	for (; iter16 != m_money.end(); iter16++)
	{
		delete *iter16;
	}

	delete m_pNumber;

	delete m_pNumber1;
}

void CStage::readFromFile(TSTRING fileName)
{
#ifdef UNICODE
	char*file = CTool::CU_U2A(fileName.c_str());
#else
	const char*file = fileName.c_str();
#endif
	TiXmlDocument *doc = new TiXmlDocument(file);
	doc->LoadFile();
	TiXmlElement*element = doc->FirstChildElement();
	while (element)
	{
#ifdef UNICODE
		wchar_t*name;
		name = CTool::CU_A2U(element->Attribute("name"));
#else
		const char*name = element->Attribute("name");
#endif
		int type;
		element->Attribute("type",&type);
		switch (type)
		{
		case 0:
			{
				m_pMap = new Map;
				m_pMap->Init(name);
				int mapType; 
				element->Attribute("MapType",&mapType);
				if(mapType==1)
				{
					const char*fileName1 = element->Attribute("fileName");
					m_pMap->InitTileMap(fileName1);
				}
				int mapNumber, desX, desY,showWidth,showHeight,stone;
				element->Attribute("mapNumber", &mapNumber);
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("showWidth", &showWidth);
				element->Attribute("showHeight", &showHeight);
				element->Attribute("stone", &stone);
				POINT pos = { desX, desY };
				m_pMap->SetDesPos(pos);
				m_pMap->SetShowWidth(showWidth);
				m_pMap->SetShowHeight(showHeight);
				m_pMap->SetMapIndex(mapNumber);
				m_pMap->SetMapType(mapType);
				if(stone==0)
					m_map[mapNumber] = m_pMap;
				else if(stone==1)
					m_stone[mapNumber]=m_pMap;
			}
			break;
		case 1:
			{
				int desX,desY,mapIndex,damage;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("mapIndex", &mapIndex);
				element->Attribute("damage", &damage);
				POINT pos = { desX, desY };
				m_pFire = new CFire;
				m_pFire->Init();
				m_pFire->SetPos(pos);
				m_pFire->SetMapIndex(mapIndex);
				m_pFire->SetDamage(damage);
				m_fire.push_back(m_pFire);
			}
			break;
		case 2:
			{
				int desX,desY,speed,mapIndex,curFrame,visible,hp,damage;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("speed", &speed);
				element->Attribute("mapIndex", &mapIndex);
				element->Attribute("curFrame", &curFrame);
				element->Attribute("visible", &visible);
				element->Attribute("HP",&hp);
				element->Attribute("damage", &damage);
				POINT pos = { desX, desY };
				m_pFly = new CFly;
				m_pFly->Init(name);
				m_pFly->ReSet(curFrame, 0, 0, 3, 0, 1);
				m_pFly->SetPos(pos);
				m_pFly->SetDesPos(pos);
				m_pFly->SetSpeed(speed);
				m_pFly->SetMapIndex(mapIndex);
				m_pFly->SetVisible(visible);
				m_pFly->SetHP(hp);
				m_pFly->SetDamage(damage);
				m_fly.push_back(m_pFly);
			}
			break;
		case 3:
			{
				int desX,desY,speed,angleX,angleY,fHalfWidth,mapIndex,hp,damage;
				int visible;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("speed", &speed);
				element->Attribute("dirX", &angleX);
				element->Attribute("dirY", &angleY);
				element->Attribute("fHalfWidth", &fHalfWidth);
				element->Attribute("mapIndex", &mapIndex);
				element->Attribute("HP", &hp);
				element->Attribute("damage", &damage);
				element->Attribute("visible",&visible);
				POINT pos = { desX, desY };
				D3DXVECTOR2 angle;
				angle.x=(float)angleX/10;
				angle.y=(float)angleY/10;
				m_pFlyMonster = new CFlyMonster;
				m_pFlyMonster->Init(name);
				m_pFlyMonster->SetPos(pos);
				m_pFlyMonster->SetDesPos(pos);
				m_pFlyMonster->SetSpeed(speed);
				m_pFlyMonster->SetAngleDir(angle);
				m_pFlyMonster->SetHalfWidth(fHalfWidth);
				m_pFlyMonster->SetMapIndex(mapIndex);
				m_pFlyMonster->SetHP(hp);
				m_pFlyMonster->SetDamage(damage);
				m_pFlyMonster->SetVisible(visible);
				m_flyMonster.push_back(m_pFlyMonster);
			}
			break;
		case 4:
			{
				int desX,desY,curRow,startRow,endRow,doorIndex,curFrame,startFrame,endFrame,doorType;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("endRow", &endRow);
				element->Attribute("doorIndex",&doorIndex);
				element->Attribute("curRow", &curRow);
				element->Attribute("startRow",&startRow);
				element->Attribute("curFrame", &curFrame);
				element->Attribute("startFrame",&startFrame);
				element->Attribute("endFrame", &endFrame);
				element->Attribute("doorType", &doorType);
				POINT pos = { desX, desY };
				m_pDoor=new CDoor;
				m_pDoor->Init(name);
				m_pDoor->SetDesPos(pos);
				m_pDoor->SetPos(pos);
				m_pDoor->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
				m_pDoor->SetDoorIndex(doorIndex);
				m_pDoor->SetDoorType(doorType);
				pos.x=curFrame*m_pDoor->GetFrameWidth();
				pos.y=curRow*m_pDoor->GetFrameHeight();
				m_pDoor->SetSrcPos(pos);
				m_door[doorIndex]=m_pDoor;
			}
			break;
		case 5:
			{
				int desX,desY,speed,shadow,hp;
				element->Attribute("shadow", &shadow);
				if(shadow!=1)
				{
					element->Attribute("desX", &desX);
					element->Attribute("desY", &desY);
					element->Attribute("speed", &speed);
				}
				if(shadow==2)
				{
					POINT pos = { desX, desY };
					m_pPlayerBody=new CPlayerBody;
					m_pPlayerBody->Init(name);
					m_pPlayerBody->SetPos(pos);
					m_pPlayerBody->SetDesPos(pos);
					m_pPlayerBody->SetPlayerSpeed(speed);
				}
				else if(shadow==3)
				{
					POINT pos = { desX, desY };
					element->Attribute("hp", &hp);
					m_pPlayerHead=new CPlayerHead;
					m_pPlayerHead->Init(name);
					m_pPlayerHead->SetPos(pos);
					m_pPlayerHead->SetDesPos(pos);
					m_pPlayerHead->SetPlayerSpeed(speed);
					m_pPlayerHead->SetCountHp(hp);
					m_pPlayerHead->SetHp(hp);
				}
				else if(shadow==1)
				{
					m_pPlayerBody->InitShadow(name);
				}
			}
			break;
		case 6:
			{
				int damage,speed;
				m_pBulletPool=new CPoolManager;
				m_pBulletPool->Init(name);
				element->Attribute("damage",&damage);
				element->Attribute("speed", &speed);
				m_pBulletPool->SetSpeed(speed);
				m_pBulletPool->SetDamage(damage);
			}
			break;
		case 7:
		{
				  int desX, desY, speed, angleX, angleY, fHalfWidth, mapIndex, fireTime, hp, damage,visible;
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  element->Attribute("speed", &speed);
				  element->Attribute("dirX", &angleX);
				  element->Attribute("dirY", &angleY);
				  element->Attribute("fHalfWidth", &fHalfWidth);
				  element->Attribute("mapIndex", &mapIndex);
				  element->Attribute("fireTime", &fireTime);
				  element->Attribute("HP", &hp); 
				  element->Attribute("damage", &damage);
				  element->Attribute("visible",&visible);
				  POINT pos = { desX, desY };
				  D3DXVECTOR2 angle;
				  angle.x = (float)angleX / 10;
				  angle.y = (float)angleY / 10;
				  m_pFlyDuke = new CFlyDuke;
				  m_pFlyDuke->Init(name);
				  m_pFlyDuke->InitFlyDuke();
				  m_pFlyDuke->SetPos(pos);
				  m_pFlyDuke->SetDesPos(pos);
				  m_pFlyDuke->SetSpeed(speed);
				  m_pFlyDuke->SetAngleDir(angle);
				  m_pFlyDuke->SetHalfWidth(fHalfWidth);
				  m_pFlyDuke->SetMapIndex(mapIndex);
				  m_pFlyDuke->SetFireTime(fireTime);
				  m_pFlyDuke->SetHP(hp);
				  m_pFlyDuke->SetDamage(damage);
				  m_pFlyDuke->SetVisible(visible);
		}
			break;
		case 8:
		{
				  int desX, desY, speed, mapNumber;
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  element->Attribute("mapIndex", &mapNumber);
				  POINT pos = { desX, desY };
				  m_pMap = new Map;
				  m_pMap->Init(name);
				  m_pMap->SetDesPos(pos);
				  m_pMap->SetMapIndex(mapNumber);
				  m_pMap->SetShowWidth(m_pMap->GetWidth());
				  m_pMap->SetShowHeight(m_pMap->GetHeight());
				  m_startSurface.push_back(m_pMap);
		}
			break;
		case 9:
		{
				  element->Attribute("mapIndex", &m_curMapIndex);
				  element->Attribute("doorIndex", &m_doorIndex);
				  element->Attribute("mapSpeed", &m_mapSpeed);
				  element->Attribute("bossRoom", &m_bossRoomNum);
				  element->Attribute("bossHP",&m_bossHP);
				  m_bossHPSum=m_bossHP;
		}
			break;
		case 10:
			{
				int desX, desY;
				m_pBlood=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
				m_pBlood->Init();
				m_pBlood->SetShowWidth(m_pBlood->GetFrameWidth());
				m_pBlood->SetShowHeight(m_pBlood->GetFrameHeight());
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				POINT pos={desX,desY};
				m_pBlood->SetDesPos(pos);
				m_pBlood->UpdateMAatrix();
			}
			break;
		case 11:
			{
				int desX, desY,endFrame,endRow,startFrame,startRow;
				m_pExplodeBlood = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				m_pExplodeBlood->Init();
				m_pExplodeBlood->SetShowWidth(m_pExplodeBlood->GetFrameWidth());
				m_pExplodeBlood->SetShowHeight(m_pExplodeBlood->GetFrameHeight());
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("endFrame", &endFrame);
				element->Attribute("endRow", &endRow);
				element->Attribute("startFrame", &startFrame);
				element->Attribute("startRow", &startRow);
				POINT pos = { desX, desY };
				m_pExplodeBlood->SetDesPos(pos);
				m_pExplodeBlood->UpdateMAatrix();
				m_pExplodeBlood->ReSet(0, 0, startFrame, endFrame, startRow, endRow);
			}
			break;
		case 12:
			{
				int desX, desY,srcX,srcY,showWidth,showHeight,mapIndex,state;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("srcX", &srcX);
				element->Attribute("srcY", &srcY);
				element->Attribute("showWidth", &showWidth);
				element->Attribute("showHeight", &showHeight);
				element->Attribute("mapIndex",&mapIndex);
				element->Attribute("state",&state);
				POINT pos = { desX, desY };
				POINT pos1 = { srcX, srcY };
				m_pGuide=new CGuide;
				m_pGuide->Init(name);
				m_pGuide->SetDesPos(pos);
				m_pGuide->SetSrcPos(pos1);
				m_pGuide->SetShowWidth(showWidth);
				m_pGuide->SetShowHeight(showHeight);
				m_pGuide->SetMapIndex(mapIndex);
				m_pGuide->SetState(state);
				m_guide[mapIndex]=m_pGuide;
			}
			break;
		case 13:
			{
				int desX, desY,srcX,srcY;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("srcX", &srcX);
				element->Attribute("srcY", &srcY);
				POINT pos = { desX, desY };
				POINT pos1 = { srcX, srcY };
				m_pPlayerHeart=new CHeart;
				m_pPlayerHeart->Init(name);
				m_pPlayerHeart->SetDesPos(pos);
				m_pPlayerHeart->SetSrcPos(pos1);
				m_heart.push_back(m_pPlayerHeart);
			}
			break;
		case 14:
			{
				int startFrame,endFrame, startRow, endRow, curFrame, curRow,damage;
				m_pBombExplode=new CBombExplode;
				m_pBombExplode->Init(name);
				element->Attribute("startFrame",&startFrame);
				element->Attribute("endFrame",&endFrame);
				element->Attribute("startRow",&startRow);
				element->Attribute("endRow",&endRow);
				element->Attribute("curFrame",&curFrame);
				element->Attribute("curRow",&curRow);
				element->Attribute("damage",&damage);
				m_pBombExplode->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
				m_pBombExplode->SetDamage(damage);
				m_bombExplode.push_back(m_pBombExplode);
			}
			break;
		case 15:
			{
				int startFrame,endFrame, startRow, endRow, curFrame, curRow,damage;
				int desX,desY,pos1X,pos1Y,pos2X,pos2Y,pos3X,pos3Y,pos4X,pos4Y,endCount,mapIndex;
				int speed;
				m_pTile=new CTile;
				m_pTile->Init(name);
				element->Attribute("startFrame",&startFrame);
				element->Attribute("endFrame",&endFrame);
				element->Attribute("startRow",&startRow);
				element->Attribute("endRow",&endRow);
				element->Attribute("curFrame",&curFrame);
				element->Attribute("curRow",&curRow);
				element->Attribute("damage",&damage);
				element->Attribute("point1X",&pos1X);
				element->Attribute("point1Y",&pos1Y);
				element->Attribute("point2X",&pos2X);
				element->Attribute("point2Y",&pos2Y);
				element->Attribute("point3X",&pos3X);
				element->Attribute("point3Y",&pos3Y);
				element->Attribute("point4X",&pos4X);
				element->Attribute("point4Y",&pos4Y);
				element->Attribute("desX",&desX);
				element->Attribute("desY",&desY);
				element->Attribute("endCount",&endCount);
				element->Attribute("mapIndex",&mapIndex);
				element->Attribute("speed",&speed);
				POINT desPos={desX,desY};
				POINT Pos1={pos1X,pos1Y};
				POINT Pos2={pos2X,pos2Y};
				POINT Pos3={pos3X,pos3Y};
				POINT Pos4={pos4X,pos4Y};
				m_pTile->SetPos(desPos);
				m_pTile->SetPoint(Pos1,Pos2,Pos3,Pos4);
				m_pTile->ReSet(curFrame,curRow,startFrame,endFrame,startRow,endRow);
				m_pTile->SetDamage(damage);
				m_pTile->SetEndPoint(endCount);
				m_pTile->SetMapIndex(mapIndex);
				m_pTile->SetSpeed(speed);
				m_tile.push_back(m_pTile);
			}
			break;
		case 16:
			{
				int desX,desY,damage,speed,mapIndex,visible,hp;
				m_pBob=new CBob;
				m_pBob->Init(name);
				element->Attribute("desX",&desX);
				element->Attribute("desY",&desY);
				element->Attribute("damage",&damage);
				element->Attribute("speed",&speed);
				element->Attribute("mapIndex",&mapIndex);
				element->Attribute("visible",&visible);
				element->Attribute("hp",&hp);
				POINT pos={desX,desY};
				m_pBob->SetPos(pos);
				m_pBob->SetDamage(damage);
				m_pBob->SetMapIndex(mapIndex);
				m_pBob->SetSpeed(speed);
				m_pBob->SetVisible(visible);
				m_pBob->SetHP(hp);
				const char*walkMap = element->Attribute("walkMap");
				m_pBob->InitAStar(walkMap);
				m_bob.push_back(m_pBob);
			}
			break;
		case 17:
			{
				m_pMonsterDead=new CMonsterDead;
				m_pMonsterDead->Init(name);
				m_monsterDead.push_back(m_pMonsterDead);
			}
			break;
		case 18:
			{
				int desX,desY,damage,hp,mapIndex,speedNormal,speedPursue,visible;
				m_pMask=new CMask;
				m_pMask->Init(name);
				element->Attribute("desX",&desX);
				element->Attribute("desY",&desY);
				element->Attribute("speedNormal",&speedNormal);
				element->Attribute("speedPursue",&speedPursue);
				element->Attribute("HP",&hp);
				element->Attribute("damage",&damage);
				element->Attribute("mapIndex",&mapIndex);
				element->Attribute("visible", &visible);
				POINT pos={desX,desY};
				m_pMask->SetPos(pos);
				m_pMask->SetDamage(damage);
				m_pMask->SetHp(hp);
				m_pMask->SetMapIndex(mapIndex);
				m_pMask->SetNormalSpeed(speedNormal);
				m_pMask->SetPursueSpeed(speedPursue);
				m_pMask->SetVisible(visible);
				m_mask.push_back(m_pMask);
			}
			break;
		case 19:
		{
				   int desX, desY, damage, hp, mapIndex, speedNormal, speedPursue, visible,isMask,num;
				   m_pMaskHeart = new CMaskHeart;
				   m_pMaskHeart->Init(name);
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("speedNormal", &speedNormal);
				   element->Attribute("speedPursue", &speedPursue);
				   element->Attribute("HP", &hp);
				   element->Attribute("damage", &damage);
				   element->Attribute("mapIndex", &mapIndex);
				   element->Attribute("visible", &visible);
				   element->Attribute("num", &num);
				   element->Attribute("isMask", &isMask);
				   POINT pos = { desX, desY };
				   m_pMaskHeart->SetPos(pos);
				   m_pMaskHeart->SetDamage(damage);
				   m_pMaskHeart->SetHp(hp);
				   m_pMaskHeart->SetMapIndex(mapIndex);
				   m_pMaskHeart->SetNormalSpeed(speedNormal);
				   m_pMaskHeart->SetPursueSpeed(speedPursue);
				   m_pMaskHeart->SetVisible(visible);
				   m_pMaskHeart->SetIsMask(isMask);
				   m_pMaskHeart->SetNum(num);
				   if (isMask == 1)
					   m_maskHeart[num] = m_pMaskHeart;
				   else
					   m_HEART[num] = m_pMaskHeart;
		}
			break;
		case 20:
		{
				   int desX, desY, damage, hp, mapIndex, visible,speed;
				   m_pFeceMonster = new CFeceMonster;
				   m_pFeceMonster->Init(name);
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("HP", &hp);
				   element->Attribute("damage", &damage);
				   element->Attribute("mapIndex", &mapIndex);
				   element->Attribute("visible", &visible);
				   element->Attribute("speed", &speed);
				   POINT pos = { desX, desY };
				   m_pFeceMonster->SetPos(pos);
				   m_pFeceMonster->SetDamage(damage);
				   m_pFeceMonster->SetHp(hp);
				   m_pFeceMonster->SetMapIndex(mapIndex);
				   m_pFeceMonster->SetVisible(visible);
				   m_pFeceMonster->SetSpeed(speed);
				   m_feceMonster.push_back(m_pFeceMonster);
		}
			break;
		case 21:
			{
				int damage,speed;
				m_pPathBullet = new CPoolManager;
				m_pPathBullet->Init(name);
				element->Attribute("damage", &damage);
				element->Attribute("speed", &speed);
				m_pPathBullet->SetDamage(damage);
				m_pPathBullet->InitBulletPath();
				m_pPathBullet->InitBulletPath1();
				m_pPathBullet->SetSpeed(speed);
			}
			break;
		case 22:
			{
				  int desX, desY, damage, hp, mapIndex, visible;
				  m_pMatherHeart=new CMatherHeart;
				  m_pMatherHeart->Init(name);
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  element->Attribute("hp", &hp);
				  element->Attribute("damage", &damage);
				  element->Attribute("mapIndex", &mapIndex);
				  element->Attribute("visible", &visible);
				  POINT pos = { desX, desY };
				  m_pMatherHeart->SetPos(pos);
				  m_pMatherHeart->SetDamage(damage);
				  m_pMatherHeart->SetHp(hp);
				  m_pMatherHeart->SetMapIndex(mapIndex);
				  m_pMatherHeart->SetVisible(visible);
			}
			break;
		case 23:
			{
				int mapIndex;
				m_pEnd=new CEnd;
				m_pEnd->Init();
				element->Attribute("mapIndex",&mapIndex);
				m_pEnd->SetMapIndex(mapIndex);
			}
			break;
		case 24:
		{
				   int desX, desY,showWidth,showHeight, goodsType, mapIndex, visible;
				   element->Attribute("goodsType", &goodsType);
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &showWidth);
				   element->Attribute("showHeight", &showHeight);
				   element->Attribute("mapIndex", &mapIndex);
				   element->Attribute("visible", &visible);
				   POINT pos = { desX, desY };
				   switch (goodsType)
				   {
				   case 0:
					   m_pPlat = new CPlat;
					   m_pPlat->Init(name);
					   m_pPlat->SetPos(pos);
					   m_pPlat->SetVisible(visible);
					   m_pPlat->SetShowWidth(showWidth);
					   m_pPlat->SetShowHeight(showHeight);
					   m_pPlat->SetMapIndex(mapIndex);
					   m_goods.push_back(m_pPlat);
					   break;
				   case 1:
					   m_pMushroom = new CMushroom;
					   m_pMushroom->Init(name);
					   m_pMushroom->SetPos(pos);
					   m_pMushroom->SetVisible(visible);
					   m_pMushroom->SetShowWidth(showWidth);
					   m_pMushroom->SetShowHeight(showHeight);
					   m_pMushroom->SetMapIndex(mapIndex);
					   m_goods.push_back(m_pMushroom);
					   break;
				   case 2:
					   m_pShoe = new CShoe;
					   m_pShoe->Init(name);
					   m_pShoe->SetPos(pos);
					   m_pShoe->SetVisible(visible);
					   m_pShoe->SetShowWidth(showWidth);
					   m_pShoe->SetShowHeight(showHeight);
					   m_pShoe->SetMapIndex(mapIndex);
					   m_goods.push_back(m_pShoe);
					   break;
				   case 3:
					   m_scissor = new CEye;
					   m_scissor->Init(name);
					   m_scissor->SetPos(pos);
					   m_scissor->SetVisible(visible);
					   m_scissor->SetShowWidth(showWidth);
					   m_scissor->SetShowHeight(showHeight);
					   m_scissor->SetMapIndex(mapIndex);
					   m_goods.push_back(m_scissor);
					   break;
				   case 4:
					   m_pBomb = new CBomb;
					   m_pBomb->Init(name);
					   m_pBomb->SetPos(pos);
					   m_pBomb->SetVisible(visible);
					   m_pBomb->SetShowWidth(showWidth);
					   m_pBomb->SetShowHeight(showHeight);
					   m_pBomb->SetMapIndex(mapIndex);
					   m_goods.push_back(m_pBomb);
					   break;
				   case 5:
					   int speed,damage;
					   element->Attribute("speed",&speed);
					   element->Attribute("damage",&damage);
					   m_pLeg = new CLeg;
					   m_pLeg->InitLeg();
					   m_pLeg->Init(name);
					   m_pLeg->SetPos(pos);
					   m_pLeg->SetVisible(visible);
					   m_pLeg->SetShowWidth(showWidth);
					   m_pLeg->SetShowHeight(showHeight);
					   m_pLeg->SetMapIndex(mapIndex);
					   m_pLeg->SetLegSpeed(speed);
					   m_pLeg->SetDamage(damage);
					   m_goods.push_back(m_pLeg);
					   break;
				   case 6:
					   m_pAngel = new CAngel;
					   m_pAngel->Init(name);
					   m_pAngel->SetPos(pos);
					   m_pAngel->SetVisible(visible);
					   m_pAngel->SetShowWidth(showWidth);
					   m_pAngel->SetShowHeight(showHeight);
					   m_pAngel->SetMapIndex(mapIndex);
					   m_goods.push_back(m_pAngel);
					   break;
				   case 7:
					   m_pPlayerHP = new CHP;
					   m_pPlayerHP->Init(name);
					   m_pPlayerHP->SetPos(pos);
					   m_pPlayerHP->SetVisible(visible);
					   m_pPlayerHP->SetShowWidth(showWidth);
					   m_pPlayerHP->SetShowHeight(showHeight);
					   m_pPlayerHP->SetMapIndex(mapIndex);
					   POINT pos={64,0};
					   m_pPlayerHP->SetSrcPos(pos);
					   m_goods.push_back(m_pPlayerHP);
					   break;
				   }
		}
			break;
			case 25:
			{
					   int desX, desY,mapIndex;
					   m_pMoney = new CMoney;
					   m_pMoney->Init();
					   element->Attribute("desX", &desX);
					   element->Attribute("desY", &desY);
					   element->Attribute("mapIndex", &mapIndex);
					   POINT pos = { desX, desY };
					   m_pMoney->SetPos(pos);
					   m_pMoney->SetMapIndex(mapIndex);
					   m_money.push_back(m_pMoney);
			}
				break;
		}
		element = element->NextSiblingElement();
	}
	m_pNumber = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("number"));
	m_pNumber->Init();
	m_pNumber->SetShowWidth(m_pNumber->GetFrameWidth());
	m_pNumber->SetShowHeight(m_pNumber->GetFrameHeight());
	POINT pos = { 50, 100 };
	m_pNumber->SetDesPos(pos);
	m_pNumber->UpdateMAatrix();

	m_pNumber1 = (CSingleImg*)CResManager::GetInstance()->GetRes(_T("number1"));
	m_pNumber1->Init();
	m_pNumber1->SetShowWidth(m_pNumber1->GetFrameWidth());
	m_pNumber1->SetShowHeight(m_pNumber1->GetFrameHeight());
	POINT pos2 = { 400, 310 };
	POINT pos1 = { 112, 0 };
	m_pNumber1->SetSrcPos(pos1);
	m_pNumber1->SetDesPos(pos2);
	m_pNumber1->UpdateMAatrix();
}

void CStage::Draw()
{
	DrawMap();
	POINT pos;
	pos.x = 28 * m_moneyCount;
	pos.y = 0;
	m_pNumber->SetSrcPos(pos);
	m_pNumber->Draw();
	if ((m_goods[7]->GetMapIndex() == m_curMapIndex) && m_goods[7]->GetVisible()
		&& m_goods[7]->GetVisibleOnMap())
		m_pNumber1->Draw();
	DrawExlpodeBlood();
	DrawDoor();
	DrawTile();
	DrawFire();
	DrawFly();
	DrawFlyMonster();
	DrawFlyDuke();
	DrawBob();
	DrawMonsterDead();
	DrawMask();
	DrawMaskHeart();
	DrawFeceMonster();
	DrawGoldenBox();
	m_pBulletPool->Render();
	DrawEnemyBullet();
	DrawPlayer();
	DrawGoods();
	DrawStartSurface();
	DrawBlood();
	DrawGuide();
	DrawPlayerHeart();
	DrawBombExplode();
	DrawMatherHeart();
	DrawMoney();
	m_pEnd->DrawLost();
	m_goods[5]->Function();
}

void CStage::Update()
{
	UpdateFire();
	UpdateFly();
	UpdateFlyMonster();
	m_pBulletPool->Update();
	ShotFeces(m_stone[m_curMapIndex]);
	UpdatePlayer();
	UpdateDoor();
	UpdateFlyDuke();
	FlyDukeFireFly();
	StartSurfaceMove();
	UpdateExplodeBlood();
	Recover();
	UpdateGuide();
	UpdateBombExplode();
	UpdateBob();
	UpdateMonsterDead();
	UpdateMatherHeart();
	MatherHeartAttack();
	MatherHeartFireBob();
	UpdateGoldenBox();
	UpdateMoney();
	UseGoods();
	LegAttack();
	if (m_curMapIndex == m_bossRoomNum&&m_isStartMusic==0)
	{
		CAudio4Bass::GetInstance()->ChannelStop(1);
		CAudio4Bass::GetInstance()->ChannelPlay(2, true);
		m_isStartMusic++;
	}
	if (m_curMapIndex != m_bossRoomNum&&m_isStartMusic == 1)
	{
		CAudio4Bass::GetInstance()->ChannelStop(2);
		CAudio4Bass::GetInstance()->ChannelPlay(1, true);
		m_isStartMusic++;
	}
}

void CStage::Move()
{
	IsPlayerUpdate(m_map[m_curMapIndex], m_stone[m_curMapIndex], 64, 32);
	BulletMove(m_stone[m_curMapIndex], 64, 32);
	TileMove();
	BobMove(m_stone[m_curMapIndex]);
	MaskMove();
	MaskHeartMove();
	FeceMonsterMove();
	EnemyBulletMove();
	if(m_pEnd->GetMapIndex()==m_curMapIndex)
		m_pEnd->Move();
	GoodsMove();
}

void CStage::Collision()
{
	Bullet_Fly();
	Bullet_FlyDuke();
	Bullet_Fire();
	Bullet_FlyMonster();
	Fire_Player();
	Fire_Fly();
	FlyDukeMove();
	Fly_Player();
	FlyDuke_Player();
	FlyMonster_Player();
	BombExplode_Player();
	Tile_Player();
	Bullet_Bob();
	Bob_Player();
	Bullet_Mask();
	Mask_Player();
	Bullet_MaskHeart();
	MaskHeart_Player();
	Bullet_FeceMonster();
	FeceMonster_Player();
	Bullet_MatherHeart();
	Bullet_Player();
	GoldenBox_Player();
	Goods_Player();
	BombExplode_Fly();
	BombExplode_MaskHeart();
	BombExplode_Fire();
	BombExplode_FlyMonster();
	BombExplode_Bob();
	BombExplode_Mask();
	BombExplode_FlyDuke();
	BombExplode_FeceMonster();
	BombExplode_Mother();
	Leg_Fly();
	Leg_Bob();
	Leg_FlyMonster();
	Leg_FlyDuke();
	Leg_Mask();
	Leg_FeceMonster();
	Leg_MaskHeart();
	Leg_MotherHeart();
	Money_Player();
}

void CStage::SetVisible(bool b)
{
	m_ExplodeVisible = b;
	m_pBulletPool->SetFalse();

	map<int, CDoor*>::iterator it = m_door.begin();
	for (; it != m_door.end(); it++)
	{
		if (it->second->GetDoorIndex() / 10 == m_curMapIndex)
			it->second->SetVisible(b);
	}

	map<int, Map*>::iterator iter = m_stone.begin();
	for (; iter != m_stone.end(); iter++)
	{
		iter->second->SetVisible(b);
	}
	
	vector<CFire*>::iterator i = m_fire.begin();
	for (; i != m_fire.end(); i++)
	{
		(*i)->SetVisibleOnMap(b);
	}

	vector<CFlyMonster*>::iterator it1 = m_flyMonster.begin();
	for (; it1 != m_flyMonster.end(); it1++)
	{
		if (m_curMapIndex == (*it1)->GetMapIndex() && (*it1)->GetVisible())
		{
			(*it1)->SetVisible(b);
		}
	}

	vector<CTile*>::iterator iter2 = m_tile.begin();
	for (; iter2 != m_tile.end(); iter2++)
	{
		(*iter2)->SetVisible(b);
	}

	m_pEnd->SetVisibleOmMap(b);

	vector<CGoods*>::iterator iter3 = m_goods.begin();
	for (; iter3 != m_goods.end(); iter3++)
	{
		(*iter3)->SetVisibleOnMap(b);
	}

	vector<CBombExplode*>::iterator iter4=m_bombExplode.begin();
	for(;iter4!=m_bombExplode.end();iter4++)
	{
		(*iter4)->SetIsExplode(false);
	}

	vector<CMoney*>::iterator iter5 = m_money.begin();
	for (; iter5 != m_money.end(); iter5++)
	{
		(*iter5)->SetVisibleOnMap(b);
	}
}

void CStage::DrawMoney()
{
	vector<CMoney*>::iterator it = m_money.begin();
	for (; it != m_money.end(); it++)
	{
		if ((*it)->GetMapIndex()==m_curMapIndex)
		{
			(*it)->Draw();
		}
	}
}

void CStage::DrawGoods()
{
	vector<CGoods*>::iterator it = m_goods.begin();
	for (; it != m_goods.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex)
			(*it)->Draw();
	}
}

void CStage::DrawMatherHeart()
{
	if(m_pMatherHeart!=nullptr&&m_pMatherHeart->GetMapIndex()==m_curMapIndex)
		m_pMatherHeart->Draw();
}

void CStage::DrawEnemyBullet()
{
	if (m_pPathBullet != nullptr)
		m_pPathBullet->Render();
}

void CStage::DrawFeceMonster()
{
	vector<CFeceMonster*>::iterator it = m_feceMonster.begin();
	for (; it != m_feceMonster.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex)
			(*it)->Draw();
	}
}

void CStage::DrawMaskHeart()
{
	map<int, CMaskHeart*>::iterator it = m_maskHeart.begin();
	for (; it != m_maskHeart.end(); it++)
	{
		if (it->second->GetMapIndex() == m_curMapIndex)
			it->second->DrawMaskHeart();
	}

	map<int, CMaskHeart*>::iterator it1 = m_HEART.begin();
	for (; it1 != m_HEART.end(); it1++)
	{
		if (it1->second->GetMapIndex() == m_curMapIndex)
			it1->second->DrawHeart();
	}
}

void CStage::DrawMask()
{
	vector<CMask*>::iterator iter=m_mask.begin();
	for(;iter!=m_mask.end();iter++)
	{
		if((*iter)->GetMapIndex()==m_curMapIndex)
			(*iter)->Draw();
	}
}

void CStage::DrawMonsterDead()
{
	vector<CMonsterDead*>::iterator iter=m_monsterDead.begin();
	for(;iter!=m_monsterDead.end();iter++)
	{
		(*iter)->Draw();
	}
}

void CStage::DrawBob()
{
	vector<CBob*>::iterator iter9=m_bob.begin();
	for(;iter9!=m_bob.end();iter9++)
	{
		if((*iter9)->GetMapIndex()==m_curMapIndex)
		 (*iter9)->Draw();
	}
}

void CStage::DrawTile()
{
	vector<CTile*>::iterator iter8 = m_tile.begin();
	for (; iter8 != m_tile.end(); iter8++)
	{
		if((*iter8)->GetMapIndex()==m_curMapIndex)
			(*iter8)->Draw();
	}
}

void CStage::DrawBombExplode()
{
	vector<CBombExplode*>::iterator it=m_bombExplode.begin();
	for(;it!=m_bombExplode.end();it++)
		(*it)->Draw();
}

void CStage::DrawExlpodeBlood()
{
	if (m_bossHP <= 0 && m_curMapIndex == m_bossRoomNum&&m_ExplodeVisible)
	{
		m_pExplodeBlood->Draw();
	}
}

void CStage::DrawBlood()
{
	if(m_curMapIndex==m_bossRoomNum&&m_bloodVisible)
	{
		POINT pos={0,64};
		m_pBlood->SetSrcPos(pos);
		m_pBlood->SetShowWidth(m_pBlood->GetFrameWidth());
		m_pBlood->Draw();
		pos.x=0;
		pos.y=0;
		m_pBlood->SetSrcPos(pos);
		m_pBlood->SetShowWidth((m_pBlood->GetFrameWidth()-40)-(220/m_bossHPSum)*(m_bossHPSum-m_bossHP));
		m_pBlood->Draw();
		if(m_bossHP<=0)
			m_bloodVisible=false;
	}
}

void CStage::DrawMap()
{
	map<int, Map*>::iterator it = m_map.begin();
	for (;it != m_map.end();it++)
	{
		it->second->UpdateMAatrix();
		it->second->Draw();
	}

	map<int, Map*>::iterator iter = m_stone.begin();
	for (;iter != m_stone.end();iter++)
	{
		if(m_curMapIndex==iter->second->GetMapIndex())
		{
			iter->second->UpdateMAatrix();
			iter->second->DrawTileMap(iter->second->GetSrcPos());
		}
	}
}

void CStage::DrawFire()
{
	vector<CFire*>::iterator iter1 = m_fire.begin();
	for (; iter1 != m_fire.end(); iter1++)
	{
		if((*iter1)->GetMapIndex()==m_curMapIndex)
			(*iter1)->Draw();
	}
}

void CStage::DrawFly()
{
	vector<CFly*>::iterator it = m_fly.begin();
	for (; it != m_fly.end(); it++)
	{
		if (m_curMapIndex == (*it)->GetMapIndex())
		{
			(*it)->Draw();
		}
	}
}

void CStage::DrawFlyMonster()
{
	vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
	for (; it != m_flyMonster.end(); it++)
	{
		if (m_curMapIndex == (*it)->GetMapIndex())
		{
			(*it)->Draw();
		}
	}
}

void CStage::DrawDoor()
{
	map<int, CDoor*>::iterator it = m_door.begin();
	for (; it != m_door.end();it++)
	{
		if(it->second->GetDoorIndex()/10==m_curMapIndex)
			it->second->Draw();
	}
}

void CStage::DrawPlayer()
{
	m_pPlayerBody->DrawShadow();
	if(m_invincibleCount%2==0)
	{
		m_pPlayerBody->Draw();
		m_pPlayerHead->Draw();
	}
	if(m_isInvincible)
	{
		m_invincibleCount++;
		if(m_invincibleCount==40)
		{
			m_isInvincible=false;
			m_invincibleCount=0;
		}
	}
}

void CStage::DrawFlyDuke()
{
	if (m_pFlyDuke!=nullptr&&m_pFlyDuke->GetMapIndex() == m_curMapIndex)
		m_pFlyDuke->Draw();
}

void CStage::DrawStartSurface()
{
	if (m_bossHP > 0)
	{
		if (m_VSVisible)
		{
			m_startSurface[7]->SetTransparent(0x00000000);
			m_VSVisible = false;
		}
		vector<Map*>::iterator it = m_startSurface.begin();
		for (; it != m_startSurface.end(); it++)
		{
			if (m_isStart)
			{
				(*it)->UpdateMAatrix();
				(*it)->Draw();
			}
		}
	}
}

void CStage::DrawGuide()
{
	if(!m_isStart)
	{
		m_pGuide->DrawFrame();
		map<int,CGuide*>::iterator it=m_guide.begin();
		for(;it!=m_guide.end();it++)
		{
			switch (it->second->GetState())
			{
			case eCUR:
				{
					POINT pos={227,163};
					it->second->SetSrcPos(pos);
				}
				break;
			case eGONE:
				{
					POINT pos={131,35};
					it->second->SetSrcPos(pos);
				}
				break;
			case eN_GONE:
				{
					POINT pos={131,67};
					it->second->SetSrcPos(pos);
				}
				break;
			case eBOSS:
				{
					POINT pos={67,163};
					it->second->SetSrcPos(pos);
				}
				break;
			}
			if (it->second->GetPos().y >= 52 && it->second->GetPos().y <= 104 && 
				it->second->GetPos().x >= 694 && it->second->GetPos().x <= 765)
				it->second->DrawTile();
		}
	}
}

void CStage::DrawPlayerHeart()
{
	POINT pos;
	if (!m_isStart)
	{
		for (int i = 0; i < m_pPlayerHead->GetHp() / 2; i++)
		{
			pos.x = 0;
			pos.y = 0;
			m_heart[i]->SetSrcPos(pos);
			m_heart[i]->Draw();
		}
		if (m_pPlayerHead->GetHp() % 2 == 1)
		{
			pos.x = m_heart[0]->GetFrameWidth();
			pos.y = 0;
			m_heart[m_pPlayerHead->GetHp() / 2]->SetSrcPos(pos);
			m_heart[m_pPlayerHead->GetHp() / 2]->Draw();
		}
		for (int i = (m_pPlayerHead->GetHp() +1)/ 2; i < m_pPlayerHead->GetCountHp()/2; i++)
		{
			pos.x = 2*m_heart[0]->GetFrameWidth();
			pos.y = 0;
			m_heart[i]->SetSrcPos(pos);
			m_heart[i]->Draw();
		}
	}
}

void CStage::DrawGoldenBox()
{
	if(m_pEnd->GetMapIndex()==m_curMapIndex&&!IsMonsterInRoom())
		m_pEnd->Draw();
}

void CStage::UpdateMoney()
{
	vector<CMoney*>::iterator it = m_money.begin();
	for (; it != m_money.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex)
		{
			if (!IsMonsterInRoom())
				(*it)->SetVisible(true);
			(*it)->Update();
		}
	}
}

void CStage::UpdateGoldenBox()
{
	if(m_pEnd->GetMapIndex()==m_curMapIndex)
		m_pEnd->Update();
	if(m_pEnd->GetMapIndex()==m_curMapIndex&&!IsMonsterInRoom())
	{
		m_pEnd->SetVisible(true);
		
	}
}

void CStage::UpdateMatherHeart()
{
	if(m_pMatherHeart!=nullptr)
		m_pMatherHeart->Update();
}

void CStage::UpdateEnemyBullet()
{
	static DWORD preTime1 = GetTickCount();
	DWORD curTime1 = GetTickCount();
	if (curTime1 - preTime1 > 5000)
	{
		preTime1 = curTime1;
		if(m_pMatherHeart->GetCurRow()==0)
			m_pMatherHeart->ReSet(0,1,0,1,1,1);
		else if(m_pMatherHeart->GetCurRow()==1)
			m_pMatherHeart->ReSet(0,0,0,1,0,0);
	
	}

	if (m_pPathBullet != nullptr)
	{
		if(m_pMatherHeart->GetCurRow()==1)
		{
			static DWORD preTime = GetTickCount();
			DWORD curTime = GetTickCount();
			if (curTime - preTime > 50)
			{
				preTime = curTime;
				m_pPathBullet->SetPath();
			}
		}

		if(m_pMatherHeart->GetCurRow()==0)
		{
			static DWORD preTime = GetTickCount();
			DWORD curTime = GetTickCount();
			if (curTime - preTime > 200)
			{
				preTime = curTime;
				m_pPathBullet->SetPath1();
			}
		}
	}
}

void CStage::UpdateBombExplode()
{
	vector<CBombExplode*>::iterator it=m_bombExplode.begin();
	for(;it!=m_bombExplode.end();it++)
		(*it)->Update();
}

void CStage::UpdateMonsterDead()
{
	vector<CMonsterDead*>::iterator iter=m_monsterDead.begin();
	for(;iter!=m_monsterDead.end();iter++)
	{
		(*iter)->Update();
	}
}

void CStage::UpdateBob()
{
	vector<CBob*>::iterator iter=m_bob.begin();
	for(;iter!=m_bob.end();iter++)
	{
		if((*iter)->GetMapIndex()==m_curMapIndex&&(*iter)->GetVisible())
			(*iter)->Update();
	}
}

void CStage::UpdateFire()
{
	vector<CFire*>::iterator it = m_fire.begin();
	for (; it != m_fire.end(); it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex)
			(*it)->Update();
	}
}

void CStage::UpdateFly()
{
	vector<CFly*>::iterator it = m_fly.begin();
	for (; it != m_fly.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex)
			(*it)->Update();
	}
}

void CStage::UpdateFlyMonster()
{
	vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
	for (; it != m_flyMonster.end(); it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex)
			(*it)->Update();
	}
}

void CStage::UpdatePlayer()
{
	m_pPlayerHead->Update();
	m_pPlayerBody->Update();
}

void CStage::UpdateDoor()
{
	if (IsMonsterInRoom()&&m_doorUpdateCount<4)
	{
		map<int, CDoor*>::iterator it = m_door.begin();
		for (; it != m_door.end(); it++)
		{
			if (it->second->GetDoorIndex() / 10 == m_curMapIndex)
				it->second->Update();
		}
		m_doorUpdateCount++;
	}
	else if (!IsMonsterInRoom() && m_doorUpdateCount == 4)
	{
		map<int, CDoor*>::iterator it = m_door.begin();
		for (; it != m_door.end(); it++)
		{
			if (it->second->GetDoorIndex() / 10 == m_curMapIndex)
				it->second->Update();
		}
		m_doorUpdateCount=0;
	}
}

void CStage::UpdateFlyDuke()
{
	if (m_pFlyDuke!=nullptr&&m_pFlyDuke->GetMapIndex() == m_curMapIndex&&!m_pFlyDuke->GetIsDead())
		m_pFlyDuke->UpdateDuke();
}

void CStage::UpdateExplodeBlood()
{
	if (m_ExplodeVisible&&m_bossHP <= 0 && (m_pExplodeBlood->GetCurFrame() != 2 || m_pExplodeBlood->GetCurRow() != 3))
	{
		m_explodeBloodCount++;
		if (m_explodeBloodCount == 2)
		{
			m_pExplodeBlood->Update();
			m_explodeBloodCount = 0;
			POINT pos = m_pExplodeBlood->GetDesPos();
			if (m_pExplodeBlood->GetCurFrame() == 0 && m_pExplodeBlood->GetCurRow() == 3)
			{
				pos.y += 10;
				m_pExplodeBlood->SetDesPos(pos);
			}
		}
	}
}

void CStage::UpdateGuide()
{
	if((m_right||m_left||m_up||m_down)&&m_guideCount==0)
	{
		m_guideCount=1;
		map<int,CGuide*>::iterator iter = m_guide.begin();
		for (; iter != m_guide.end(); iter++)
		{
			POINT pos=iter->second->GetPos();
			if(iter->second->GetMapIndex()==m_curMapIndex&&iter->second->GetState()!=eBOSS)
				iter->second->SetState(eGONE);
			if(iter->second->GetMapIndex()==m_doorIndex&&iter->second->GetState()!=eBOSS)
				iter->second->SetState(eCUR);
			if(m_right)
				pos.x-=16;
			else if(m_left)
				pos.x+=16;
			else if(m_up)
				pos.y+=13;
			else if(m_down)
				pos.y-=13;
			iter->second->SetDesPos(pos);
		}
	}
	if(!m_right&&!m_left&&!m_up&&!m_down)
		m_guideCount=0;
}

void CStage::FireMove(int dir)
{
	vector<CFire*>::iterator it = m_fire.begin();
	for (; it != m_fire.end(); it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex)
		{
			(*it)->SetDir(dir);
			(*it)->MoveOnMap();
		}
	}
}

void CStage::FlyMoveOnMap(int dir)
{
	vector<CFly*>::iterator it = m_fly.begin();
	for (; it != m_fly.end(); it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex)
		{
			(*it)->SetDir(dir);
			(*it)->MoveOnMap();
		}
	}
}

void CStage::FlyMonsterMove(Map*map)
{
	vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
	for (; it != m_flyMonster.end(); it++)
		if((*it)->GetMapIndex()==m_curMapIndex)
			(*it)->Move(map);
}

void CStage::EnemyBulletMove()
{
	if (m_pPathBullet != nullptr)
	{
		m_pPathBullet->PathMove();
	}
}

void CStage::MaskMove()
{
	vector<CMask*>::iterator iter=m_mask.begin();
	for(;iter!=m_mask.end();iter++)
	{
		if((*iter)->GetMapIndex()==m_curMapIndex)
		{
			(*iter)->UpdateRc();
			(*iter)->UpdateAim(m_pPlayerBody->GetPlayerPos());
			(*iter)->Move();
		}
	}
}

void CStage::BobMove(Map*stone)
{
	vector<CBob*>::iterator iter=m_bob.begin();
	for(;iter!=m_bob.end();iter++)
	{
		if((*iter)->GetMapIndex()==m_curMapIndex&&(*iter)->GetVisible())
			(*iter)->AStarMove(stone);
	}
}

void CStage::TileMove()
{
	vector<CTile*>::iterator iter8 = m_tile.begin();
	for (; iter8 != m_tile.end(); iter8++)
	{
		if((*iter8)->GetMapIndex()==m_curMapIndex)
		(*iter8)->Move();
	}
}

void CStage::FlyMonsterMoveOnMap(int dir)
{
	vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
	for (; it != m_flyMonster.end(); it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex)
		{
			(*it)->SetDir(dir);
			(*it)->MoveOnMap();
		}
	}
}

void CStage::LegMoveOnMap(int dir)
{
	if(m_pLeg->GetLegVisible())
	{
		m_pLeg->SetDirOnMap(dir);
		m_pLeg->MoveOnMap();
	}
}

void CStage::BobMoveOnMap(int dir)
{
	vector<CBob*>::iterator it=m_bob.begin();
	for(;it!=m_bob.end();it++)
	{
		if((*it)->GetMapIndex()==m_curMapIndex&&(*it)->GetVisible())
		{
			(*it)->SetDir(dir);
			(*it)->MoveOnMap();
		}
	}
}

void CStage::DoorMoveOnMap(int dir)
{
	map<int, CDoor*>::iterator it = m_door.begin();
	for (; it != m_door.end(); it++)
	{
		if (it->second->GetDoorIndex() / 10 == m_curMapIndex)
		{
			it->second->SetDir(dir);
			it->second->MoveOnMap();
		}
	}
}

void CStage::FeceMonsterMove()
{
	vector<CFeceMonster*>::iterator iter = m_feceMonster.begin();
	for (; iter != m_feceMonster.end(); iter++)
	{
		if ((*iter)->GetVisible() && (*iter)->GetMapIndex() == m_curMapIndex)
		{
			(*iter)->UpdateAimPos();
			(*iter)->Move(m_stone[m_curMapIndex]);
		}
	}
}

void CStage::PlayerMove(Map*pMap,int tileWidth,int num)
{
	m_pPlayerHead->Move(pMap, tileWidth,  num);
	m_pPlayerBody->Move(pMap, tileWidth,  num);
}

void CStage::BulletMove(Map*pMap,int tileWidth,int num)
{
	m_pBulletPool->Move(pMap,tileWidth,num);
}

void CStage::FlyDukeMove()
{
	POINT pos = m_pFlyDuke->GetPos();
	pos.y -= 150;
	pos.x -= 150;
	if (m_pFlyDuke->GetMapIndex() == m_curMapIndex&&!m_pFlyDuke->GetIsDead())
	{
		m_pFlyDuke->Move(m_map[m_curMapIndex]);
	}
	m_pExplodeBlood->SetDesPos(pos);
}

void CStage::GoodsMove()
{
	m_pPlayerBody->UpdateBodyRect();
	vector<CGoods*>::iterator it = m_goods.begin();
	for (; it != m_goods.end(); it++)
	{
		(*it)->UpdateRc();
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
		{
			if (it != m_goods.begin())
			{
				if (!m_pPlayerHead->GetIsHold())
				{
					(*it)->Move();
				}
				else if (m_pPlayerHead->GetIsHold()&&IsHit((*it)->GetRc(),m_pPlayerBody->GetBodyRect()))
				{
					POINT pos = m_pPlayerHead->GetPlayerPos();
					(*it)->SetPos(pos);
				}
			}
		}
	}
}

void CStage::MaskHeartMove()
{
	map<int, CMaskHeart*>::iterator it = m_maskHeart.begin();
	for (; it != m_maskHeart.end(); it++)
	{
		if (it->second->GetMapIndex() == m_curMapIndex&&it->second->GetVisible())
		{
			it->second->UpdateMaskRc();
			it->second->MaskHeartUpdateAim(m_pPlayerBody->GetPlayerPos());
			it->second->Move();
		}
	}

	map<int, CMaskHeart*>::iterator it1 = m_HEART.begin();
	for (; it1 != m_HEART.end(); it1++)
	{
		if (it1->second->GetVisible()&&it1->second->GetMapIndex() == m_curMapIndex)
		{
			it1->second->HeartUpdate();
			it1->second->HeartMove();
		}
	}
}

void CStage::FlyDukeFireFly()
{
	POINT pos;
	pos.x = m_pFlyDuke->GetPos().x;
	pos.y = m_pFlyDuke->GetPos().y;
	int count = 0;
	if (m_pFlyDuke->GetCurRow() == 0)
		m_isFireFly = true;
	if (m_pFlyDuke->GetCurFrame() == 0 && m_pFlyDuke->GetCurRow() == 1 && m_isFireFly&&m_pFlyDuke->GetVisible())
	{
		vector<CFly*>::iterator it = m_fly.begin();
		for (; it != m_fly.end(); it++)
		{
			if ((*it)->GetMapIndex() == m_curMapIndex && !(*it)->GetVisible())
			{
				count++;
				if (count == 1)
				{
					pos.x -= 100;
					pos.y += 70;
				}
				else if (count == 2)
				{
					pos.x += 50;
				}
				else if (count == 3)
				{
					pos.x += 100;
				}
				(*it)->SetPos(pos);
				(*it)->SetVisible(true);
				(*it)->SetHP(1);
				if (count % 3 == 0)
				{
					m_isFireFly = false;
					break;
				}
			}
		}
	}
	srand(clock());
	if (m_pFlyDuke->GetCurFrame() == 1 && m_pFlyDuke->GetCurRow() == 0 && m_pFlyDuke->GetVisible())
	{
		pos.x=rand()%20-10+pos.x;
		if (pos.x < 170)
			pos.x = 170;
		else if(pos.x>700)
			pos.x = 700;
		m_pFlyDuke->SetPos(pos);
	}    
	else if (m_pFlyDuke->GetCurFrame() == 0 && m_pFlyDuke->GetCurRow() == 1 && m_pFlyDuke->GetVisible())
	{
		pos.y = m_pFlyDuke->GetPos().y;
		pos.y = rand() % 10-5 + pos.y;
		if (pos.y < 120)
			pos.y = 120;
		else if (pos.y>455)
			pos.y = 455;
		m_pFlyDuke->SetPos(pos);
	}
}

void CStage::IsPlayerUpdate(Map*m_pMap,Map*m_pStone,int tileWidth,int num)
{
	RECT *rc = (RECT*)CPlatform::GetInstance()->GetPlatData(_T("rect"));
	int clientHeight = rc->bottom;
	int clientWidth = rc->right;
	int pX = m_pPlayerBody->GetPlayerPos().x;
	int pY = m_pPlayerBody->GetPlayerPos().y;
	int mX = m_pMap->GetSrcPos().x;
	int mY = m_pMap->GetSrcPos().y;
	int dir=m_pPlayerBody->GetPlayerDir();
	m_pPlayerBody->SetBottom(m_pStone,tileWidth,num);
	m_pPlayerBody->SetTop(m_pStone,tileWidth, num);
	m_pPlayerBody->SetLeft(m_pStone, tileWidth, num);
	m_pPlayerBody->SetRight(m_pStone, tileWidth, num);
	switch (dir)
	{
	case eNONE:
		break;
	case eUP:
		if (pY < clientHeight / 2 && mY > 0 && m_pPlayerBody->GetTop())
		{
			m_pMap->SetMapDir(eUP);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eDOWN);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eUP);
			m_pStone->Update();
			FireMove(eDOWN);
			FlyMoveOnMap(eDOWN);
			FlyMonsterMoveOnMap(eDOWN);
			DoorMoveOnMap(eDOWN);
			BobMoveOnMap(eDOWN);
			LegMoveOnMap(eDOWN);
		}
		else
		{
			PlayerMove(m_pStone, tileWidth, num);
		}
		break;
	case eDOWN:
		if (pY > clientHeight / 2 && mY + clientHeight < m_pMap->GetHeight() && m_pPlayerBody->GetBottom())
		{
			m_pMap->SetMapDir(eDOWN);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eUP);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eDOWN);
			m_pStone->Update();
			FireMove(eUP);
			FlyMoveOnMap(eUP);
			FlyMonsterMoveOnMap(eUP);
			DoorMoveOnMap(eUP);
			BobMoveOnMap(eUP);
			LegMoveOnMap(eUP);
		}
		else
			PlayerMove(m_pStone, tileWidth, num);
		break;
	case eLEFT:
		if (pX < clientWidth / 2 && mX > 0 && m_pPlayerBody->GetLeft())
		{
			m_pMap->SetMapDir(eLEFT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eRIGHT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eLEFT);
			m_pStone->Update();
			FireMove(eRIGHT);
			FlyMoveOnMap(eRIGHT);
			FlyMonsterMoveOnMap(eRIGHT);
			DoorMoveOnMap(eRIGHT);
			BobMoveOnMap(eRIGHT);
			LegMoveOnMap(eRIGHT);
		}
		else
			PlayerMove(m_pStone, tileWidth, num);
		break;
	case eRIGHT:
		if (pX > clientWidth / 2 && mX + clientWidth < m_pMap->GetWidth() && m_pPlayerBody->GetRight())
		{
			m_pMap->SetMapDir(eRIGHT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eLEFT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eRIGHT);
			m_pStone->Update();
			FireMove(eLEFT);
			FlyMoveOnMap(eLEFT);
			FlyMonsterMoveOnMap(eLEFT);
			DoorMoveOnMap(eLEFT);
			BobMoveOnMap(eLEFT);
			LegMoveOnMap(eLEFT);
		}
		else
			PlayerMove(m_pStone, tileWidth, num);
		break;
	case eUP | eLEFT:
		if (pY < clientHeight / 2 && mY > 0 && m_pPlayerBody->GetTop())
		{
			m_pMap->SetMapDir(eUP);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eDOWN);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eUP);
			m_pStone->Update();
			FireMove(eDOWN);
			FlyMoveOnMap(eDOWN);
			FlyMonsterMoveOnMap(eDOWN);
			DoorMoveOnMap(eDOWN);
			BobMoveOnMap(eDOWN);
			LegMoveOnMap(eDOWN);
		}
		else if (pY > 0)
		{
			m_pPlayerBody->SetDir(eUP);
			m_pPlayerHead->SetDir(eUP);
			PlayerMove(m_pStone, tileWidth, num);
		}
		if (pX < clientWidth / 2 && mX > 0 &&  m_pPlayerBody->GetLeft())
		{
			m_pMap->SetMapDir(eLEFT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eRIGHT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eLEFT);
			m_pStone->Update();
			FireMove(eRIGHT);
			FlyMoveOnMap(eRIGHT);
			FlyMonsterMoveOnMap(eRIGHT);
			DoorMoveOnMap(eRIGHT);
			BobMoveOnMap(eRIGHT);
			LegMoveOnMap(eRIGHT);
		}
		else if (pX > 0)
		{
			m_pPlayerBody->SetDir(eLEFT);
			m_pPlayerHead->SetDir(eLEFT);
			PlayerMove(m_pStone, tileWidth, num);
		}
		m_pPlayerBody->SetDir(eUP | eLEFT);
		m_pPlayerHead->SetDir(eUP | eLEFT);
		break;
	case eDOWN | eLEFT:
		if (pX < clientWidth / 2 && mX > 0 && m_pPlayerBody->GetLeft())
		{
			m_pMap->SetMapDir(eLEFT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eRIGHT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eLEFT);
			m_pStone->Update();
			FireMove(eRIGHT);
			FlyMoveOnMap(eRIGHT);
			FlyMonsterMoveOnMap(eRIGHT);
			DoorMoveOnMap(eRIGHT);
			BobMoveOnMap(eRIGHT);
			LegMoveOnMap(eRIGHT);
		}
		else if (pX > 0)
		{
			m_pPlayerBody->SetDir(eLEFT);
			m_pPlayerHead->SetDir(eLEFT);
			PlayerMove(m_pStone, tileWidth, num);
		}
		if (pY > clientHeight / 2 && mY + clientHeight < m_pMap->GetHeight() && m_pPlayerBody->GetBottom())
		{
			m_pMap->SetMapDir(eDOWN);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eUP);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eDOWN);
			m_pStone->Update();
			FireMove(eUP);
			FlyMoveOnMap(eUP);
			FlyMonsterMoveOnMap(eUP);
			DoorMoveOnMap(eUP);
			BobMoveOnMap(eUP);
			LegMoveOnMap(eUP);
		}
		else if (pY<clientHeight)
		{
			m_pPlayerBody->SetDir(eDOWN);
			m_pPlayerHead->SetDir(eDOWN);
			PlayerMove(m_pStone, tileWidth, num);
		}
		m_pPlayerBody->SetDir(eDOWN | eLEFT);
		m_pPlayerHead->SetDir(eDOWN | eLEFT);
		break;
	case eUP | eRIGHT:
		if (pY < clientHeight / 2 && mY > 0 && m_pPlayerBody->GetTop())
		{
			m_pMap->SetMapDir(eUP);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eDOWN);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eUP);
			m_pStone->Update();
			FireMove(eDOWN);
			FlyMoveOnMap(eDOWN);
			FlyMonsterMoveOnMap(eDOWN);
			DoorMoveOnMap(eDOWN);
			BobMoveOnMap(eDOWN);
			LegMoveOnMap(eDOWN);
		}
		else if (pY > 0)
		{
			m_pPlayerBody->SetDir(eUP);
			m_pPlayerHead->SetDir(eUP);
			PlayerMove(m_pStone, tileWidth, num);
		}
		if (pX > clientWidth / 2 && mX + clientWidth < m_pMap->GetWidth() && m_pPlayerBody->GetRight())
		{
			m_pMap->SetMapDir(eRIGHT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eLEFT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eRIGHT);
			m_pStone->Update();
			FireMove(eLEFT);
			FlyMoveOnMap(eLEFT);
			FlyMonsterMoveOnMap(eLEFT);
			DoorMoveOnMap(eLEFT);
			BobMoveOnMap(eLEFT);
			LegMoveOnMap(eLEFT);
		}
		else if (pX<clientWidth)
		{
			m_pPlayerBody->SetDir(eRIGHT);
			m_pPlayerHead->SetDir(eRIGHT);
			PlayerMove(m_pStone, tileWidth, num);
		}
		m_pPlayerBody->SetDir(eUP | eRIGHT);
		m_pPlayerHead->SetDir(eUP | eRIGHT);
		break;
	case eDOWN | eRIGHT:
		if (pY > clientHeight / 2 && mY + clientHeight < m_pMap->GetHeight() && m_pPlayerBody->GetBottom())
		{
			m_pMap->SetMapDir(eDOWN);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eUP);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eDOWN);
			m_pStone->Update();
			FireMove(eUP);
			FlyMoveOnMap(eUP);
			FlyMonsterMoveOnMap(eUP);
			DoorMoveOnMap(eUP);
			BobMoveOnMap(eUP);
			LegMoveOnMap(eUP);
		}
		else if (pY<clientHeight)
		{
			m_pPlayerBody->SetDir(eDOWN);
			m_pPlayerHead->SetDir(eDOWN);
			PlayerMove(m_pStone, tileWidth, num);
		}
		if (pX > clientWidth / 2 && mX + clientWidth < m_pMap->GetWidth() && m_pPlayerBody->GetRight())
		{
			m_pMap->SetMapDir(eRIGHT);
			m_pMap->Update();
			m_pBulletPool->SetDirOnMap(eLEFT);
			m_pBulletPool->MoveOnMap();
			m_pStone->SetMapDir(eRIGHT);
			m_pStone->Update();
			FireMove(eLEFT);
			FlyMoveOnMap(eLEFT);
			FlyMonsterMoveOnMap(eLEFT);
			DoorMoveOnMap(eLEFT);
			BobMoveOnMap(eLEFT);
			LegMoveOnMap(eLEFT);
		}
		else if (pX < clientWidth)
		{
			m_pPlayerBody->SetDir(eRIGHT);
			m_pPlayerHead->SetDir(eRIGHT);
			PlayerMove(m_pStone, tileWidth, num);
		}
		m_pPlayerBody->SetDir(eDOWN | eRIGHT);
		m_pPlayerHead->SetDir(eDOWN | eRIGHT);
		break;
	}
}

void CStage::MapChange()
{
	map<int, CDoor*>::iterator it = m_door.begin();
	for (; it != m_door.end();it++)
	{
		int doorX = it->second->GetDesPos().x;
		int doorY = it->second->GetDesPos().y;
		if (it->second->GetDoorIndex()/10 == m_curMapIndex
			&&it->second->GetDoorType() == 2 && it->second->GetCurRow()==4
			&&m_pPlayerBody->GetBodyRect().right > doorX-10 &&
			m_pPlayerBody->GetBodyRect().right < doorX+30 
			&&m_pPlayerBody->GetBodyRect().top >doorY +10&&
			m_pPlayerBody->GetBodyRect().top < doorY+40 &&
			(m_pPlayerBody->GetPlayerDir() == eRIGHT ||
			m_pPlayerBody->GetPlayerDir() == (eRIGHT | eDOWN) ||
			m_pPlayerBody->GetPlayerDir() == (eRIGHT | eUP)))
		{
			m_doorIndex = it->second->GetDoorIndex()%10;
			if (m_doorIndex == m_bossRoomNum)
				m_isStart = true;
			m_right = true;
			break;
		}
		if (it->second->GetDoorIndex() / 10 == m_curMapIndex
			&&it->second->GetDoorType() == 4 && it->second->GetCurRow() == 0
			&&m_pPlayerBody->GetBodyRect().left < doorX+68 &&
			m_pPlayerBody->GetBodyRect().right > doorX + 30
			&&m_pPlayerBody->GetBodyRect().top > doorY + 10 &&
			m_pPlayerBody->GetBodyRect().top < doorY + 40 &&
			(m_pPlayerBody->GetPlayerDir() == eLEFT ||
			m_pPlayerBody->GetPlayerDir() == (eLEFT | eDOWN) ||
			m_pPlayerBody->GetPlayerDir() == (eLEFT | eUP)) )
		{
			m_doorIndex = it->second->GetDoorIndex()%10;
			if (m_doorIndex == m_bossRoomNum)
				m_isStart = true;
			m_left = true;
			break;
		}
		if (it->second->GetDoorIndex() / 10 == m_curMapIndex
			&&it->second->GetDoorType() == 1 && it->second->GetCurFrame() == 4
			&&m_pPlayerBody->GetBodyRect().left < doorX + 60 &&
			m_pPlayerBody->GetBodyRect().left > doorX + 26
			&& m_pPlayerBody->GetBodyRect().top > doorY + 48 &&
			m_pPlayerBody->GetBodyRect().top < doorY + 128 &&
			(m_pPlayerBody->GetPlayerDir() == eUP ||
			m_pPlayerBody->GetPlayerDir() == (eUP | eLEFT) ||
			m_pPlayerBody->GetPlayerDir() == (eUP | eRIGHT)))
		{
			m_doorIndex = it->second->GetDoorIndex()%10;
			if (m_doorIndex == m_bossRoomNum)
				m_isStart = true;
			m_up = true;
			break;
		}
		if (it->second->GetDoorIndex() / 10 == m_curMapIndex
			&&it->second->GetDoorType() == 3 && it->second->GetCurFrame() == 0
			&&m_pPlayerBody->GetBodyRect().left < doorX + 42 &&
			m_pPlayerBody->GetBodyRect().left > doorX+22 
			&& m_pPlayerBody->GetBodyRect().bottom > doorY - 40 &&
			m_pPlayerBody->GetBodyRect().bottom < doorY+20  &&
			(m_pPlayerBody->GetPlayerDir() == eDOWN ||
			m_pPlayerBody->GetPlayerDir() == (eDOWN | eLEFT) ||
			m_pPlayerBody->GetPlayerDir() == (eDOWN | eRIGHT)))
		{
			m_doorIndex = it->second->GetDoorIndex() % 10;
			if (m_doorIndex == m_bossRoomNum)
				m_isStart = true;
			m_down = true;
			break;
		}
	}
}

void CStage::MapMove()
{
	POINT posDoorIndex = { m_map[m_doorIndex]->GetDesPos().x, m_map[m_doorIndex]->GetDesPos().y };
	POINT posCurMap = { m_map[m_curMapIndex]->GetDesPos().x, m_map[m_curMapIndex]->GetDesPos().y };
	POINT posHead = { m_pPlayerHead->GetPlayerPos().x, m_pPlayerHead->GetPlayerPos().y };
	POINT posBody = { m_pPlayerBody->GetPlayerPos().x, m_pPlayerBody->GetPlayerPos().y };
	if (m_right)
	{
		SetVisible(false);

		if (posDoorIndex.x > 0)
		{
			posDoorIndex.x -= m_mapSpeed;
			posCurMap.x -= m_mapSpeed;
			posBody.x -= m_mapSpeed;
			posHead.x -= m_mapSpeed;
			m_map[m_doorIndex]->SetDesPos(posDoorIndex);
			m_map[m_curMapIndex]->SetDesPos(posCurMap);
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
		}
		else if (posDoorIndex.x == 0 && !m_isStart)
		{
			posBody.x = m_door[m_curMapIndex+m_doorIndex*10]->GetDesPos().x + 50;
			posHead.x = posBody.x - 1;
			posBody.y = m_door[m_curMapIndex + m_doorIndex*10]->GetDesPos().y + 5;
			posHead.y = posBody.y - 22;
			m_curMapIndex = m_doorIndex;
			m_right = false;
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
			SetVisible(true);
		}
	}
	else if(m_left)
	{
		SetVisible(false);

		if (posDoorIndex.x < 0)
		{
			posDoorIndex.x += m_mapSpeed;
			posCurMap.x += m_mapSpeed;
			posBody.x += m_mapSpeed;
			posHead.x += m_mapSpeed;
			m_map[m_doorIndex]->SetDesPos(posDoorIndex);
			m_map[m_curMapIndex]->SetDesPos(posCurMap);
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
		}
		else if (posDoorIndex.x == 0 && !m_isStart)
		{
			posBody.x = m_door[m_curMapIndex  + m_doorIndex*10]->GetDesPos().x - 50;
			posHead.x = posBody.x - 1;
			posBody.y = m_door[m_curMapIndex  + m_doorIndex*10]->GetDesPos().y + 5;
			posHead.y = posBody.y - 22;
			m_curMapIndex = m_doorIndex;
			m_left = false;
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
			SetVisible(true);
		}
	}
	else if (m_up)
	{
		SetVisible(false);

		if (posDoorIndex.y < 0)
		{
			posDoorIndex.y += m_mapSpeed;
			posCurMap.y += m_mapSpeed;
			if (posBody.y < 400)
			{
				posBody.y += m_mapSpeed;
				posHead.y += m_mapSpeed;
			}
			m_map[m_doorIndex]->SetDesPos(posDoorIndex);
			m_map[m_curMapIndex]->SetDesPos(posCurMap);
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
		}
		if (posDoorIndex.y == 0 && !m_isStart)
		{
			posBody.x = m_door[m_curMapIndex  + m_doorIndex*10]->GetDesPos().x + 10;
			posHead.x = posBody.x - 1;
			posBody.y = m_door[m_curMapIndex  + m_doorIndex*10]->GetDesPos().y - 50;
			posHead.y = posBody.y - 22;
			m_curMapIndex = m_doorIndex;
			m_up = false;
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
			SetVisible(true);
		}
	}
	else if (m_down)
	{
		SetVisible(false);

		if (posDoorIndex.y > 0)
		{
			posDoorIndex.y -= m_mapSpeed;
			posCurMap.y -= m_mapSpeed;
			if (posBody.y > 150)
			{
				posBody.y -= m_mapSpeed;
				posHead.y -= m_mapSpeed;
			}
			m_map[m_doorIndex]->SetDesPos(posDoorIndex);
			m_map[m_curMapIndex]->SetDesPos(posCurMap);
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);
		}
		if (posDoorIndex.y == 0 && !m_isStart)
		{
			posBody.x = m_door[m_curMapIndex + m_doorIndex * 10]->GetDesPos().x + 10;
			posHead.x = posBody.x - 1;
			posBody.y = m_door[m_curMapIndex + m_doorIndex * 10]->GetDesPos().y + 50;
			posHead.y = posBody.y - 22;
			m_curMapIndex = m_doorIndex;
			m_down = false;
			m_pPlayerBody->SetPos(posBody);
			m_pPlayerHead->SetPos(posHead);

			SetVisible(true);

		}
	}
}

void CStage::BombExplode_MaskHeart()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	map<int, CMaskHeart*>::iterator iter = m_HEART.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_HEART.end(); iter++)
		{
			iter->second->UpdateHeartRc();
			if ((*it)->GetIsExplode() && (iter)->second->GetVisible()
				&& IsHit((*it)->GetRect(), (iter)->second->GetHeartRc())
				&&(iter)->second->GetMapIndex()==m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(iter)->second->SetHp((iter)->second->GetHp() - 2);
				if ((iter)->second->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					iter->second->SetVisible(false);
					m_maskHeart[iter->second->GetNum()]->SetVisible(false);
				}
			}
		}
	}
}

void CStage::BombExplode_Fly()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CFly*>::iterator iter = m_fly.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_fly.end(); iter++)
		{
			(*iter)->UpdateFlyRect();
			if ((*it)->GetIsExplode()&&(*iter)->GetVisible()
				&&IsHit((*it)->GetRect(),(*iter)->GetFlyRect())
				&&(*iter)->GetMapIndex()==m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetHP((*iter)->GetHP() - 2);
				if ((*iter)->GetHP() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter)->SetIsDead(true);
				}
			}
		}
	}
}

void CStage::BombExplode_FlyDuke()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		m_pFlyDuke->UpdateFlyDukeRect();
		if ((*it)->GetIsExplode() && m_pFlyDuke->GetVisible()
			&& IsHit((*it)->GetRect(), m_pFlyDuke->GetDukeRect())
			&& m_pFlyDuke->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
			&&(*it)->GetCurRow()==0)
		{
			m_pFlyDuke->SetHP(m_pFlyDuke->GetHP() - 2);
			m_bossHP -= 2;
			if (m_pFlyDuke->GetHP() <= 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(6, false);
				m_pFlyDuke->SetIsDead(true);
				m_ExplodeVisible = false;
			}
		}
	}
}

void CStage::BombExplode_Mask()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CMask*>::iterator iter = m_mask.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_mask.end(); iter++)
		{
			(*iter)->UpdateRc();
			if ((*it)->GetIsExplode() && (*iter)->GetVisible()
				&& IsHit((*it)->GetRect(), (*iter)->GetRc())
				&& (*iter)->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetHp((*iter)->GetHp() - 2);
				if ((*iter)->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter)->SetVisible(false);
				}
			}
		}
	}
}

void CStage::BombExplode_FlyMonster()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CFlyMonster*>::iterator iter = m_flyMonster.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_flyMonster.end(); iter++)
		{
			(*iter)->UpdateFlyMonsterRect();
			if ((*it)->GetIsExplode() && (*iter)->GetVisible()
				&& IsHit((*it)->GetRect(), (*iter)->GetFlyMonsterRect())
				&& (*iter)->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetHP((*iter)->GetHP() - 2);
				if ((*iter)->GetHP() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(5, false);
					(*iter)->SetVisible(false);
					vector<CBombExplode*>::iterator it1 = m_bombExplode.begin();
					for (; it1 != m_bombExplode.end(); it1++)
					{
						if (!(*it1)->GetIsExplode())
						{
							POINT pos;
							pos.x = (*iter)->GetPosX() - 90;
							pos.y = (*iter)->GetPosY() - 170;
							(*it1)->SetDesPos(pos);
							(*it1)->SetIsExplode(true);
							break;
						}
					}
				}
			}
		}
	}
}

void CStage::BombExplode_Fire()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CFire*>::iterator iter = m_fire.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_fire.end(); iter++)
		{
			(*iter)->UpdateFireRect();
			if ((*it)->GetIsExplode() && (*iter)->GetVisible()
				&& IsHit((*it)->GetRect(), (*iter)->GetFireRect())
				&& (*iter)->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetVisible(false);
			}
		}
	}
}

void CStage::BombExplode_Bob()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CBob*>::iterator iter = m_bob.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_bob.end(); iter++)
		{
			(*iter)->UpdateRect();
			if ((*it)->GetIsExplode() && (*iter)->GetVisible()
				&& (IsHit((*it)->GetRect(), (*iter)->GetBodyRect()) || IsHit((*it)->GetRect(), (*iter)->GetHeadRect()))
				&& (*iter)->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetHP((*iter)->GetHp() - 2);
				if ((*iter)->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(5, false);
					(*iter)->SetVisible(false);
				}
			}
		}
	}
}

void CStage::BombExplode_FeceMonster()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	vector<CFeceMonster*>::iterator iter = m_feceMonster.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		for (; iter != m_feceMonster.end(); iter++)
		{
			(*iter)->UpdateRc();
			if ((*it)->GetIsExplode() && (*iter)->GetVisible()
				&& IsHit((*it)->GetRect(), (*iter)->GetRc())
				&& (*iter)->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
				&&(*it)->GetCurRow()==0)
			{
				(*iter)->SetHp((*iter)->GetHp() - 2);
				if ((*iter)->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter)->SetVisible(false);
				}
			}
		}
	}
}

void CStage::BombExplode_Mother()
{
	vector<CBombExplode*>::iterator it = m_bombExplode.begin();
	for (; it != m_bombExplode.end(); it++)
	{
		(*it)->UpdateRect();
		if(m_pMatherHeart!=nullptr)
			m_pMatherHeart->UpdateMahterRc();
		if (m_pMatherHeart!=nullptr&&(*it)->GetIsExplode() && m_pMatherHeart->GetVisible()
			&& IsHit((*it)->GetRect(), m_pMatherHeart->GetMatherRc())
			&& m_pMatherHeart->GetMapIndex() == m_curMapIndex&&(*it)->GetCurFrame()==0
			&&(*it)->GetCurRow()==0)
		{
			m_pMatherHeart->SetHp(m_pMatherHeart->GetHp() - 2);
			m_bossHP -= 2;
			if (m_pMatherHeart->GetHp() <= 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(6, false);
				m_pMatherHeart->SetVisible(false);
				m_ExplodeVisible = false;
			}
		}
	}
}

void CStage::Bullet_MaskHeart()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			map<int, CMaskHeart*>::iterator it = m_maskHeart.begin();
			for (; it != m_maskHeart.end(); it++)
			{
				if (it->second->GetMapIndex() == m_curMapIndex && it->second->GetVisible())
				{
					it->second->UpdateMaskRc();
					if (IsHit((*iter)->GetBulletRect(), it->second->GetMaskRc()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							(*iter)->SetIsExplode(true);
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						break;
					}
				}
			}

			map<int, CMaskHeart*>::iterator it1 = m_HEART.begin();
			for (; it1 != m_HEART.end(); it1++)
			{
				if (it1->second->GetMapIndex() == m_curMapIndex && it1->second->GetVisible())
				{
					it1->second->UpdateHeartRc();
					if (IsHit((*iter)->GetBulletRect(), it1->second->GetHeartRc()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							it1->second->SetIsRed(true);
							it1->second->SetHp(it1->second->GetHp() - m_pBulletPool->GetDamage());
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}

						if (it1->second->GetHp() <= 0)
						{
							CAudio4Bass::GetInstance()->ChannelPlay(6, false);
							it1->second->SetVisible(false);
							m_maskHeart[it1->second->GetNum()]->SetVisible(false);
							vector<CMonsterDead*>::iterator iter2 = m_monsterDead.begin();
							for (; iter2 != m_monsterDead.end(); iter2++)
							{
								if ((*iter2)->GetIsDead() == false)
								{
									POINT pos;
									pos.x = it1->second->GetPos().x - 60;
									pos.y = it1->second->GetPos().y - 60;
									(*iter2)->SetPos(pos);
									(*iter2)->SetIsDead(true);
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
	}

	map<int, CMaskHeart*>::iterator it2 = m_HEART.begin();
	for (; it2 != m_HEART.end(); it2++)
	{
		if (it2->second->GetIsRed() == true)
		{
			m_addRedCount++;
			if (m_addRedCount == 5)
			{
				it2->second->SetIsRed(false);
				m_addRedCount = 0;
			}
		}
	}
}

void CStage::Bullet_Fly()
{
	vector<CBullet*>::iterator iter= m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			vector<CFly*>::iterator it = m_fly.begin();
			for (; it != m_fly.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateFlyRect();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetFlyRect()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							BackFly((*iter), *it);
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						break;
					}
				}
			}
		}
	}
}

void CStage::Bullet_Fire()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			vector<CFire*>::iterator it = m_fire.begin();
			for (; it != m_fire.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateFireRect();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetFireRect()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						(*it)->SetVisible(false);
						CAudio4Bass::GetInstance()->ChannelPlay(6, false);
						break;
					}
				}
			}
		}
	}
}

void CStage::Bullet_FlyMonster()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
			for (; it != m_flyMonster.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateFlyMonsterRect();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetFlyMonsterRect()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							(*it)->SetIsRed(true);
							(*it)->SetHP((*it)->GetHP() - m_pBulletPool->GetDamage());
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						if ((*it)->GetHP() <= 0)
						{	
							CAudio4Bass::GetInstance()->ChannelPlay(5, false);
							(*it)->SetVisible(false);
							vector<CBombExplode*>::iterator it1=m_bombExplode.begin();
							for(;it1!=m_bombExplode.end();it1++)
							{
								if(!(*it1)->GetIsExplode())
								{
									POINT pos;
									pos.x=(*it)->GetPosX()-90;
									pos.y=(*it)->GetPosY()-170;
									(*it1)->SetDesPos(pos);
									(*it1)->SetIsExplode(true);
									break;
								}
							}
						}

						break;
					}
				}
			}
		}
	}
	vector<CFlyMonster*>::iterator it1 = m_flyMonster.begin();
	for (; it1 != m_flyMonster.end(); it1++)
	{
		if ((*it1)->GetIsRed() == true)
		{
			m_addRedCount++;
			if (m_addRedCount == 5)
			{
				(*it1)->SetIsRed(false);
				m_addRedCount = 0;
			}
		}
	}
}

void CStage::Bullet_Bob()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();


			vector<CBob*>::iterator it = m_bob.begin();
			for (; it != m_bob.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateRect();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetHeadRect())||
						IsHit((*iter)->GetBulletRect(),(*it)->GetBodyRect()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							(*it)->SetHP((*it)->GetHp() - m_pBulletPool->GetDamage());
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						(*it)->SetIsRed(true);
						if((*it)->GetHp()<=0)
						{
							CAudio4Bass::GetInstance()->ChannelPlay(6, false);
							(*it)->SetVisible(false);
							vector<CMonsterDead*>::iterator iter2=m_monsterDead.begin();
							for(;iter2!=m_monsterDead.end();iter2++)
							{
								if((*iter2)->GetIsDead()==false)
								{
									POINT pos;
									pos.x=(*it)->GetPos().x-60;
									pos.y=(*it)->GetPos().y-60;
									(*iter2)->SetPos(pos);
									(*iter2)->SetIsDead(true);
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
	}

	vector<CBob*>::iterator it = m_bob.begin();
	for (; it != m_bob.end(); it++)
	{
		if ((*it)->GetIsRed())
		{
			m_addRedCount++;
			if (m_addRedCount == 5)
			{
				(*it)->SetIsRed(false);
				m_addRedCount = 0;
			}
		}}
}

void CStage::Bullet_Mask()
{
	vector<CBullet*>::iterator iter= m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			vector<CMask*>::iterator it = m_mask.begin();
			for (; it != m_mask.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateRc();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetRc()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							BackMask((*iter), (*it));
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						break;
					}
				}
			}
		}
	}
	vector<CMask*>::iterator it1 = m_mask.begin();
	for (; it1 != m_mask.end(); it1++)
	{
		if ((*it1)->GetIsRed() == true)
		{
			m_addRedCount++;
			if (m_addRedCount == 5)
			{
				(*it1)->SetIsRed(false);
				m_addRedCount = 0;
			}
		}
	}
}

void CStage::Bullet_FeceMonster()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode())
		{
			(*iter)->UpdateBulletRect();

			vector<CFeceMonster*>::iterator it = m_feceMonster.begin();
			for (; it != m_feceMonster.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateRc();
					if (IsHit((*iter)->GetBulletRect(), (*it)->GetRc()))
					{
						if (!m_pBulletPool->GetIsBomb())
						{
							CAudio4Bass::GetInstance()->ChannelPlay(10, false);
							(*iter)->SetIsExplode(true);
							(*it)->SetHp((*it)->GetHp() - m_pBulletPool->GetDamage());
						}
						else
						{
							(*iter)->SetVisible(false);
							BombExplode((*iter)->GetPos(), 60, 130);
						}
						(*it)->SetIsRed(true);
						if ((*it)->GetHp() <= 0)
						{
							CAudio4Bass::GetInstance()->ChannelPlay(6, false);
							(*it)->SetVisible(false);
							vector<CMonsterDead*>::iterator iter2 = m_monsterDead.begin();
							for (; iter2 != m_monsterDead.end(); iter2++)
							{
								if ((*iter2)->GetIsDead() == false)
								{
									POINT pos;
									pos.x = (*it)->GetPos().x - 60;
									pos.y = (*it)->GetPos().y - 60;
									(*iter2)->SetPos(pos);
									(*iter2)->SetIsDead(true);
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
	}
	vector<CFeceMonster*>::iterator it1 = m_feceMonster.begin();
	for (; it1 != m_feceMonster.end(); it1++)
	{
		if ((*it1)->GetIsRed() == true)
		{
			m_addRedCount++;
			if (m_addRedCount == 5)
			{
				(*it1)->SetIsRed(false);
				m_addRedCount = 0;
			}
		}
	}
}

void CStage::Bullet_FlyDuke()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() && !(*iter)->GetIsExplode() && m_curMapIndex == m_bossRoomNum&&!m_pFlyDuke->GetIsDead()
			&& m_pFlyDuke->GetVisible())
		{
			(*iter)->UpdateBulletRect();
			m_pFlyDuke->UpdateFlyDukeRect();
			if (IsHit(m_pFlyDuke->GetDukeRect(), (*iter)->GetBulletRect()))
			{
				if (IsFlyDuke_Bullet_Collision(m_pFlyDuke->GetDukeRect(), (*iter)->GetBulletRect()))
				{
					if (!m_pBulletPool->GetIsBomb())
					{
						CAudio4Bass::GetInstance()->ChannelPlay(10, false);
						(*iter)->SetIsExplode(true);
						m_pFlyDuke->SetHP(m_pFlyDuke->GetHP() - m_pBulletPool->GetDamage());
						m_bossHP -= m_pBulletPool->GetDamage();
					}
					else
					{
						(*iter)->SetVisible(false);
						BombExplode((*iter)->GetPos(), 60, 130);
					}
					m_pFlyDuke->SetIsRed(true);
					if (m_pFlyDuke->GetHP() <= 0)
					{
						CAudio4Bass::GetInstance()->ChannelPlay(6, false);
						m_pFlyDuke->SetIsDead(true);
						m_ExplodeVisible = false;
					}
				}
			}
		}
	}
	if (m_pFlyDuke->GetIsRed() == true)
	{
		m_addRedCount++;
		if (m_addRedCount == 5)
		{
			m_pFlyDuke->SetIsRed(false);
			m_addRedCount = 0;
		}
	}
	m_pFlyDuke->Dead();
	if (!m_pFlyDuke->GetVisible() && !m_down&&!m_up&&!m_right&&!m_left)
		m_ExplodeVisible = true;
}

void CStage::Bullet_MatherHeart()
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if (m_pMatherHeart!=nullptr&&(*iter)->GetVisible() && !(*iter)->GetIsExplode() && m_curMapIndex == m_bossRoomNum&&m_pMatherHeart->GetVisible())
		{
			(*iter)->UpdateBulletRect();
			m_pMatherHeart->UpdateMahterRc();
			if (IsHit(m_pMatherHeart->GetMatherRc(), (*iter)->GetBulletRect()))
			{
				if (!m_pBulletPool->GetIsBomb())
				{
					CAudio4Bass::GetInstance()->ChannelPlay(10, false);
					(*iter)->SetIsExplode(true);
					m_pMatherHeart->SetHp(m_pMatherHeart->GetHp() - m_pBulletPool->GetDamage());
					m_bossHP -= m_pBulletPool->GetDamage();
				}
				else
				{
					(*iter)->SetVisible(false);
					BombExplode((*iter)->GetPos(), 60, 130);
				}
				m_pMatherHeart->SetIsRed(true);
				if (m_pMatherHeart->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					m_pMatherHeart->SetVisible(false);
					m_ExplodeVisible = false;
				}
			}
		}
	}
	if (m_pMatherHeart!=nullptr&&m_pMatherHeart->GetIsRed() == true)
	{
		m_addRedCount++;
		if (m_addRedCount == 5)
		{
			m_pMatherHeart->SetIsRed(false);
			m_addRedCount = 0;
		}
	}
}

void CStage::GoldenBox_Player()
{
	m_pPlayerBody->UpdateBodyRect();
	m_pPlayerHead->UpdateHeadRect();
	m_pEnd->UpdateRc();
	if ((IsHit(m_pPlayerBody->GetBodyRect(), m_pEnd->GetRc()) ||
		IsHit(m_pPlayerHead->GetHeadRect(), m_pEnd->GetRc())) && m_pEnd->GetVisibleOnMap()&&m_pEnd->GetVisible()
		&&m_pEnd->GetCurFrame()==0&&m_pEnd->GetMapIndex()==m_curMapIndex)
	{
		m_pEnd->End();
	}
}

void CStage::Bullet_Player()
{
	if (m_pPathBullet != nullptr)
	{
		vector<CBullet*>::iterator iter = m_pPathBullet->GetBulletPoolBegin();
		vector<CBullet*>::iterator iter1 = m_pPathBullet->GetBulletPoolEnd();
		for (; iter != iter1; iter++)
		{
			if ((*iter)->GetVisible() && !(*iter)->GetIsExplode() && m_curMapIndex == m_bossRoomNum&&m_pMatherHeart->GetVisible())
			{
				(*iter)->UpdateBigRc();
				m_pPlayerBody->UpdateBodyRect();
				m_pPlayerHead->UpdateHeadRect();
				if ((IsHit(m_pPlayerBody->GetBodyRect(), (*iter)->GetBulletRect()) ||
					IsHit(m_pPlayerHead->GetHeadRect(), (*iter)->GetBulletRect())) && !m_isInvincible)
				{
					POINT pos;
					pos.x = (*iter)->GetPos().x + 65;
					pos.y = (*iter)->GetPos().y + 60;
					PlayerBeHurted(pos);
					if (m_pPlayerHead->GetHp() > 0)
						m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - m_pBulletPool->GetDamage());
					if (m_pPlayerHead->GetHp() <= 0)
						m_pEnd->End();
					if (!m_pEnd->GetIsdead())
					CAudio4Bass::GetInstance()->ChannelPlay(3, true);
					break;
				}
			}
		}
	}
}

void CStage::FeceMonster_Player()
{
	vector<CFeceMonster*>::iterator it = m_feceMonster.begin();
	for (; it != m_feceMonster.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
		{
			(*it)->UpdateRc();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRc()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetRc())) && !m_isInvincible)
			{
				POINT pos;
				pos.x = (*it)->GetPos().x;
				pos.y = (*it)->GetPos().y;
				PlayerBeHurted(pos);
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::Mask_Player()
{
	vector<CMask*>::iterator it = m_mask.begin();
	for (; it != m_mask.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
		{
			(*it)->UpdateRc();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRc())||
				IsHit(	m_pPlayerHead->GetHeadRect(), (*it)->GetRc()))&&!m_isInvincible)
			{
				POINT pos;
				pos.x = (*it)->GetPos().x + 10;
				pos.y = (*it)->GetPos().y + 10;
				PlayerBeHurted(pos);
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::Fire_Player()
{
	vector<CFire*>::iterator it = m_fire.begin();
	for (; it != m_fire.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible() && (*it)->GetVisibleOnMap())
		{
			(*it)->UpdateFireRect();
			m_pPlayerBody->UpdateBodyRect();
			if (IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetFireRect())&&!m_isInvincible)
			{
				POINT pos;
				pos.x = (*it)->GetPos().x + 10;
				pos.y = (*it)->GetPos().y + 10;
				PlayerBeHurted(pos);
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::Fire_Fly()
{
	vector<CFire*>::iterator iter = m_fire.begin();
	for (; iter != m_fire.end(); iter++)
	{
		if ((*iter)->GetVisible() && (*iter)->GetMapIndex() == m_curMapIndex)
		{
			(*iter)->UpdateFireRect();

			vector<CFly*>::iterator it = m_fly.begin();
			for (; it != m_fly.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
				{
					(*it)->UpdateFlyRect();
					if (IsHit((*iter)->GetFireRect(), (*it)->GetFlyRect()))
					{
						(*it)->SetIsDead(true); 
						(*it)->SetHP(0);
						CAudio4Bass::GetInstance()->ChannelPlay(6, false);
						break;
					}
				}
			}
		}
	}
}

void CStage::Money_Player()
{
	vector<CMoney*>::iterator it = m_money.begin();
	for (; it != m_money.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible()&&(*it)->GetVisibleOnMap()&&(*it)->GetVisiblePlayer())
		{
			(*it)->UpdateRc();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRc()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetRc())))
			{
				CAudio4Bass::GetInstance()->ChannelPlay(12, true);
				(*it)->SetVisiblePlayer(false);
				(*it)->SetCurFrame(0);
				m_moneyCount++;
				break;
			}
		}
	}
}

void CStage::MaskHeart_Player()
{
	map<int, CMaskHeart*>::iterator it = m_maskHeart.begin();
	for (; it != m_maskHeart.end(); it++)
	{
		if (it->second->GetMapIndex() == m_curMapIndex && it->second->GetVisible())
		{
			it->second->UpdateMaskRc();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), it->second->GetMaskRc()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), it->second->GetMaskRc())) && !m_isInvincible)
			{
				PlayerBeHurted(it->second->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - it->second->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}

	map<int, CMaskHeart*>::iterator it1 = m_HEART.begin();
	for (; it1 != m_HEART.end(); it1++)
	{
		if (it1->second->GetMapIndex() == m_curMapIndex && it1->second->GetVisible())
		{
			it1->second->UpdateHeartRc();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), it1->second->GetHeartRc()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), it1->second->GetHeartRc())) && !m_isInvincible)
			{
				PlayerBeHurted(it1->second->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - it1->second->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				break;
			}
		}
	}
}

void CStage::Fly_Player()
{
	vector<CFly*>::iterator it = m_fly.begin();
	for (; it != m_fly.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
		{
			(*it)->UpdateFlyRect();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetFlyRect())||
				IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetFlyRect()))&&!m_isInvincible)
			{
				PlayerBeHurted((*it)->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::FlyDuke_Player()
{
	if (m_curMapIndex==m_bossRoomNum&&!m_pFlyDuke->GetIsDead()&&m_pFlyDuke->GetVisible())
	{
		m_pPlayerHead->UpdateHeadCollision();
		m_pPlayerBody->UpdateBodyCollision();
		m_pFlyDuke->UpdateFlyDukeRect();
		if (IsHit(m_pFlyDuke->GetDukeRect(),m_pPlayerBody->GetBodyCollision())&&!m_isInvincible)
		{
			if (IsFlyDuke_PlayerBody_Collision(m_pFlyDuke->GetDukeRect(),m_pPlayerBody->GetBodyCollision())&&!m_isInvincible)
			{
				PlayerBeHurted(m_pFlyDuke->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - m_pFlyDuke->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
			}
		}

		if (IsHit(m_pFlyDuke->GetDukeRect(), m_pPlayerHead->GetHeadCollision()))
		{
			if (IsFlyDuke_PlayerHead_Collision(m_pFlyDuke->GetDukeRect(), m_pPlayerHead->GetHeadCollision())&&!m_isInvincible)
			{
				PlayerBeHurted(m_pFlyDuke->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - m_pFlyDuke->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
			}
		}
	}
}

void CStage::FlyMonster_Player()
{
	vector<CFlyMonster*>::iterator it = m_flyMonster.begin();
	for (; it != m_flyMonster.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex && (*it)->GetVisible())
		{
			(*it)->UpdateFlyMonsterRect();
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetFlyMonsterRect()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetFlyMonsterRect())) && !m_isInvincible)
			{
				POINT pos;
				pos.x = (*it)->GetPosX();
				pos.y = (*it)->GetPosY();
				PlayerBeHurted(pos);
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::BombExplode_Player()
{
	vector<CBombExplode*>::iterator it=m_bombExplode.begin();
	for(;it!=m_bombExplode.end();it++)
	{
		(*it)->UpdateRect();
		if((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRect())||
			IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetRect()))&&(*it)->GetIsExplode()
			&& !m_isInvincible)
		{
			POINT pos=(*it)->GetPos();
			pos.x +=92;
			pos.y +=176;
			PlayerBeHurted(pos);
			if (m_pPlayerHead->GetHp() > 0)
				m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
			if (m_pPlayerHead->GetHp() <= 0)
				m_pEnd->End();
			if (!m_pEnd->GetIsdead())
			CAudio4Bass::GetInstance()->ChannelPlay(3, true);
			break;
		}
	}
}

void CStage::Bob_Player()
{
	vector<CBob*>::iterator it=m_bob.begin();
	for(;it!=m_bob.end();it++)
	{
		(*it)->UpdateRect();

		if ((*it)->GetVisible() && (*it)->GetMapIndex() == m_curMapIndex)
		{
			m_pPlayerBody->UpdateBodyRect();
			m_pPlayerHead->UpdateHeadRect();
			if ((IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetHeadRect()) ||
				IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetHeadRect())
				|| IsHit(m_pPlayerHead->GetHeadRect(), (*it)->GetBodyRect())
				|| IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetBodyRect())) && !m_isInvincible)
			{
				PlayerBeHurted((*it)->GetPos());
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::Goods_Player()
{
	POINT pos;
	pos = m_pPlayerHead->GetPlayerPos();
	vector<CGoods*>::iterator it = m_goods.begin();
	m_pPlayerBody->UpdateBodyRect();
	it++;
	for (; it != m_goods.end(); it++)
	{
		(*it)->UpdateRc();
		if (IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRc()) && (*it)->GetMapIndex() == m_curMapIndex 
			&& (*it)->GetVisibleOnMap()&&(*it)->GetVisible())
		{
			if (it != m_goods.end()-1)
			{
				(*it)->SetIsUse(true);
				CAudio4Bass::GetInstance()->ChannelPlay(13, true);
				m_pPlayerBody->SetVisible(false);
				m_pPlayerHead->SetVisible(false);
				m_pPlayerHead->SetIsHold(true);
			}
			else if (it == m_goods.end() - 1&&m_moneyCount>=2)
			{
				(*it)->SetIsUse(true);
				CAudio4Bass::GetInstance()->ChannelPlay(13, true);
				m_pPlayerBody->SetVisible(false);
				m_pPlayerHead->SetVisible(false);
				m_pPlayerHead->SetIsHold(true);
				m_moneyCount -= 2;
			}
		}
	}
}

void CStage::Tile_Player()
{
	vector<CTile*>::iterator it = m_tile.begin();
	for (; it != m_tile.end(); it++)
	{
		if ((*it)->GetMapIndex() == m_curMapIndex&&(*it)->GetVisible())
		{
			(*it)->UpdateTileRect();
			m_pPlayerBody->UpdateBodyRect();
			if (IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetTileRect())&&!m_isInvincible)
			{
				POINT pos;
				pos.x=(*it)->GetPos().x+26;
				pos.y=(*it)->GetPos().y+18;
				PlayerBeHurted(pos);
				if (m_pPlayerHead->GetHp() > 0)
					m_pPlayerHead->SetHp(m_pPlayerHead->GetHp() - (*it)->GetDamage());
				if (m_pPlayerHead->GetHp() <= 0)
					m_pEnd->End();
				if (!m_pEnd->GetIsdead())
				CAudio4Bass::GetInstance()->ChannelPlay(3, true);
				break;
			}
		}
	}
}

void CStage::BackFly(CBullet*bullet,CFly*fly)
{
	POINT pos=fly->GetPos();
	fly->SetHP(fly->GetHP()-m_pBulletPool->GetDamage());
	if (fly->GetHP() <= 0)
	{
		CAudio4Bass::GetInstance()->ChannelPlay(6, false);
		fly->SetIsDead(true);
	}
	if(bullet->GetDir()==eUP)
		pos.y-=30;
	else if(bullet->GetDir()==eDOWN)
		pos.y+=30;
	else if(bullet->GetDir()==eLEFT)
		pos.x-=30;
	else if(bullet->GetDir()==eRIGHT)
		pos.x+=30;
	fly->SetPos(pos);
}

void CStage::BackMask(CBullet*bullet,CMask*mask)
{
	POINT pos=mask->GetPos();
	if(bullet->GetDir()==eUP)
	{
		if(pos.y-30>110)
			pos.y-=30;
		if(mask->GetDir()==eUP)
		{
			mask->SetHp(mask->GetHp()-m_pBulletPool->GetDamage());
			mask->SetIsRed(true);
		}
	}
	else if(bullet->GetDir()==eDOWN)
	{
		if(pos.y+30<450)
			pos.y+=30;
		if(mask->GetDir()==eDOWN)
		{
			mask->SetHp(mask->GetHp()-m_pBulletPool->GetDamage());
			mask->SetIsRed(true);
		}
	}
	else if(bullet->GetDir()==eLEFT)
	{
		if(pos.x-30>96)
			pos.x-=30;
		if(mask->GetDir()==eLEFT)
		{
			mask->SetHp(mask->GetHp()-m_pBulletPool->GetDamage());
			mask->SetIsRed(true);
		}
	}
	else if(bullet->GetDir()==eRIGHT)
	{
		if(pos.x+30<710)
			pos.x+=30;
		if(mask->GetDir()==eRIGHT)
		{
			mask->SetHp(mask->GetHp()-m_pBulletPool->GetDamage());
			mask->SetIsRed(true);
		}
	}
	mask->SetPos(pos);

	if (mask->GetHp() <= 0)
	{
		CAudio4Bass::GetInstance()->ChannelPlay(6, false);
		mask->SetVisible(false);
		vector<CMonsterDead*>::iterator iter2=m_monsterDead.begin();
		for(;iter2!=m_monsterDead.end();iter2++)
		{
			if((*iter2)->GetIsDead()==false)
			{
				POINT pos;
				pos.x=mask->GetPos().x-60;
				pos.y=mask->GetPos().y-60;
				(*iter2)->SetPos(pos);
				(*iter2)->SetIsDead(true);
				break;
			}
		}
	}
}

void CStage::InitCollision()
{
	int width;
	int height;
	POINT	pos;

	width = 88;
	height = 88;
	m_pPPixelBullet = new DWORD[width*height];
	for(int i = 0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			pos.x = j;
			pos.y = i;
			m_pPPixelBullet[i*width+j] = m_pBulletPool->GetColorValue(pos);
		}
	}


	width = m_pFlyDuke->GetPicWidth();
	height = m_pFlyDuke->GetPicHeight();
	m_pPPixelBoss = new DWORD[width*height];
	for(int i = 0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			pos.x = j;
			pos.y = i;
			m_pPPixelBoss[i*width+j]= m_pFlyDuke->GetColorValue(pos);
		}
	}

    width = m_pPlayerBody->GetPicWidth();
	height = m_pPlayerBody->GetPicHeight();
	m_pPPixelBody = new DWORD[width*height];
	for(int i = 0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			pos.x = j;
			pos.y = i;
			m_pPPixelBody[i*width+j]= m_pPlayerBody->GetColorValue(pos);
		}
	}

	width = m_pPlayerHead->GetPicWidth();
	height = m_pPlayerHead->GetPicHeight();
	m_pPPixelHead = new DWORD[width*height];
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			pos.x = j;
			pos.y = i;
			m_pPPixelHead[i*width + j] = m_pPlayerHead->GetColorValue(pos);
		}
	}
}

void CStage::StartSurfaceMove()
{
	POINT pos;
	if (m_isStart)
	{
		if (m_startSurface[6]->GetDesPos().x < 40)
		{
			pos.x=m_startSurface[1]->GetDesPos().x + m_mapSpeed;
			pos.y = m_startSurface[1]->GetDesPos().y;
			m_startSurface[1]->SetDesPos(pos);

			pos.x = m_startSurface[4]->GetDesPos().x + m_mapSpeed;
			pos.y = m_startSurface[4]->GetDesPos().y;
			m_startSurface[4]->SetDesPos(pos);

			pos.x = m_startSurface[2]->GetDesPos().x - m_mapSpeed;
			pos.y = m_startSurface[2]->GetDesPos().y;
			m_startSurface[2]->SetDesPos(pos);

			pos.x = m_startSurface[3]->GetDesPos().x - m_mapSpeed;
			pos.y = m_startSurface[3]->GetDesPos().y;
			m_startSurface[3]->SetDesPos(pos);

			pos.x = m_startSurface[5]->GetDesPos().x - m_mapSpeed;
			pos.y = m_startSurface[5]->GetDesPos().y;
			m_startSurface[5]->SetDesPos(pos);

			pos.x = m_startSurface[6]->GetDesPos().x + m_mapSpeed;
			pos.y = m_startSurface[6]->GetDesPos().y;
			m_startSurface[6]->SetDesPos(pos);

			m_startSurface[7]->SetCenter(m_startSurface[7]->GetWidth() / 2, m_startSurface[7]->GetHeight() / 2);
			m_startSurface[7]->SetMove(380, 110);
		}
		if (m_startSurface[6]->GetDesPos().x == 40)
		{
			m_startSurface[7]->SetTransparent(0xff000000);
			if (m_VSScale > 1)
			{
				static DWORD preTime = GetTickCount();
				DWORD curTime = GetTickCount();
				if (curTime - preTime > 10)
				{
					preTime = curTime;
					m_VSScale -= 0.1f;
				}
				m_angle -= m_angle1;
				m_angle1 += 0.018;
			}
			m_startSurface[7]->SetAngle(m_angle);
			m_startSurface[7]->SetScale(m_VSScale, m_VSScale);

			if (m_VSScale <= 1.0)
			{
				if (m_startReturnCount == 0)
				{
					static DWORD preTime = GetTickCount();
					DWORD curTime = GetTickCount();
					if (curTime - preTime > 2000)
					{
						preTime = curTime;
						m_startReturnCount++;
					}
				}

				if (m_startReturnCount == 1)
				{
					pos.x = m_startSurface[1]->GetDesPos().x - m_mapSpeed;
					pos.y = m_startSurface[1]->GetDesPos().y;
					m_startSurface[1]->SetDesPos(pos);

					pos.x = m_startSurface[4]->GetDesPos().x - m_mapSpeed;
					pos.y = m_startSurface[4]->GetDesPos().y;
					m_startSurface[4]->SetDesPos(pos);

					pos.x = m_startSurface[2]->GetDesPos().x + m_mapSpeed;
					pos.y = m_startSurface[2]->GetDesPos().y;
					m_startSurface[2]->SetDesPos(pos);

					pos.x = m_startSurface[3]->GetDesPos().x + m_mapSpeed;
					pos.y = m_startSurface[3]->GetDesPos().y;
					m_startSurface[3]->SetDesPos(pos);
				}

				if (pos.x = m_startSurface[1]->GetDesPos().x<=-960)
				  m_isStart = false;
			}
		}
	}
}

void CStage::PlayerBeHurted(POINT enemyPos)
{
	m_pPlayerHead->SetVisible(false);
	m_pPlayerBody->SetVisible(false);

	POINT pos1=m_pPlayerBody->GetPlayerPos();
	POINT pos;
	pos.x=pos1.x-enemyPos.x;
	pos.y=pos1.y-enemyPos.y;

	if(pos.x>0&&m_pPlayerBody->GetBodyRect().right+20<=739)
	{
		pos1=m_pPlayerBody->GetPlayerPos();
		pos1.x=m_pPlayerBody->GetPlayerPos().x+20;
		m_pPlayerBody->SetPos(pos1);
		pos1=m_pPlayerHead->GetPlayerPos();
		pos1.x=m_pPlayerHead->GetPlayerPos().x+20;
		m_pPlayerHead->SetPos(pos1);
	}
	else if(pos.x<0&&m_pPlayerBody->GetBodyRect().left-20>=96)
	{
		pos1=m_pPlayerBody->GetPlayerPos();
		pos1.x=m_pPlayerBody->GetPlayerPos().x-20;
		m_pPlayerBody->SetPos(pos1);
		pos1=m_pPlayerHead->GetPlayerPos();
		pos1.x=m_pPlayerHead->GetPlayerPos().x-20;
		m_pPlayerHead->SetPos(pos1);
	}

	if(pos.y>0&&m_pPlayerBody->GetBodyRect().bottom+20<=480)
	{
		pos1=m_pPlayerBody->GetPlayerPos();
		pos1.y=m_pPlayerBody->GetPlayerPos().y+20;
		m_pPlayerBody->SetPos(pos1);
		pos1=m_pPlayerHead->GetPlayerPos();
		pos1.y=m_pPlayerHead->GetPlayerPos().y+20;
		m_pPlayerHead->SetPos(pos1);
	}
	else if(pos.y<0&&m_pPlayerBody->GetBodyRect().top-20>=96)
	{
		pos1=m_pPlayerBody->GetPlayerPos();
		pos1.y=m_pPlayerBody->GetPlayerPos().y-20;
		m_pPlayerBody->SetPos(pos1);
		pos1=m_pPlayerHead->GetPlayerPos();
		pos1.y=m_pPlayerHead->GetPlayerPos().y-20;
		m_pPlayerHead->SetPos(pos1);
	}

	m_isInvincible=true;
}

void CStage::Recover()
{
	if (!m_pPlayerHead->GetVisible())
	{
		m_addRedCount++;
		if (!m_pPlayerHead->GetIsHold())
		{
			if (m_addRedCount >= 5)
			{
				m_pPlayerHead->SetVisible(true);
				m_pPlayerBody->SetVisible(true);
				m_addRedCount = 0;
			}
		}
		else if (m_pPlayerHead->GetIsHold())
		{
			if (m_addRedCount >= 20)
			{
				m_pPlayerHead->SetVisible(true);
				m_pPlayerBody->SetVisible(true);
				m_pPlayerHead->SetIsHold(false);
				m_addRedCount = 0;

				vector<CGoods*>::iterator it = m_goods.begin();
				m_pPlayerBody->UpdateBodyRect();
				it++;
				for (; it != m_goods.end(); it++)
				{
					(*it)->UpdateRc();
					if (IsHit(m_pPlayerBody->GetBodyRect(), (*it)->GetRc()))
					{
						(*it)->SetVisible(false);
					}
				}
			}
		}
		if(!m_pPlayerBody->GetIsRun())
			m_pPlayerBody->SetVisible(false);
	}
}

void CStage::IsShoot(Map*pMap, int tileWidth, int num, int change)
{
	vector<CBullet*>::iterator iter = m_pBulletPool->GetBulletPoolBegin();
	vector<CBullet*>::iterator iter1 = m_pBulletPool->GetBulletPoolEnd();
	for (; iter != iter1; iter++)
	{
		if ((*iter)->GetVisible() &&pMap->GetMapIndex()==m_curMapIndex)
		{
			(*iter)->UpdateBulletRect();
			for (int i = (*iter)->GetBulletRect().left; i <= (*iter)->GetBulletRect().right; i++)
			{
				for(int j=(*iter)->GetBulletRect().top;j<=(*iter)->GetBulletRect().bottom;j++)
				{
					int x = (j + pMap->GetSrcPos().y) / tileWidth;
					int y = (i + pMap->GetSrcPos().x) / tileWidth;
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

void CStage::ShotFeces(Map*pStone)
{
	IsShoot(pStone, 64, 23, 24);
	IsShoot(pStone, 64, 22, 23);
	IsShoot(pStone, 64, 20, 22);
	IsShoot(pStone, 64, 19, 20);
}

void CStage::UseGoods()
{
	vector<CGoods*>::iterator it = m_goods.begin();
	it++;
	for (; it != m_goods.end(); it++)
	{
		if ((*it)->GetIsUse())
			(*it)->Function();
	}
}

void CStage::BombExplode(POINT m_pos,int x,int y)
{
	vector<CBombExplode*>::iterator it=m_bombExplode.begin();
	for(;it!=m_bombExplode.end();it++)
	{
		if(!(*it)->GetIsExplode())
		{
			POINT pos;
			pos.x=m_pos.x-x;
			pos.y=m_pos.y-y;
			(*it)->SetDesPos(pos);
			(*it)->SetIsExplode(true);
			CAudio4Bass::GetInstance()->ChannelPlay(5, false);
			break;
		}
	}
}

void CStage::MatherHeartAttack()
{
	if(m_pMatherHeart!=nullptr&&m_pMatherHeart->GetMapIndex()==m_curMapIndex&&m_pMatherHeart->GetVisible())
	{
		UpdateEnemyBullet();
	}
}

void CStage::MatherHeartFireBob()
{
	if (m_pMatherHeart != nullptr&&m_pMatherHeart->GetVisible() && m_pMatherHeart->GetMapIndex() == m_curMapIndex)
	{
		static DWORD preTime = GetTickCount();
		DWORD curTime = GetTickCount();
		if (curTime - preTime > 5000)
		{
			preTime = curTime;
			vector<CBob*>::iterator it = m_bob.begin();
			for (; it != m_bob.end(); it++)
			{
				if ((*it)->GetMapIndex() == m_curMapIndex&&!(*it)->GetVisible())
				{
					POINT pos = {370,140};
					(*it)->SetPos(pos);
					(*it)->UpdateRect();
					(*it)->SetVisible(true);
				}
			}
		}
	}
}

void CStage::LegAttack()
{
	vector<CFly*>::iterator iter1= m_fly.begin();
	for (; iter1 != m_fly.end(); iter1++)
	{
		if((*iter1)->GetMapIndex()==m_curMapIndex&&(*iter1)->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos=(*iter1)->GetPos();
			pos.x+=30;
			pos.y+=30;
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	vector<CBob*>::iterator iter2= m_bob.begin();
	for (; iter2 != m_bob.end(); iter2++)
	{
		if((*iter2)->GetMapIndex()==m_curMapIndex&&(*iter2)->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos=(*iter2)->GetPos();
			pos.x+=30;
			pos.y+=30;
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	vector<CFlyMonster*>::iterator iter3= m_flyMonster.begin();
	for (; iter3 != m_flyMonster.end(); iter3++)
	{
		if((*iter3)->GetMapIndex()==m_curMapIndex&&(*iter3)->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos;
			pos.x=(*iter3)->GetPosX();
			pos.y=(*iter3)->GetPosY();
			pos.x+=30;
			pos.y+=30;
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	if(m_pFlyDuke!=nullptr&&m_pFlyDuke->GetMapIndex()==m_curMapIndex&&m_pFlyDuke->GetVisible()&&m_pLeg->GetLegVisible()
		&&!m_pLeg->GetIsMove())
	{
		POINT pos;
		pos.x=m_pFlyDuke->GetPosX();
		pos.y=m_pFlyDuke->GetPosY();
		pos.x+=30;
		pos.y+=60;
		m_pLeg->SetAimPos(pos);
		m_pLeg->SetIsMove(true);
		return;
	}

	vector<CMask*>::iterator iter4= m_mask.begin();
	for (; iter4 != m_mask.end(); iter4++)
	{
		if((*iter4)->GetMapIndex()==m_curMapIndex&&(*iter4)->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos=(*iter4)->GetPos();
			pos.x+=30;
			pos.y+=30;
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	vector<CFeceMonster*>::iterator iter5= m_feceMonster.begin();
	for (; iter5 != m_feceMonster.end(); iter5++)
	{
		if((*iter5)->GetMapIndex()==m_curMapIndex&&(*iter5)->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos=(*iter5)->GetPos();
			pos.y+=10;
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	map<int,CMaskHeart*>::iterator iter6=m_HEART.begin();
	for(;iter6!=m_HEART.end();iter6++)
	{
		if((iter6)->second->GetMapIndex()==m_curMapIndex&&(iter6)->second->GetVisible()&&m_pLeg->GetLegVisible()
			&&!m_pLeg->GetIsMove())
		{
			POINT pos=(iter6)->second->GetPos();
			m_pLeg->SetAimPos(pos);
			m_pLeg->SetIsMove(true);
			return;
		}
	}

	if(m_pMatherHeart!=nullptr&&m_pMatherHeart->GetMapIndex()==m_curMapIndex&&m_pMatherHeart->GetVisible()&&m_pLeg->GetLegVisible()
		&&!m_pLeg->GetIsMove())
	{
		POINT pos;
		pos=m_pMatherHeart->GetPos();
		pos.x+=60;
		pos.y+=120;
		m_pLeg->SetAimPos(pos);
		m_pLeg->SetIsMove(true);
		return;
	}
}

void CStage::Leg_Fly()
{
	vector<CFly*>::iterator iter1= m_fly.begin();
	for (; iter1 != m_fly.end(); iter1++)
	{
		if((*iter1)->GetMapIndex()==m_curMapIndex&&(*iter1)->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			(*iter1)->UpdateFlyRect();
			m_pLeg->UpdateLegRc();
			if(IsHit(m_pLeg->GetLegRc(),(*iter1)->GetFlyRect()))
			{
				(*iter1)->SetHP((*iter1)->GetHP()-m_pLeg->GetDamage());
				if ((*iter1)->GetHP() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter1)->SetIsDead(true);
				}
			}
			break;
		}
	}
}

void CStage::Leg_Bob()
{
	vector<CBob*>::iterator iter2= m_bob.begin();
	for (; iter2 != m_bob.end(); iter2++)
	{
		if((*iter2)->GetMapIndex()==m_curMapIndex&&(*iter2)->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			(*iter2)->UpdateRect();
			m_pLeg->UpdateLegRc();
			if(IsHit(m_pLeg->GetLegRc(),(*iter2)->GetBodyRect())||IsHit(m_pLeg->GetLegRc(),(*iter2)->GetHeadRect()))
			{
				(*iter2)->SetHP((*iter2)->GetHp()-m_pLeg->GetDamage());
				if ((*iter2)->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter2)->SetVisible(false);
				}
			}
			break;
		}
	}
}

void CStage::Leg_FlyMonster()
{
	vector<CFlyMonster*>::iterator iter2= m_flyMonster.begin();
	for (; iter2 != m_flyMonster.end(); iter2++)
	{
		if((*iter2)->GetMapIndex()==m_curMapIndex&&(*iter2)->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			(*iter2)->UpdateFlyMonsterRect();
			m_pLeg->UpdateLegRc();
			if(IsHit(m_pLeg->GetLegRc(),(*iter2)->GetFlyMonsterRect()))
			{
				(*iter2)->SetHP((*iter2)->GetHP()-m_pLeg->GetDamage());
				if ((*iter2)->GetHP() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(5, false);
					(*iter2)->SetVisible(false);
					vector<CBombExplode*>::iterator it1=m_bombExplode.begin();
					for(;it1!=m_bombExplode.end();it1++)
					{
						if(!(*it1)->GetIsExplode())
						{
							POINT pos;
							pos.x=(*iter2)->GetPosX()-90;
							pos.y=(*iter2)->GetPosY()-170;
							(*it1)->SetDesPos(pos);
							(*it1)->SetIsExplode(true);
							break;
						}
					}
				}
			}
			break;
		}
	}
}

void CStage::Leg_FlyDuke()
{
	if(m_pFlyDuke!=nullptr&&m_pFlyDuke->GetMapIndex()==m_curMapIndex&&m_pFlyDuke->GetVisible()&&m_pLeg->GetLegVisible()
		&&m_pLeg->GetIsMove())
	{
		m_pLeg->UpdateLegRc();
		m_pFlyDuke->UpdateDuke();
		if(IsHit(m_pLeg->GetLegRc(),m_pFlyDuke->GetDukeRect()))
		{
			m_pFlyDuke->SetHP(m_pFlyDuke->GetHP()-m_pLeg->GetDamage());
			m_bossHP-=m_pLeg->GetDamage();
			if(m_pFlyDuke->GetHP()<=0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(6, false);
				m_pFlyDuke->SetIsDead(true);
				m_ExplodeVisible = false;
			}
		}
	}
}

void CStage::Leg_Mask()
{
	vector<CMask*>::iterator iter4= m_mask.begin();
	for (; iter4 != m_mask.end(); iter4++)
	{
		if((*iter4)->GetMapIndex()==m_curMapIndex&&(*iter4)->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			m_pLeg->UpdateLegRc();
			(*iter4)->UpdateRc();
			if(IsHit((*iter4)->GetRc(),m_pLeg->GetLegRc()))
			{
				(*iter4)->SetHp((*iter4)->GetHp()-m_pLeg->GetDamage());
				if((*iter4)->GetHp()<=0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter4)->SetVisible(false);
				}
					break;
			}
		}
	}
}

void CStage::Leg_FeceMonster()
{
	vector<CFeceMonster*>::iterator iter2= m_feceMonster.begin();
	for (; iter2 != m_feceMonster.end(); iter2++)
	{
		if((*iter2)->GetMapIndex()==m_curMapIndex&&(*iter2)->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			(*iter2)->UpdateRc();
			m_pLeg->UpdateLegRc();
			if(IsHit(m_pLeg->GetLegRc(),(*iter2)->GetRc()))
			{
				(*iter2)->SetHp((*iter2)->GetHp()-m_pLeg->GetDamage());
				if ((*iter2)->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(*iter2)->SetVisible(false);
				}
			}
			break;
		}
	}
}

void CStage::Leg_MaskHeart()
{
	map<int,CMaskHeart*>::iterator iter6=m_HEART.begin();
	for(;iter6!=m_HEART.end();iter6++)
	{
		if((iter6)->second->GetMapIndex()==m_curMapIndex&&(iter6)->second->GetVisible()&&m_pLeg->GetLegVisible()
			&&m_pLeg->GetIsMove())
		{
			iter6->second->UpdateHeartRc();
			m_pLeg->UpdateLegRc();
			if(IsHit(iter6->second->GetHeartRc(),m_pLeg->GetLegRc()))
			{
				(iter6)->second->SetHp((iter6)->second->GetHp()-m_pLeg->GetDamage());
				if ((iter6)->second->GetHp() <= 0)
				{
					CAudio4Bass::GetInstance()->ChannelPlay(6, false);
					(iter6)->second->SetVisible(false);
					m_maskHeart[iter6->second->GetNum()]->SetVisible(false);
				}
			}
			break;
		}
	}

}

void CStage::Leg_MotherHeart()
{
	if(m_pMatherHeart!=nullptr&&m_pMatherHeart->GetMapIndex()==m_curMapIndex&&m_pMatherHeart->GetVisible()&&m_pLeg->GetLegVisible()
		&&m_pLeg->GetIsMove())
	{
		m_pLeg->UpdateLegRc();
		m_pMatherHeart->UpdateMahterRc();
		if(IsHit(m_pLeg->GetLegRc(),m_pMatherHeart->GetMatherRc()))
		{
			m_pMatherHeart->SetHp(m_pMatherHeart->GetHp()-1);
			m_bossHP-=1;
			if(m_pMatherHeart->GetHp()<=0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(6, false);
				m_pMatherHeart->SetVisible(false);
				m_ExplodeVisible = false;
			}
		}
	}
}

void CStage::SelectGoods()
{
	srand(GetTickCount());
	int i = rand() % m_goodsCount + 1;
	m_goods[i]->SetVisible(true);
}

RECT CStage::SortRect(RECT rect1,RECT rect2)
{
	int a1[4],a2[4];
	a1[0]=rect1.top;
	a1[1]=rect1.bottom;
	a1[2]=rect2.top;
	a1[3]=rect2.bottom;

	a2[0]=rect1.left;
	a2[1]=rect1.right;
	a2[2]=rect2.left;
	a2[3]=rect2.right;

	for(int i=0;i<4;i++)
	{
		int k=i;
		for(int j=i+1;j<4;j++)
		{
			if(a1[k]>a1[j])
			{
				k=j;
			}
		}
		int temp1=a1[i];
		a1[i]=a1[k];
		a1[k] = temp1;
	}

	for(int i=0;i<4;i++)
	{
		int k=i;
		for(int j=i+1;j<4;j++)
		{
			if(a2[k]>a2[j])
			{
				k=j;
			}
		}
		int temp1=a2[i];
		a2[i]=a2[k];
		a2[k] = temp1;
	}

	RECT rc={a2[1],a1[1],a2[2],a1[2]};
	return rc;
}

bool CStage::IsFlyDuke_Bullet_Collision(RECT FlyDuke, RECT Bullet)
{
	int width = m_pFlyDuke->GetWidth();
	int frameWidth = m_pFlyDuke->GetFrameWidth();
	for (int i = Bullet.top; i<=Bullet.bottom; i++)
	{
		for (int j = Bullet.left; j<=Bullet.right; j++)
		{
			DWORD colorA = m_pPPixelBullet[(i-Bullet.top+35)*88+j-Bullet.left+37];
			POINT pt = { j, i };
			if(PtInRect(&m_pFlyDuke->GetDukeRect(),pt))
			{
				int y = i - m_pFlyDuke->GetDukeRect().top;
				int x = j - m_pFlyDuke->GetDukeRect().left;
				DWORD colorB = m_pPPixelBoss[y * width + m_pFlyDuke->GetCurRow()*width + x + m_pFlyDuke->GetCurFrame() * frameWidth];
				if ((colorA >= 0xff000000 ) && (colorB >= 0xff000000))
					return true;
			}
		}
	}
	return false;
}

bool CStage::IsFlyDuke_PlayerBody_Collision(RECT FlyDuke,RECT playerBody)
{
	int width = m_pFlyDuke->GetWidth();
	int frameWidth = m_pFlyDuke->GetFrameWidth();
	RECT rc=SortRect(FlyDuke,playerBody);
	for (int i = rc.top; i <= rc.bottom; i++)
	{
		for (int j = rc.left; j <= rc.right; j++)
		{
			DWORD colorA = m_pPPixelBody[(i-playerBody.top)*500+j-playerBody.left];
			POINT pt = { j, i };
			if(PtInRect(&m_pFlyDuke->GetDukeRect(),pt))
			{
				int y = i - m_pFlyDuke->GetDukeRect().top;
				int x = j - m_pFlyDuke->GetDukeRect().left;
				DWORD colorB = m_pPPixelBoss[y * width + m_pFlyDuke->GetCurRow()*width + x + m_pFlyDuke->GetCurFrame() * frameWidth];
				if ((colorA >= 0xff000000 ) && (colorB >= 0xff000000))
					return true;
			}
		}
	}
	return false;
}

bool CStage::IsFlyDuke_PlayerHead_Collision(RECT FlyDuke, RECT playerHead)
{
	int width = m_pFlyDuke->GetWidth();
	int frameWidth = m_pFlyDuke->GetFrameWidth();
	RECT rc = SortRect(FlyDuke, playerHead);
	for (int i = rc.top; i <= rc.bottom; i++)
	{
		for (int j = rc.left; j <= rc.right; j++)
		{
			DWORD colorA = m_pPPixelHead[(i - playerHead.top) * 390 + j - playerHead.left];
			POINT pt = { j, i };
			if (PtInRect(&m_pFlyDuke->GetDukeRect(), pt))
			{
				int y = i - m_pFlyDuke->GetDukeRect().top;
				int x = j - m_pFlyDuke->GetDukeRect().left;
				DWORD colorB = m_pPPixelBoss[y * width + m_pFlyDuke->GetCurRow()*width + x + m_pFlyDuke->GetCurFrame() * frameWidth];
				if ((colorA >= 0xff000000) && (colorB >= 0xff000000))
					return true;
			}
		}
	}
	return false;
}

bool CStage::IsHit(RECT rect1, RECT rect2)
{
	if (rect1.right>rect2.left && rect1.left<rect2.right
		&& rect1.bottom>rect2.top && rect1.top<rect2.bottom)
	{
		return true;
	}
	return false;
}

bool CStage::IsMonsterInRoom()
{
	vector<CFly*>::iterator it = m_fly.begin();
	for (; it != m_fly.end(); it++)
	{
		if (m_curMapIndex == (*it)->GetMapIndex() && (*it)->GetVisible())
		{
			CAudio4Bass::GetInstance()->ChannelPlay(9, false);
			return true;
		}
	}

	if (m_curMapIndex == m_bossRoomNum&&m_bossHP>0)
		return true;

	vector<CFlyMonster*>::iterator it1 = m_flyMonster.begin();
	for (; it1 != m_flyMonster.end(); it1++)
	{
		if (m_curMapIndex == (*it1)->GetMapIndex() && (*it1)->GetVisible())
		{
			return true;
		}
	}

	vector<CMask*>::iterator it2 = m_mask.begin();
	for (; it2 != m_mask.end(); it2++)
	{
		if (m_curMapIndex == (*it2)->GetMapIndex() && (*it2)->GetVisible())
		{
			return true;
		}
	}

	vector<CBob*>::iterator it3 = m_bob.begin();
	for (; it3 != m_bob.end(); it3++)
	{
		if (m_curMapIndex == (*it3)->GetMapIndex() && (*it3)->GetVisible())
		{
			if (m_bobMusicCount % 50 == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(11, false);
			}
			m_bobMusicCount++;
			return true;
		}
	}

	vector<CFeceMonster*>::iterator it4 = m_feceMonster.begin();
	for (; it4 != m_feceMonster.end(); it4++)
	{
		if (m_curMapIndex == (*it4)->GetMapIndex() && (*it4)->GetVisible())
		{
			return true;
		}
	}

	map<int, CMaskHeart*>::iterator it5 = m_maskHeart.begin();
	for (; it5 != m_maskHeart.end(); it5++)
	{
		if (m_curMapIndex == it5->second->GetMapIndex() && it5->second->GetVisible())
		{
			return true;
		}
	}

	return false;
}

Map*CStage::GetMap(int num)
{
	map<int, Map*>::iterator it = m_map.find(num);
	if (it != m_map.end())
		return it->second;
	else
		return nullptr;
}

Map*CStage::GetStone(int num)
{
	map<int, Map*>::iterator it = m_stone.find(num);
	if (it != m_stone.end())
		return it->second;
	else
		return nullptr;
}

CPlayerHead*CStage::GetPlayerHead()
{
	return m_pPlayerHead;
}

CPlayerBody*CStage::GetPlayerBody()
{
	return m_pPlayerBody;
}

CPoolManager*CStage::GetBulletPool()
{
	return m_pBulletPool;
}

CFlyDuke*CStage::GetFlyDuke()
{
	return m_pFlyDuke;
}

CMatherHeart*CStage::GetMatherHeart()
{
	return m_pMatherHeart;
}

int CStage::GetBossHp()
{
	return m_bossHP;
}

void CStage::SetGoodsCount(int i)
{
	m_goodsCount = i;
}