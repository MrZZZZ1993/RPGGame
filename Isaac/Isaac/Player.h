#pragma once
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	virtual void Init(TSTRING) = 0; 
	virtual void Draw() = 0;
	virtual void Update() = 0;
	void SetPlayerSpeed(WORD);
	void Move(Map*,int,int);
	void ReSet(WORD, WORD, WORD, WORD, WORD, WORD);
	void SetDir(int);
	void SetTop(Map*,int,int);
	void SetBottom(Map*, int, int);
	void SetLeft(Map*, int, int);
	void SetRight(Map*, int, int);
	void SetPos(POINT);
	void SetDesPos(POINT);
	void SetVisible(bool);
	void SetIsRun(bool);
	bool GetVisible();
	WORD GetPlayerSpeed();
	POINT GetPlayerPos();
	int GetPlayerDir();
	bool GetBottom();
	bool GetTop();
	bool GetLeft();
	bool GetRight();
	bool GetIsRun();
	int GetPicWidth();
	int GetPicHeight();
	DWORD GetColorValue(POINT);
protected:
	CSingleImg* m_pPlayer;
	POINT m_playerPos;
	WORD m_playerSpeed;
	int m_playerDir;
	bool m_bIsReset;
	int m_state;
	bool top;
	bool bottom;
	bool left;
	bool right;
	bool m_visible;
	bool m_isRun;
};

