#pragma once
class CPoolManager:public CKeyListener
{
public:
	CPoolManager();
	~CPoolManager();
	void Init(TSTRING);
	void InitBulletPath();
	void InitBulletPath1();
	void Render();
	void Move(Map*,int,int);
	void SetPath();
	void SetPath1();
	void PathMove();
	void Refresh();
	void Update();
	void OnKeyDown(SEvent);
	void OnKeyUp(SEvent);
	void Fire(int);
	void SetRate(int);
	void MoveOnMap();
	void SetDirOnMap(int);
	void SetDamage(int);
	void SetFalse();
	void UpdateBullet();
	void SetSpeed(int);
	void SetIsBomb(bool);
	bool GetIsBomb();
	int GetDamage();
	DWORD GetColorValue(POINT);
	vector<CBullet*>::iterator GetBulletPoolBegin();
	vector<CBullet*>::iterator GetBulletPoolEnd();
	vector<CBullet*>GetBulletPool();
private:
	CBullet *m_pBullet;
	vector<CBullet*>m_bulletPool;
	WORD m_count;
	int m_rate;
	int m_dirOnMap;
	int m_dir;
	int m_bulletFireCount;
	int m_bulletFireCount1;
	bool IsFire;
	bool m_isBomb;
	int m_damage;
	vector<D3DXVECTOR2>m_bulletPath;
	vector<D3DXVECTOR2>m_bulletPath1;
};