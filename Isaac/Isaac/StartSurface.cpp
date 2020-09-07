#include "stdafx.h"
#include "StartSurface.h"


CStartSurface::CStartSurface()
{
	m_pFly = nullptr;
	m_pBoy = nullptr;
	m_pLogo = nullptr;
	m_pBg = nullptr;
	m_count = 0;
	m_angle = 0;
	count = 0;
	countAngle1 = 0;
	dir = false;
	m_speed = 0;
	m_updateRate = 0;
	m_preAngle = 0.0f;
}

CStartSurface::~CStartSurface()
{
	delete m_pFly;
	delete m_pBoy;
	delete m_pLogo;
	delete m_pBg;
}

void CStartSurface::Init()
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
		int type, desX, desY,showWidth,showHeight;
		element->Attribute("type",&type);
		switch(type)
		{
		case 0:
			{
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("showWidth", &showWidth);
				element->Attribute("showHeight", &showHeight);

				POINT pos = { desX, desY };
				m_pBg = (CStaticImg *)CResManager::GetInstance()->GetRes(name);
				m_pBg->Init();
				m_pBg->SetDesPos(pos);
				m_pBg->SetShowWidth(showWidth);
				m_pBg->SetShowHeight(showHeight);
			}
			break;
		case 1:
			{
				int angle;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				element->Attribute("showWidth", &showWidth);
				element->Attribute("showHeight", &showHeight);
				element->Attribute("angle", &angle);

				POINT pos = { desX, desY };
				RECT rc = *(RECT*)CPlatform::GetInstance()->GetPlatData(_T("rect"));
				m_pLogo = (CStaticImg*)CResManager::GetInstance()->GetRes(name);
				m_pLogo->Init();
				m_pLogo->SetCenter(m_pLogo->GetPicWidth() / 2, 0);
				m_pLogo->SetAngle(angle);
				m_pLogo->SetMove( rc.right / 2, 0);
				m_pLogo->SetDesPos(pos);
				m_pLogo->SetShowWidth(showWidth);
				m_pLogo->SetShowHeight(showHeight);
			}
			break;
		case 2:
		{
				  int startFrame, endFrame;
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  element->Attribute("startFrame", &startFrame);
				  element->Attribute("endFrame", &endFrame);

				  POINT pos = { desX, desY };
				  m_pBoy = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				  m_pBoy->Init();
				  m_pBoy->SetDesPos(pos);
				  m_pBoy->SetShowWidth(m_pBoy->GetFrameWidth());
				  m_pBoy->SetShowHeight(m_pBoy->GetFrameHeight());
				  m_pBoy->SetStartFrame(startFrame);
				  m_pBoy->SetEndFrame(endFrame);
		}
			break;
		case 3:
		{
				  int startRow, endRow;
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  element->Attribute("startRow", &startRow);
				  element->Attribute("endRow", &endRow);

				  POINT pos = { desX, desY };
				  m_pFly = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				  m_pFly->Init();
				  m_pFly->SetDesPos(pos);
				  m_pFly->SetShowWidth(m_pFly->GetFrameWidth());
				  m_pFly->SetShowHeight(m_pFly->GetFrameHeight());
				  m_pFly->SetStartRow(startRow);
				  m_pFly->SetEndRow(endRow);
		}
			break;
		case 4:
		{
				  int a;
				  element->Attribute("speed", &m_speed);
			      element->Attribute("updateRate", &m_updateRate);
				  element->Attribute("countAngle", &count);
				  element->Attribute("countAngle1", &countAngle1);
				  element->Attribute("preAngle", &a);
				  m_preAngle = (float)a / 1000;
		}
			break;
		}
		element = element->NextSiblingElement();
	}
}

void CStartSurface::Draw()
{
	m_pBg->Draw();
	m_pLogo->Draw();
	m_pBoy->Draw();
	m_pFly->Draw();
}

void CStartSurface::Update()
{
	m_pFly->UpdateMAatrix();
	m_pBoy->UpdateMAatrix();
	m_pLogo->UpdateMAatrix();
	m_pBg->UpdateMAatrix();

	if (dir)
	{
		count++;
		m_angle += m_preAngle;
	}
	else
	{
		count --;
		m_angle -= m_preAngle;
	}
	if (count == countAngle1)
		dir = false;
	else if (count == -countAngle1)
		dir = true;

	m_pLogo->SetAngle(m_angle);

	m_count++;
	if (m_count % m_updateRate == 0)
	{
		m_pBoy->Update();
		m_pFly->Update();
		m_count = 0;
	}

	if (CGameManager::GetInstance()->GetGameState()==eSELECT_FILE)
	if (m_pBg->GetDesPos().y > -m_pBg->GetPicHeight())
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y -= m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFly->GetDesPos();
		pos.y -= m_speed;
		m_pFly->SetDesPos(pos);

		pos = m_pBoy->GetDesPos();
		pos.y -= m_speed;
		m_pBoy->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y -= m_speed;
		m_pLogo->SetDesPos(pos);
	}

	if (CGameManager::GetInstance()->GetGameState() == eSTART_SURFACE)
	if (m_pBg->GetDesPos().y < 0)
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y += m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFly->GetDesPos();
		pos.y += m_speed;
		m_pFly->SetDesPos(pos);

		pos = m_pBoy->GetDesPos();
		pos.y += m_speed;
		m_pBoy->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y += m_speed;
		m_pLogo->SetDesPos(pos);
	}
}

void CStartSurface::OnKeyDown(SEvent event)
{
	if (event.keyInput.pressedDown)
		switch (event.keyInput.key)
	{
		case VK_RETURN:
			if (m_pBg->GetDesPos().y == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eSELECT_FILE);
				CInputManager::GetInstance()->DeleteKeyListener(_T("StartSurface"));
				CInputManager::GetInstance()->AddKeyListener(_T("SelectFile"), CGameManager::GetInstance()->GetSelectFile());
				CGameManager::GetInstance()->GetSelectFile()->SetIsUp(true);
			}
			break;
	}
}