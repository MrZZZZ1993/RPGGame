#pragma once
class CSelectPlayer:public CKeyListener
{
public:
	CSelectPlayer();
	~CSelectPlayer();
	void Init();
	void Draw();
	void Update();
	void OnKeyDown(SEvent event);
private:
	CStaticImg*m_pBG;
	CSingleImg*m_pPlayer;
	CSingleImg*m_pArrow;
	CSingleImg*m_pName;
    CStaticImg*m_pHeart;
	CStaticImg*m_pAttack;
	CStaticImg*m_pSpeed;
	CStaticImg*m_pTwo;
	CStaticImg*m_pThree;
	CStaticImg*m_pNone;
	D3DXVECTOR2 m_desPos[5];
	D3DXVECTOR2 m_desPos0;
	D3DXVECTOR2 m_desPos1;
	D3DXVECTOR2 m_desPos2;
	D3DXVECTOR2 m_desPos3;
	D3DXVECTOR2 m_desPos4;
	D3DXVECTOR2 m_line[4];
	int m_posIndex;
	int m_speed;
	int m_BGSpeed;
	int m_dir;
	float m_dis;
	int m_count;
	int m_countName;
	long m_transparent;
	bool m_isChangeName;
};

