#include "stdafx.h"
#include "SelectFile.h"


CSelectFile::CSelectFile()
{
	m_pFile1=nullptr;
	m_pFile2=nullptr;
	m_pFile3=nullptr;
	m_pDelete=nullptr;
	m_pBg=nullptr;
	m_pLogo = nullptr;
	m_select = eFILE_ONE;
	m_bIsUp = true;
	m_speed = 32;
	m_pFile=nullptr;
	m_count=0;
}

CSelectFile::~CSelectFile()
{
	delete m_pFile1;
	delete m_pFile2;
	delete m_pFile3;
	delete m_pDelete;
	delete m_pBg;
	vector<CSingleImg*>::iterator it=m_file.begin();
	for(;it!=m_file.end();it++)
	{
		delete (*it);
	}
}

void CSelectFile::Init()
{
	FILE *file;

	fopen_s(&file, "file1.bin", "rb+");
	fread(&m_saveNum1, sizeof(int), 1, file);
	fclose(file);

	fopen_s(&file, "file2.bin", "rb+");
	fread(&m_saveNum2, sizeof(int), 1, file);
	fclose(file);

	fopen_s(&file, "file3.bin", "rb+");
	fread(&m_saveNum3, sizeof(int), 1, file);
	fclose(file);



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
		case 11:
		{
				  element->Attribute("desX", &desX);
				  element->Attribute("desY", &desY);
				  POINT pos = { desX, desY };
				  m_pBg = (CStaticImg *)CResManager::GetInstance()->GetRes(name);
				  m_pBg->Init();
				  m_pBg->SetDesPos(pos);
				  m_pBg->SetShowWidth(m_pBg->GetPicWidth());
				  m_pBg->SetShowHeight(m_pBg->GetPicHeight());
		}
			break;
		case 12:
		{
				   int width, height;
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &width);
				   element->Attribute("showHeight", &height);
				   POINT pos = { desX, desY };
				   m_pFile1 = (CMulImg *)CResManager::GetInstance()->GetRes(name);
				   m_pFile1->Init();
				   m_pFile1->SetDesPos(pos);
				   m_pFile1->SetShowWidth(width);
				   m_pFile1->SetShowHeight(height);
		}
			break;
		case 13:
		{
				   int width, height;
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &width);
				   element->Attribute("showHeight", &height);
				   POINT pos = { desX, desY };
				   m_pFile2 = (CMulImg *)CResManager::GetInstance()->GetRes(name);
				   m_pFile2->Init();
				   m_pFile2->SetDesPos(pos);
				   m_pFile2->SetShowWidth(width);
				   m_pFile2->SetShowHeight(height);
		}
			break;
		case 14:
		{
				   int width, height;
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &width);
				   element->Attribute("showHeight", &height);
				   POINT pos = { desX, desY };
				   m_pFile3 = (CMulImg *)CResManager::GetInstance()->GetRes(name);
				   m_pFile3->Init();
				   m_pFile3->SetDesPos(pos);
				   m_pFile3->SetShowWidth(width);
				   m_pFile3->SetShowHeight(height);
		}
			break;
		case 15:
		{
				   int width, height;
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &width);
				   element->Attribute("showHeight", &height);
				   POINT pos = { desX, desY };
				   m_pLogo = (CStaticImg *)CResManager::GetInstance()->GetRes(name);
				   m_pLogo->Init();
				   m_pLogo->SetDesPos(pos);
				   m_pLogo->SetShowWidth(width);
				   m_pLogo->SetShowHeight(height);
		}
			break;
		case 16:
		{
				   int width, height;
				   element->Attribute("desX", &desX);
				   element->Attribute("desY", &desY);
				   element->Attribute("showWidth", &width);
				   element->Attribute("showHeight", &height);
				   POINT pos = { desX, desY };
				   m_pDelete = (CMulImg *)CResManager::GetInstance()->GetRes(name);
				   m_pDelete->Init();
				   m_pDelete->SetDesPos(pos);
				   m_pDelete->SetShowWidth(width);
				   m_pDelete->SetShowHeight(height);
		}
			break;
		case 17:
			element->Attribute("speed", &m_speed);
			break;
		case 29:
			{
				int width, height;
				element->Attribute("desX", &desX);
				element->Attribute("desY", &desY);
				POINT pos = { desX, desY };
				m_pFile = (CSingleImg*)CResManager::GetInstance()->GetRes(name);
				m_pFile->Init();
				m_pFile->SetDesPos(pos);
				m_pFile->SetShowWidth(m_pFile->GetFrameWidth());
				m_pFile->SetShowHeight(m_pFile->GetFrameHeight());
				m_pFile->UpdateMAatrix();
				m_pFile->ReSet(0,0,0,1,0,0);
				m_file.push_back(m_pFile);
			}
			break;
		}
		element = element->NextSiblingElement();
	}
}

void CSelectFile::Draw()
{
	m_pBg->Draw();
	m_pLogo->Draw();
	m_pFile1->Draw();
	m_pFile2->Draw();
	m_pFile3->Draw();
	m_pDelete->Draw();

	if(m_saveNum1==1)
		m_file[0]->Draw();
	if(m_saveNum2==1)
		m_file[1]->Draw();
	if(m_saveNum3==1)
		m_file[2]->Draw();
	if (m_saveNum1 == 2)
		m_file[3]->Draw();
	if (m_saveNum2 == 2)
		m_file[4]->Draw();
	if (m_saveNum3 == 2)
		m_file[5]->Draw();
}

void CSelectFile::Update()
{
	m_pFile1->UpdateMAatrix();
	m_pFile2->UpdateMAatrix();
	m_pFile3->UpdateMAatrix();
	m_pDelete->UpdateMAatrix();
	m_pBg->UpdateMAatrix();
	m_pLogo->UpdateMAatrix();

	if (CGameManager::GetInstance()->GetGameState() == eSELECT_FILE)
	if (m_pBg->GetDesPos().y > 0&&m_bIsUp)
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y -= m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFile1->GetDesPos();
		pos.y -= m_speed;
		m_pFile1->SetDesPos(pos);

		pos = m_pFile2->GetDesPos();
		pos.y -= m_speed;
		m_pFile2->SetDesPos(pos);

		pos = m_pFile3->GetDesPos();
		pos.y -= m_speed;
		m_pFile3->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y -= m_speed;
		m_pLogo->SetDesPos(pos);

		pos = m_pDelete->GetDesPos();
		pos.y -= m_speed;
		m_pDelete->SetDesPos(pos);

		vector<CSingleImg*>::iterator it=m_file.begin();
		for(;it!=m_file.end();it++)
		{
			pos=(*it)->GetDesPos();
			pos.y-=m_speed;
			(*it)->SetDesPos(pos);
		}
	}
	else if (m_pBg->GetDesPos().y < 0 && !m_bIsUp)
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y += m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFile1->GetDesPos();
		pos.y += m_speed;
		m_pFile1->SetDesPos(pos);

		pos = m_pFile2->GetDesPos();
		pos.y += m_speed;
		m_pFile2->SetDesPos(pos);

		pos = m_pFile3->GetDesPos();
		pos.y += m_speed;
		m_pFile3->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y += m_speed;
		m_pLogo->SetDesPos(pos);

		pos = m_pDelete->GetDesPos();
		pos.y += m_speed;
		m_pDelete->SetDesPos(pos);

		vector<CSingleImg*>::iterator it=m_file.begin();
		for(;it!=m_file.end();it++)
		{
			pos=(*it)->GetDesPos();
			pos.y+=m_speed;
			(*it)->SetDesPos(pos);
		}
	}

	if (CGameManager::GetInstance()->GetGameState() == eSTART_SURFACE)
	if (m_pBg->GetDesPos().y < m_pBg->GetPicHeight())
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y += m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFile1->GetDesPos();
		pos.y += m_speed;
		m_pFile1->SetDesPos(pos);

		pos = m_pFile2->GetDesPos();
		pos.y += m_speed;
		m_pFile2->SetDesPos(pos);

		pos = m_pFile3->GetDesPos();
		pos.y += m_speed;
		m_pFile3->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y += m_speed;
		m_pLogo->SetDesPos(pos);

		pos = m_pDelete->GetDesPos();
		pos.y += m_speed;
		m_pDelete->SetDesPos(pos);

		vector<CSingleImg*>::iterator it=m_file.begin();
		for(;it!=m_file.end();it++)
		{
			pos=(*it)->GetDesPos();
			pos.y+=m_speed;
			(*it)->SetDesPos(pos);
		}
	}

	if (CGameManager::GetInstance()->GetGameState() == eNEW_RUN)
	if (m_pBg->GetDesPos().y > -m_pBg->GetPicHeight())
	{
		POINT pos = m_pBg->GetDesPos();
		pos.y -= m_speed;
		m_pBg->SetDesPos(pos);

		pos = m_pFile1->GetDesPos();
		pos.y -= m_speed;
		m_pFile1->SetDesPos(pos);

		pos = m_pFile2->GetDesPos();
		pos.y -= m_speed;
		m_pFile2->SetDesPos(pos);

		pos = m_pFile3->GetDesPos();
		pos.y -= m_speed;
		m_pFile3->SetDesPos(pos);

		pos = m_pLogo->GetDesPos();
		pos.y -= m_speed;
		m_pLogo->SetDesPos(pos);

		pos = m_pDelete->GetDesPos();
		pos.y -= m_speed;
		m_pDelete->SetDesPos(pos);

		vector<CSingleImg*>::iterator it=m_file.begin();
		for(;it!=m_file.end();it++)
		{
			pos=(*it)->GetDesPos();
			pos.y-=m_speed;
			(*it)->SetDesPos(pos);
		}
	}



	
	POINT pos;
	if (m_pBg->GetDesPos().y == 0 && CGameManager::GetInstance()->GetGameState() == eSELECT_FILE)
	switch (m_select)
	{
	case eFILE_ONE:
		pos = m_pFile1->GetDesPos();
		pos.y = 50;
		m_pFile1->SetDesPos(pos);
		m_pFile1->SetCurFrame(1);

		pos = m_pFile2->GetDesPos();
		pos.y = 80;
		m_pFile2->SetDesPos(pos);
		m_pFile2->SetCurFrame(0);

		pos = m_pFile3->GetDesPos();
		pos.y = 80;
		m_pFile3->SetDesPos(pos);
		m_pFile3->SetCurFrame(0);

		m_pDelete->SetCurFrame(0);

		pos=m_file[0]->GetDesPos();
		pos.y=50;
		m_file[0]->SetDesPos(pos);

		pos=m_file[1]->GetDesPos();
		pos.y=80;
		m_file[1]->SetDesPos(pos);

		pos=m_file[2]->GetDesPos();
		pos.y=80;
		m_file[2]->SetDesPos(pos);

		pos=m_file[3]->GetDesPos();
		pos.y=50;
		m_file[3]->SetDesPos(pos);

		pos=m_file[4]->GetDesPos();
		pos.y=80;
		m_file[4]->SetDesPos(pos);

		pos=m_file[5]->GetDesPos();
		pos.y=80;
		m_file[5]->SetDesPos(pos);

		m_count++;
		if(m_saveNum1==1&&m_count==7)
		{
			m_file[0]->Update();
			m_count=0;
		}
		else if(m_saveNum1==2&&m_count==7)
		{
			m_file[3]->Update();
			m_count=0;
		}
		if (m_count == 7)
			m_count = 0;
		break;
	case  eFILE_TWO:
		pos = m_pFile2->GetDesPos();
		pos.y = 50;
		m_pFile2->SetDesPos(pos);
		m_pFile2->SetCurFrame(1);

		pos = m_pFile1->GetDesPos();
		pos.y = 80;
		m_pFile1->SetDesPos(pos);
		m_pFile1->SetCurFrame(0);

		pos = m_pFile3->GetDesPos();
		pos.y = 80;
		m_pFile3->SetDesPos(pos);
		m_pFile3->SetCurFrame(0);

		m_pDelete->SetCurFrame(0);

		pos=m_file[0]->GetDesPos();
		pos.y=80;
		m_file[0]->SetDesPos(pos);

		pos=m_file[1]->GetDesPos();
		pos.y=50;
		m_file[1]->SetDesPos(pos);

		pos=m_file[2]->GetDesPos();
		pos.y=80;
		m_file[2]->SetDesPos(pos);

		pos=m_file[3]->GetDesPos();
		pos.y=80;
		m_file[3]->SetDesPos(pos);

		pos=m_file[4]->GetDesPos();
		pos.y=50;
		m_file[4]->SetDesPos(pos);

		pos=m_file[5]->GetDesPos();
		pos.y=80;
		m_file[5]->SetDesPos(pos);

		m_count++;
		if(m_saveNum2==1&&m_count==7)
		{
			m_file[1]->Update();
			m_count=0;
		}
		else if(m_saveNum2==2&&m_count==7)
		{
			m_file[4]->Update();
			m_count=0;
		}
		if (m_count == 7)
			m_count = 0;
		break;
	case  eFILE_THREE:
		pos = m_pFile3->GetDesPos();
		pos.y = 50;
		m_pFile3->SetDesPos(pos);
		m_pFile3->SetCurFrame(1);

		pos = m_pFile2->GetDesPos();
		pos.y = 80;
		m_pFile2->SetDesPos(pos);
		m_pFile2->SetCurFrame(0);

		pos = m_pFile1->GetDesPos();
		pos.y = 80;
		m_pFile1->SetDesPos(pos);
		m_pFile1->SetCurFrame(0);

		m_pDelete->SetCurFrame(0);

		pos=m_file[0]->GetDesPos();
		pos.y=80;
		m_file[0]->SetDesPos(pos);

		pos=m_file[1]->GetDesPos();
		pos.y=80;
		m_file[1]->SetDesPos(pos);

		pos=m_file[2]->GetDesPos();
		pos.y=50;
		m_file[2]->SetDesPos(pos);

		pos=m_file[3]->GetDesPos();
		pos.y=80;
		m_file[3]->SetDesPos(pos);

		pos=m_file[4]->GetDesPos();
		pos.y=80;
		m_file[4]->SetDesPos(pos);

		pos=m_file[5]->GetDesPos();
		pos.y=50;
		m_file[5]->SetDesPos(pos);

		m_count++;
		if(m_saveNum3==1&&m_count==7)
		{
			m_file[2]->Update();
			m_count=0;
		}
		else if(m_saveNum3==2&&m_count==7)
		{
			m_file[5]->Update();
			m_count=0;
		}
		if (m_count == 7)
			m_count = 0;
		break;
	case  eFILE_DELETE:
		m_pDelete->SetCurFrame(1);

		pos = m_pFile2->GetDesPos();
		pos.y = 80;
		m_pFile2->SetDesPos(pos);
		m_pFile2->SetCurFrame(0);

		pos = m_pFile3->GetDesPos();
		pos.y = 80;
		m_pFile3->SetDesPos(pos);
		m_pFile3->SetCurFrame(0);

		pos = m_pFile1->GetDesPos();
		pos.y = 80;
		m_pFile1->SetDesPos(pos);
		m_pFile1->SetCurFrame(0);

		pos=m_file[0]->GetDesPos();
		pos.y=80;
		m_file[0]->SetDesPos(pos);

		pos=m_file[1]->GetDesPos();
		pos.y=80;
		m_file[1]->SetDesPos(pos);

		pos=m_file[2]->GetDesPos();
		pos.y=80;
		m_file[2]->SetDesPos(pos);

		pos=m_file[3]->GetDesPos();
		pos.y=80;
		m_file[3]->SetDesPos(pos);

		pos=m_file[4]->GetDesPos();
		pos.y=80;
		m_file[4]->SetDesPos(pos);

		pos=m_file[5]->GetDesPos();
		pos.y=80;
		m_file[5]->SetDesPos(pos);
		break;
	}
}

void CSelectFile::OnKeyDown(SEvent event)
{
	if (event.keyInput.pressedDown)
	{
		switch (event.keyInput.key)
		{
		case VK_UP :
			m_select = eFILE_TWO;
			break;
		case VK_DOWN:
			m_select = eFILE_DELETE;
			break;
		case VK_LEFT:
			if (m_select != 4)
			{
				m_select -= 1;
				if (m_select == 0)
					m_select = eFILE_THREE;
			}
			break;
		case VK_RIGHT:
			if (m_select != 4)
			{
				m_select += 1;
				if (m_select == 4)
					m_select = eFILE_ONE;
			}
			break;
		case VK_RETURN:
			if (m_pBg->GetDesPos().y == 0&&m_select!=eFILE_DELETE)
			{
				LoadSave();
				CGameManager::GetInstance()->InitFirstStage();
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eNEW_RUN);
				CInputManager::GetInstance()->DeleteKeyListener(_T("SelectFile"));
				CInputManager::GetInstance()->AddKeyListener(_T("NewGame"), CGameManager::GetInstance()->GetNewGame());
			}
			else if (m_pBg->GetDesPos().y == 0 && m_select == eFILE_DELETE)
			{
				DeleteFileW();
			}
			break;
		case VK_ESCAPE:
			if (m_pBg->GetDesPos().y == 0)
			{
				CAudio4Bass::GetInstance()->ChannelPlay(7,false);
				CGameManager::GetInstance()->SetGameState(eSTART_SURFACE);
				CInputManager::GetInstance()->DeleteKeyListener(_T("SelectFile"));
				CInputManager::GetInstance()->AddKeyListener(_T("StartSurface"), CGameManager::GetInstance()->GetStartface());
			}
			break;
		}
	}
}

void CSelectFile::SetIsUp(bool b)
{
	m_bIsUp = b;
}

void CSelectFile::DeleteFileW()
{
	m_save = 0;
	FILE *file;
	fopen_s(&file, "file1.bin", "wb+");
	fwrite(&m_save, sizeof(int), 1, file);
	fclose(file);

	fopen_s(&file, "file2.bin", "wb+");
	fwrite(&m_save, sizeof(int), 1, file);
	fclose(file);

	fopen_s(&file, "file3.bin", "wb+");
	fwrite(&m_save, sizeof(int), 1, file);
	fclose(file);

}

void CSelectFile::Save()
{
	FILE *file;
//	m_save=0;
	if(CGameManager::GetInstance()->GetFirstStage()->GetFlyDuke()!=nullptr
		&&CGameManager::GetInstance()->GetFirstStage()->GetBossHp()<=0)
	{
		switch (m_select)
		{
		case eFILE_ONE:
			if(m_saveNum1!=2)
				m_save=1;
			break;
		case eFILE_TWO:
			if(m_saveNum2!=2)
				m_save=1;
			break;
		case eFILE_THREE:
			if(m_saveNum3!=2)
				m_save=1;
			break;
		}
	}
	if (CGameManager::GetInstance()->GetFirstStage()->GetMatherHeart() != nullptr
		&&CGameManager::GetInstance()->GetFirstStage()->GetBossHp() <= 0)
	{
		m_save = 2;
	}

	switch (m_select)
	{
	case eFILE_ONE:
		fopen_s(&file, "file1.bin", "wb+");
		fwrite(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	case eFILE_TWO:
		fopen_s(&file, "file2.bin", "wb+");
		fwrite(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	case eFILE_THREE:
		fopen_s(&file, "file3.bin", "wb+");
		fwrite(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	}
}

void CSelectFile::LoadSave()
{
	FILE *file;
	switch (m_select)
	{
	case eFILE_ONE:
		fopen_s(&file, "file1.bin", "rb+");
		fread(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	case eFILE_TWO:
		fopen_s(&file, "file2.bin", "rb+");
		fread(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	case eFILE_THREE:
		fopen_s(&file, "file3.bin", "rb+");
		fread(&m_save, sizeof(int), 1, file);
		fclose(file);
		break;
	}
}

int CSelectFile::GetSaveNum()
{
	return m_save;
}