#include "stdafx.h"
#include "NewGame.h"


CNewGame::CNewGame()
{
	m_pNewGame = nullptr;
	m_pOption = nullptr;
	m_speed = 0;
}

CNewGame::~CNewGame()
{
	delete m_pNewGame;
	delete m_pOption;
}

void CNewGame::Init()
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
		case 8:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pNewGame = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				  m_pNewGame->Init();
				  m_pNewGame->SetDesPos(pos);
				  m_pNewGame->SetShowWidth(m_pNewGame->GetPicWidth());
				  m_pNewGame->SetShowHeight(m_pNewGame->GetPicHeight());
		}
			break;
		case 9:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pOption = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				  m_pOption->Init();
				  m_pOption->SetDesPos(pos);
				  m_pOption->SetShowWidth(m_pOption->GetPicWidth());
				  m_pOption->SetShowHeight(m_pOption->GetPicHeight());
		}
			break;
		case 10:
			element->Attribute("speed", &m_speed);
			break;
		}
		element = element->NextSiblingElement();
	}
}

void CNewGame::Draw()
{
	m_pNewGame->Draw();
	m_pOption->Draw();
}

void CNewGame::Update()
{
	m_pNewGame->UpdateMAatrix();
	m_pOption->UpdateMAatrix();

	if (CGameManager::GetInstance()->GetGameState() == eSELECT_FILE)
	if (m_pNewGame->GetDesPos().y < m_pNewGame->GetPicHeight())
	{
		POINT pos = m_pNewGame->GetDesPos();
		pos.y += m_speed;
		m_pNewGame->SetDesPos(pos);

		pos = m_pOption->GetDesPos();
		pos.y += m_speed;
		m_pOption->SetDesPos(pos);
	}

	if (CGameManager::GetInstance()->GetGameState() == eNEW_RUN)
	{
		if (m_pNewGame->GetDesPos().y > 0)
		{
			POINT pos = m_pNewGame->GetDesPos();
			pos.y -= m_speed;
			m_pNewGame->SetDesPos(pos);

			pos = m_pOption->GetDesPos();
			pos.y -= m_speed;
			m_pOption->SetDesPos(pos);
		}

		if (m_pNewGame->GetDesPos().x < 0)
		{
			POINT pos = m_pNewGame->GetDesPos();
			pos.x += m_speed;
			m_pNewGame->SetDesPos(pos);

			pos = m_pOption->GetDesPos();
			pos.x += m_speed;
			m_pOption->SetDesPos(pos);
		}
	}

	if (CGameManager::GetInstance()->GetGameState() == eSELECT_PLAYER)
	if (m_pNewGame->GetDesPos().x > -m_pNewGame->GetPicWidth())
	{
		POINT pos = m_pNewGame->GetDesPos();
		pos.x -= m_speed;
		m_pNewGame->SetDesPos(pos);

		pos = m_pOption->GetDesPos();
		pos.x -= m_speed;
		m_pOption->SetDesPos(pos);
	}
}

void CNewGame::OnKeyDown(SEvent event)
{
	if (event.keyInput.pressedDown)
	{
		switch (event.keyInput.key)
		{
		case VK_RETURN:
			if (m_pNewGame->GetDesPos().y == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eSELECT_PLAYER);
				CInputManager::GetInstance()->DeleteKeyListener(_T("NewGame"));
				CInputManager::GetInstance()->AddKeyListener(_T("SelectPlayer"), CGameManager::GetInstance()->GetSelectPlayer());
			}
			break;
		case VK_ESCAPE:
			if (m_pNewGame->GetDesPos().x == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eSELECT_FILE);
				CInputManager::GetInstance()->DeleteKeyListener(_T("NewGame"));
				CInputManager::GetInstance()->AddKeyListener(_T("SelectFile"), CGameManager::GetInstance()->GetSelectFile());
				CGameManager::GetInstance()->GetSelectFile()->SetIsUp(false);
			}
			break;
		}
	}
}