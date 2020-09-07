#include "stdafx.h"
#include "SelectPlayer.h"


CSelectPlayer::CSelectPlayer()
{
	m_pBG = nullptr;
	m_pPlayer = nullptr;
	m_pArrow = nullptr;
	m_pName = nullptr;
	m_pHeart=nullptr;
	m_pAttack=nullptr;
	m_pSpeed=nullptr;
	m_pThree = nullptr;
	m_pTwo = nullptr;
	m_pNone = nullptr;
	m_posIndex = 0;
	m_speed = 0;
	m_dis = 0;
	m_dir = eNONE;
	m_count = 0;
	m_isChangeName = false;
	m_countName = 0;
	m_BGSpeed = 0;
	m_transparent = 0xff000000;
}

CSelectPlayer::~CSelectPlayer()
{
	delete m_pBG;
	delete m_pPlayer;
	delete m_pArrow;
	delete m_pName;
	delete m_pHeart;
	delete m_pAttack;
	delete m_pSpeed;
	delete m_pTwo;
	delete m_pThree;
	delete m_pNone;
}

void CSelectPlayer::Init()
{
	TiXmlDocument *doc = new TiXmlDocument("Data.xml");
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
		int type, desX, desY;
		element->Attribute("type", &type);
		switch (type)
		{
		case 18:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pBG = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				  m_pBG->Init();
				  m_pBG->SetDesPos(pos);
				  m_pBG->SetShowWidth(m_pBG->GetPicWidth());
				  m_pBG->SetShowHeight(m_pBG->GetPicHeight());
		}
			break;
		case 19:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pPlayer = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				  m_pPlayer->Init();
				  m_pPlayer->SetDesPos(pos);
				  m_pPlayer->SetShowWidth(m_pPlayer->GetFrameWidth());
				  m_pPlayer->SetShowHeight(m_pPlayer->GetFrameHeight());
		}
			break;
		case 20:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pArrow = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				   m_pArrow->Init();
				   m_pArrow->SetDesPos(pos);
				   pos.x = m_pArrow->GetFrameWidth();
				   pos.y = 0;
				   m_pArrow->SetSrcPos(pos);
				   m_pArrow->SetShowWidth(m_pArrow->GetFrameWidth());
				   m_pArrow->SetShowHeight(m_pArrow->GetFrameHeight());
		}
			break;
		case 21:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pName = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				   m_pName->Init();
				   m_pName->SetDesPos(pos);
				   m_pName->SetShowWidth(m_pName->GetFrameWidth());
				   m_pName->SetShowHeight(m_pName->GetFrameHeight());
		}
			break;
		case 22:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pHeart = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pHeart->Init();
				   m_pHeart->SetDesPos(pos);
				   m_pHeart->SetShowWidth(m_pHeart->GetPicWidth());
				   m_pHeart->SetShowHeight(m_pHeart->GetPicHeight());
		}
			break;
		case 23:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pAttack = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pAttack->Init();
				   m_pAttack->SetDesPos(pos);
				   m_pAttack->SetShowWidth(m_pAttack->GetPicWidth());
				   m_pAttack->SetShowHeight(m_pAttack->GetPicHeight());
		}
			break;
		case 24:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pSpeed = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pSpeed->Init();
				   m_pSpeed->SetDesPos(pos);
				   m_pSpeed->SetShowWidth(m_pSpeed->GetPicWidth());
				   m_pSpeed->SetShowHeight(m_pSpeed->GetPicHeight());
		}
			break;
		case 25:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pTwo = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pTwo->Init();
				   m_pTwo->SetDesPos(pos);
				   m_pTwo->SetShowWidth(m_pTwo->GetPicWidth());
				   m_pTwo->SetShowHeight(m_pTwo->GetPicHeight());
		}
			break;
		case 26:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pThree = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pThree->Init();
				   m_pThree->SetDesPos(pos);
				   m_pThree->SetShowWidth(m_pThree->GetPicWidth());
				   m_pThree->SetShowHeight(m_pThree->GetPicHeight());
		}
			break;
		case 27:
		{
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   POINT pos = { desX, desY };
				   m_pNone = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				   m_pNone->Init();
				   m_pNone->SetDesPos(pos);
				   m_pNone->SetShowWidth(m_pNone->GetPicWidth());
				   m_pNone->SetShowHeight(m_pNone->GetPicHeight());
		}
			break;
		case 28:
			{
				int x,y;
				element->Attribute("x1", &x);
				element->Attribute("y1", &y);
				m_desPos0.x=m_desPos[0].x = x;
				m_desPos0.y=m_desPos[0].y=y;
				m_desPos4.x=m_desPos[4].x = x;
				m_desPos4.y=m_desPos[4].y=y;
				element->Attribute("x2", &x);
				element->Attribute("y2", &y);
				m_desPos1.x=m_desPos[1].x = x;
				m_desPos1.y=m_desPos[1].y=y;
				element->Attribute("x3", &x);
				element->Attribute("y3", &y);
				m_desPos2.x=m_desPos[2].x = x;
				m_desPos2.y=m_desPos[2].y=y;
				element->Attribute("x4", &x);
				element->Attribute("y4", &y);
				m_desPos3.x=m_desPos[3].x = x;
				m_desPos3.y=m_desPos[3].y=y;
				element->Attribute("speed", &m_speed);
				element->Attribute("BGspeed", &m_BGSpeed);
			}
			break;
		}
		element = element->NextSiblingElement();
	}
	
	for (int i = 0; i < 4;i++)
		D3DXVec2Normalize(&m_line[i],&(m_desPos[i+1]-m_desPos[i]));

	m_dis = D3DXVec2Length(&(m_desPos[1] - m_desPos[0]));
}

void CSelectPlayer::Draw()
{
	POINT pos;
	int width = m_pPlayer->GetFrameWidth();
	int height = m_pPlayer->GetFrameHeight();
	int curFrame = m_pPlayer->GetCurFrame();
	int curRow = m_pPlayer->GetCurRow();
	POINT srcPos = { curFrame*width, curRow*height };

	m_pBG->Draw();
	m_pArrow->Draw();
	m_pName->Draw();
	if (m_countName == 0)
	{
		m_pHeart->Draw();
		m_pAttack->Draw();
		m_pSpeed->Draw();
		pos.x = 560+m_pBG->GetDesPos().x;
		pos.y = 435;
		m_pTwo->SetDesPos(pos);
		m_pTwo->Draw();
		m_pThree->Draw();
		pos.x = 440 + m_pBG->GetDesPos().x;
		pos.y = 435;
		m_pTwo->SetDesPos(pos);
		m_pTwo->Draw();
	}
	else
		m_pNone->Draw();

	if (m_posIndex == 4)
		m_posIndex = 0;
	

	if (m_dir == eRIGHT)
	{
		if (D3DXVec2Length(&(m_desPos[m_posIndex] - m_desPos0)) < m_dis)
		{
			if (D3DXVec2Length(&(m_desPos0 - m_desPos[(1 + m_posIndex) % 4])) <= m_speed)
			{
				m_desPos0 = m_desPos[(1 + m_posIndex) % 4];
				m_dir = eNONE;
			}
			else
			{
				m_desPos0 += m_line[m_posIndex] * m_speed;
			}
		}
	}

	switch (m_posIndex)
	{
	case 0:
		if (m_count == 0)
			m_transparent = 0xff000000;
		else
			m_transparent = 0x88000000;
		break;
	case 1:
		m_transparent = 0x33000000;
		break;
	case 2:
		m_transparent = 0x88000000;
		break;
	case 3:
		m_transparent = 0xff000000;
		break;
	}
	m_pPlayer->SetTrasparent(m_transparent);
	pos.x = m_desPos0.x + m_pBG->GetDesPos().x;
	pos.y=m_desPos0.y ;
	m_pPlayer->SetSrcPos(srcPos);
	m_pPlayer->SetDesPos(pos);
	m_pPlayer->Draw();


	if (m_dir == eRIGHT)
	{
		if (D3DXVec2Length(&(m_desPos[(m_posIndex + 1) % 4] - m_desPos1)) < m_dis)
		{
			if (D3DXVec2Length(&(m_desPos1 - m_desPos[(2 + m_posIndex) % 4])) <= m_speed)
			{
				m_desPos1 = m_desPos[(2 + m_posIndex) % 4];
				m_dir = eNONE;
			}
			else
			{
				m_desPos1 += m_line[(m_posIndex + 1) % 4] * m_speed;
			}
		}
	}
	
	switch ((m_posIndex + 1) % 4)
	{
	case 0:
		m_transparent = 0x88000000;
		break;
	case 1:
		if (m_count == 0)
			m_transparent = 0x88000000;
		else
			m_transparent = 0x33000000;
		break;
	case 2:
		m_transparent = 0x88000000;
		break;
	case 3:
		m_transparent = 0xff000000;
		break;
	}
	m_pPlayer->SetTrasparent(m_transparent);
	srcPos.x = width;
	pos.x = m_desPos1.x + m_pBG->GetDesPos().x;
	pos.y=m_desPos1.y ;
	m_pPlayer->SetSrcPos(srcPos);
	m_pPlayer->SetDesPos(pos);
	m_pPlayer->Draw();

	if (m_dir == eRIGHT)
	{
		if (D3DXVec2Length(&(m_desPos[(m_posIndex + 2) % 4] - m_desPos2)) < m_dis)
		{
			if (D3DXVec2Length(&(m_desPos2 - m_desPos[(3 + m_posIndex) % 4])) <= m_speed)
			{
				m_desPos2 = m_desPos[(3 + m_posIndex) % 4];
				m_dir = eNONE;
			}
			else
			{
				m_desPos2 += m_line[(m_posIndex + 2) % 4] * m_speed;
			}
		}
	}
	
	switch ((m_posIndex + 2) % 4)
	{
	case 0:
		m_transparent = 0x88000000;
		break;
	case 1:
		m_transparent = 0x33000000;
		break;
	case 2:
		if (m_count == 0)
			m_transparent = 0x33000000;
		else
			m_transparent = 0x88000000;
		break;
	case 3:
		m_transparent = 0xff000000;
		break;
	}
	m_pPlayer->SetTrasparent(m_transparent);
	srcPos.x = width*2;
	pos.x = m_desPos2.x + m_pBG->GetDesPos().x;
	pos.y=m_desPos2.y ;
	m_pPlayer->SetSrcPos(srcPos);
	m_pPlayer->SetDesPos(pos);
	m_pPlayer->Draw();

	if (m_dir == eRIGHT)
	{
		if (D3DXVec2Length(&(m_desPos[(m_posIndex + 3) % 4] - m_desPos3)) < m_dis)
		{
			if (D3DXVec2Length(&(m_desPos3 - m_desPos[(4 + m_posIndex) % 4])) <= m_speed)
			{
				m_desPos3 = m_desPos[(4 + m_posIndex) % 4];
				m_dir = eNONE;
			}
			else
			{
				m_desPos3 += m_line[(m_posIndex + 3) % 4] * m_speed;
			}
		}
	}
	
	switch ((m_posIndex + 3) % 4)
	{
	case 0:
		m_transparent = 0x88000000;
		break;
	case 1:
		m_transparent = 0x33000000;
		break;
	case 2:
		m_transparent = 0x88000000;
		break;
	case 3:
		if (m_count == 0)
			m_transparent = 0x88000000;
		else
			m_transparent = 0xff000000;
		break;
	}
	m_pPlayer->SetTrasparent(m_transparent);
	srcPos.x = width * 3;
	pos.x = m_desPos3.x + m_pBG->GetDesPos().x;
	pos.y=m_desPos3.y ;
	m_pPlayer->SetSrcPos(srcPos);
	m_pPlayer->SetDesPos(pos);
	m_pPlayer->Draw();

}

void CSelectPlayer::Update()
{
	m_pBG->UpdateMAatrix();
	m_pPlayer->UpdateMAatrix();
	m_pArrow->UpdateMAatrix();
	m_pName->UpdateMAatrix();
	m_pHeart->UpdateMAatrix();
	m_pAttack->UpdateMAatrix();
	m_pSpeed->UpdateMAatrix();
	m_pTwo->UpdateMAatrix();
	m_pThree->UpdateMAatrix();
	m_pNone->UpdateMAatrix();

	if (m_isChangeName)
		switch (m_countName)
	{
		case 0:
			m_isChangeName = false;
			m_pName->ReSet(0, 0, 0, 0, 0, 0);
			break;
		case 1:
			m_isChangeName = false;
			m_pName->ReSet(6, 6, 0, 0, 6, 6);
			break;
		case 2:
			m_isChangeName = false;
			m_pName->ReSet(4, 4, 0, 0, 4, 4);
			break;
		case 3:
			m_isChangeName = false;
			m_pName->ReSet(1, 1, 0, 0, 1, 1);
			break;
	}
	m_pName->Update();

	if (CGameManager::GetInstance()->GetGameState() == eSELECT_PLAYER)
	if (m_pBG->GetDesPos().x > 0)
	{
		POINT pos = m_pBG->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pBG->SetDesPos(pos);

		pos = m_pPlayer->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pPlayer->SetDesPos(pos);

		pos = m_pArrow->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pArrow->SetDesPos(pos);

		pos = m_pName->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pName->SetDesPos(pos);

		pos = m_pHeart->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pHeart->SetDesPos(pos);

		pos = m_pAttack->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pAttack->SetDesPos(pos);

		pos = m_pTwo->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pTwo->SetDesPos(pos);

		pos = m_pSpeed->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pSpeed->SetDesPos(pos);

		pos = m_pThree->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pThree->SetDesPos(pos);

		pos = m_pNone->GetDesPos();
		pos.x -= m_BGSpeed;
		m_pNone->SetDesPos(pos);
	}

	if (CGameManager::GetInstance()->GetGameState() == eNEW_RUN)
	if (m_pBG->GetDesPos().x < 832)
	{
		POINT pos = m_pBG->GetDesPos();
		pos.x += m_BGSpeed;
		m_pBG->SetDesPos(pos);

		pos = m_pPlayer->GetDesPos();
		pos.x += m_BGSpeed;
		m_pPlayer->SetDesPos(pos);

		pos = m_pArrow->GetDesPos();
		pos.x += m_BGSpeed;
		m_pArrow->SetDesPos(pos);

		pos = m_pName->GetDesPos();
		pos.x += m_BGSpeed;
		m_pName->SetDesPos(pos);

		pos = m_pHeart->GetDesPos();
		pos.x += m_BGSpeed;
		m_pHeart->SetDesPos(pos);

		pos = m_pAttack->GetDesPos();
		pos.x += m_BGSpeed;
		m_pAttack->SetDesPos(pos);

		pos = m_pTwo->GetDesPos();
		pos.x += m_BGSpeed;
		m_pTwo->SetDesPos(pos);

		pos = m_pSpeed->GetDesPos();
		pos.x += m_BGSpeed;
		m_pSpeed->SetDesPos(pos);

		pos = m_pThree->GetDesPos();
		pos.x += m_BGSpeed;
		m_pThree->SetDesPos(pos);

		pos = m_pNone->GetDesPos();
		pos.x += m_BGSpeed;
		m_pNone->SetDesPos(pos);
	}
}

void CSelectPlayer::OnKeyDown(SEvent event)
{
	if (event.keyInput.pressedDown)
	{
		switch (event.keyInput.key)
		{
		case VK_RIGHT:
			m_count++;
			if (m_dir == eNONE)
			{
				m_dir = eRIGHT;
				if (m_count != 1)
				{
					m_posIndex += 1;
				}
				m_isChangeName = true;
				m_countName++;
				if (m_countName == 4)
					m_countName = 0;
			}
			break;
		case VK_RETURN:
			if (m_countName == 0 && m_pBG->GetDesPos().x == 0)
			{
				CAudio4Bass::GetInstance()->ChannelStop(0);
				CAudio4Bass::GetInstance()->ChannelPlay(1,true);
				CGameManager::GetInstance()->GetTransition()->SetStart(true);
				CInputManager::GetInstance()->DeleteKeyListener(_T("SelectPlayer"));
				CInputManager::GetInstance()->AddKeyListener(_T("PlayerHead"), CGameManager::GetInstance()->GetFirstStage()->GetPlayerHead());
				CInputManager::GetInstance()->AddKeyListener(_T("PlayerBody"), CGameManager::GetInstance()->GetFirstStage()->GetPlayerBody());
				CInputManager::GetInstance()->AddKeyListener(_T("BulletPool"), CGameManager::GetInstance()->GetFirstStage()->GetBulletPool());
			}
			break;
		case VK_ESCAPE:
			if (m_pBG->GetDesPos().x == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eNEW_RUN);
				CInputManager::GetInstance()->DeleteKeyListener(_T("SelectPlayer"));
				CInputManager::GetInstance()->AddKeyListener(_T("NewGame"), CGameManager::GetInstance()->GetNewGame());
			}
			break;
		}
	}
}