#pragma once
class CGameManager:public CSingleton<CGameManager>
{
public:
	CGameManager();
	~CGameManager();
	void Init(HWND&);
	void Render();
	void Update();
	void InitTransition();
	void InitShadow();
	void InitStartSurface();
	void InitSelectFile();
	void InitNewGame();
	void InitSelectPlayer();
	void InitFirstStage();
	void WinProc(UINT,WPARAM,LPARAM);
	void SetGameState(GAME_STATE);
	GAME_STATE GetGameState();
	CSelectFile*GetSelectFile();
	CStartSurface*GetStartface();
	CNewGame*GetNewGame();
	CSelectPlayer*GetSelectPlayer();
	CTransition*GetTransition();
	CStage*GetFirstStage();
	CStaticImg*GetShadow();
private:
	CStartSurface*m_pStartSurface;
	CSelectFile*m_pSelectFile;
	GAME_STATE m_gameState;
	CNewGame*m_pNewGame;
	CSelectPlayer*m_pSelectPlayer;
	CStaticImg*m_pShadow;
	CTransition*m_pTransition;
	CStage*m_pFirst;
};

