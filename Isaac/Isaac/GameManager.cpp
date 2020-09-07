#include "stdafx.h"
#include "GameManager.h"


CGameManager::CGameManager()
{
	m_pStartSurface = nullptr;
	m_pSelectFile = nullptr;
	m_gameState = eNONE_START;
	m_pNewGame = nullptr;
	m_pShadow=nullptr;
	m_pSelectPlayer = nullptr;
	m_pTransition = nullptr;
}

CGameManager::~CGameManager()
{
	delete m_pSelectFile;
	delete m_pNewGame;
	delete m_pShadow;
	delete m_pSelectPlayer;
	delete m_pTransition;
	delete m_pFirst;
	delete m_pStartSurface;
}

void CGameManager::Init(HWND &hWnd)
{
	LPDIRECT3D9 pD3D = nullptr;
	LPDIRECT3DDEVICE9 pDev = nullptr;
	RECT *rect=new RECT;
	GetClientRect(hWnd, rect);
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDev);
	CPlatform::GetInstance()->AddPlatData(_T("pDev"), pDev);
	CPlatform::GetInstance()->AddPlatData(_T("rect"), rect);
	CPlatform::GetInstance()->AddPlatData(_T("hWnd"), hWnd);

	CResManager::GetInstance()->LoadResFromFile(_T("game.xml"));
	InitStartSurface();
	InitSelectFile();
	InitNewGame();
	InitShadow();
	m_pShadow->UpdateMAatrix();
	InitSelectPlayer();
	InitTransition();
	m_gameState = eSTART_SURFACE;
	CAudio4Bass::GetInstance()->Initialize();
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/start.ogg", BASS_SAMPLE_LOOP);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/play.ogg", BASS_SAMPLE_LOOP);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/bossRoom.ogg", BASS_SAMPLE_LOOP);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/behurt.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/die.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/explode.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/monsterDie.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/21.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/fire.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/fly.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/bulletExplode.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/bob.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/money.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->LoadFile("../bin/music/goods.wav", BASS_SAMPLE_MONO);
	CAudio4Bass::GetInstance()->ChannelPlay(0, true);
}

void CGameManager::Render()
{
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)CPlatform::GetInstance()->GetPlatData(_T("pDev"));
	pDev->Clear(NULL, NULL, D3DCLEAR_TARGET, 0xffffffff, 0, NULL);
	pDev->BeginScene();

	switch (m_gameState)
	{
	case eSTART_SURFACE:
		m_pSelectFile->Draw();
		m_pStartSurface->Draw();
		m_pShadow->Draw();
		break;
	case eSELECT_FILE:
		m_pSelectFile->Draw();
		m_pStartSurface->Draw();
		m_pNewGame->Draw();
		m_pShadow->Draw();
		break;
	case eNEW_RUN:
		m_pSelectFile->Draw();
		m_pSelectPlayer->Draw();
		m_pNewGame->Draw();
		m_pShadow->Draw();
		break;
	case eSELECT_PLAYER:
		m_pNewGame->Draw();
		m_pSelectPlayer->Draw();
		m_pShadow->Draw();
		m_pTransition->Draw();
		break;
	case eGAME_PLAY:
		m_pFirst->Draw();
		m_pTransition->Draw();
		break;
	}

	pDev->EndScene();
	pDev->Present(NULL, NULL, NULL, NULL);
}

void CGameManager::Update()
{
	switch (m_gameState)
	{
	case eSTART_SURFACE:
		m_pStartSurface->Update();
		m_pSelectFile->Update();
		break;
	case eSELECT_FILE:
		m_pStartSurface->Update();
		m_pSelectFile->Update();
		m_pNewGame->Update();
		break;
	case eNEW_RUN:
		m_pSelectFile->Update();
		m_pNewGame->Update();
		m_pSelectPlayer->Update();
		break;
	case eSELECT_PLAYER:
		m_pNewGame->Update();
		m_pSelectPlayer->Update();
		m_pTransition->Update();
		break;
	case eGAME_PLAY:
		m_pTransition->Update();
		m_pFirst->FlyMonsterMove(m_pFirst->GetMap(1));
		m_pFirst->Update();
		m_pFirst->Move();
		m_pFirst->MapChange();
		m_pFirst->MapMove();
		m_pFirst->Collision();
	}
}

void CGameManager::InitTransition()
{
	m_pTransition = new CTransition;
	m_pTransition->Init();
}

void CGameManager::InitShadow()
{
	m_pShadow = (CStaticImg *)CResManager::GetInstance()->GetRes(_T("shadow"));
	m_pShadow->Init();
	m_pShadow->SetShowWidth(832);
	m_pShadow->SetShowHeight(576);
}

void CGameManager::InitStartSurface()
{
	m_pStartSurface = new CStartSurface;
	m_pStartSurface->Init();
	CInputManager::GetInstance()->AddKeyListener(_T("StartSurface"), m_pStartSurface);
}

void CGameManager::InitSelectFile()
{
	m_pSelectFile = new CSelectFile;
	m_pSelectFile->Init();
}

void CGameManager::InitNewGame()
{
	m_pNewGame = new CNewGame;
	m_pNewGame->Init();
}

void CGameManager::InitSelectPlayer()
{
	m_pSelectPlayer = new CSelectPlayer;
	m_pSelectPlayer->Init();
}

void CGameManager::InitFirstStage()
{
	FILE *file;
	int i = 1;
	fopen_s(&file, "FileNum.bin", "rb+");
	fread(&i, sizeof(int), 1, file);
	fclose(file);

	i++;
	if (i == 3)
		i = 1;
	fopen_s(&file, "FileNum.bin", "wb+");
	fwrite(&i, sizeof(char), 1, file);
	fclose(file);


	TSTRING fileName;
	m_pFirst=new CStage;

	switch(i)
	{
	case 1:
		fileName=_T("First-1.xml");
		break;
	case 2:
		fileName=_T("First.xml");
		break;
	}

	m_pSelectFile->LoadSave();
	if(m_pSelectFile->GetSaveNum()==0)
	{
		m_pFirst->readFromFile(_T("First.xml"));
		m_pFirst->SetGoodsCount(2);
	}
	else if (m_pSelectFile->GetSaveNum() == 1 || m_pSelectFile->GetSaveNum() == 2)
	{
		m_pFirst->readFromFile(fileName);
		if (m_pSelectFile->GetSaveNum() == 1)
			m_pFirst->SetGoodsCount(4);
		else if (m_pSelectFile->GetSaveNum() == 2)
			m_pFirst->SetGoodsCount(5);
	}
	m_pFirst->SelectGoods();
	m_pFirst->InitCollision();
}

void CGameManager::WinProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	CInputManager::GetInstance()->WinProc(msg,wParam,lParam);
}

void CGameManager::SetGameState(GAME_STATE gameState)
{
	m_gameState = gameState;
}

GAME_STATE CGameManager::GetGameState()
{
	return m_gameState;
}

CSelectFile*CGameManager::GetSelectFile()
{
	return m_pSelectFile;
}

CStartSurface*CGameManager::GetStartface()
{
	return m_pStartSurface;
}

CNewGame*CGameManager::GetNewGame()
{
	return m_pNewGame;
}

CSelectPlayer*CGameManager::GetSelectPlayer()
{
	return m_pSelectPlayer;
}

CTransition*CGameManager::GetTransition()
{
	return m_pTransition;
}

CStage*CGameManager::GetFirstStage()
{
	return m_pFirst;
}

CStaticImg*CGameManager::GetShadow()
{
	return m_pShadow;
}