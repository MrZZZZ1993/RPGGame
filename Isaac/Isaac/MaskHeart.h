#pragma once
class CMaskHeart:public CMask
{
public:
	CMaskHeart();
	~CMaskHeart();
	void DrawMaskHeart();
	void DrawHeart();
	void HeartMove();
	void HeartUpdate();
	void MaskHeartUpdateAim(POINT);
	void UpdateHeartRc();
	void UpdateMaskRc();
	void SetIsMask(int);
	void SetNum(int);
	int GetNum();
	int GetIsMask();
	RECT GetHeartRc();
	RECT GetMaskRc();
private:
	RECT m_heartRc;
	RECT m_maskRc;
	int m_isMask;
	int m_num;
};

