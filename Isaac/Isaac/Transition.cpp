#include "stdafx.h"
#include "Transition.h"


CTransition::CTransition()
{
	m_pTransition = nullptr;
	m_pBlack = nullptr;
	m_transparent = 0x00000000;
	m_start = false;
	m_count = 0;
	m_startCount = 0;
	m_endCount = 0;
}

CTransition::~CTransition()
{
	delete m_pTransition;
	delete m_pBlack;
}

void CTransition::Init()
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
		case 5:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pTransition = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				  m_pTransition->Init();
				  m_pTransition->SetShowWidth(m_pTransition->GetPicWidth());
				  m_pTransition->SetShowHeight(m_pTransition->GetPicHeight());
				  m_pTransition->SetTrasparent(m_transparent);
				  m_pTransition->SetDesPos(pos); 
		}
			break;
		case 6:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pBlack = (CStaticImg*)CResManager::GetInstance()->GetRes(_T("black"));
				  m_pBlack->Init();
				  m_pBlack->SetShowWidth(m_pBlack->GetPicWidth());
				  m_pBlack->SetShowHeight(m_pBlack->GetPicHeight());
				  m_pBlack->SetDesPos(pos);
		}
			break;
		case 7:
			element->Attribute("startCount", &m_startCount);
			element->Attribute("endCount", &m_endCount);
			break;
		}
		element = element->NextSiblingElement();
	}
}

void CTransition::Draw()
{
	m_pTransition->Draw();
	if (m_count >= m_startCount&&m_count <= m_endCount)
		m_pBlack->Draw();
}

void CTransition::Update()
{
	if (m_start)
	{
		m_pTransition->UpdateMAatrix();
		m_pBlack->UpdateMAatrix();
		if (m_transparent == 0xff000000)
			CGameManager::GetInstance()->SetGameState(eGAME_PLAY);
		if (CGameManager::GetInstance()->GetGameState() == eGAME_PLAY)
			m_count++;
		if (CGameManager::GetInstance()->GetGameState() == eSELECT_PLAYER&&m_transparent != 0xff000000)
		{
			m_transparent += 0x05000000;
			m_pTransition->SetTrasparent(m_transparent);
		}
		else if (CGameManager::GetInstance()->GetGameState() == eGAME_PLAY&&m_transparent != 0x00000000&&m_count>=50)
		{
			m_transparent -= 0x05000000;
			m_pTransition->SetTrasparent(m_transparent);
		}
		if (CGameManager::GetInstance()->GetGameState() == eGAME_PLAY&&m_transparent == 0x00000000)
		{
			m_start = false;
		}
	}
}

void CTransition::SetStart(bool b)
{
	m_start = b;
}
