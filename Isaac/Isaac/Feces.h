#pragma once
class CFeces:public CBuilding
{
public:
	CFeces();
	~CFeces();
	void IsShoot(vector<CBullet*>,Map*,int,int,int);
private:
	int m_count;
};

