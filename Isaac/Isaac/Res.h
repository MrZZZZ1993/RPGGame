#pragma once
class CRes
{
public:
	CRes();
	~CRes();
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update(){};
	void UpdateMAatrix();
	void SetXScale(float);
	void SetYScale(float);
	void SetAngle(float);
	void SetCenter(int, int);
	void SetMove(int, int);
	void SetSrcPos(POINT);
	void SetDesPos(POINT);
	void SetShowWidth(WORD);
	void SetShowHeight(WORD);
	void SetName(TSTRING);
	void SetPath(TSTRING);
	void SetColRef(COLORREF);
	void SetTrasparent(long);
	void SetAddColor(long);
	long GetAddColor();
	POINT GetSrcPos();
	POINT GetDesPos();
	WORD GetShowWidth();
	WORD GetShowHeight();
	TSTRING GetName();
	TSTRING GetPath();
	COLORREF GetColRef();
protected:
	POINT m_srcPos;
	POINT m_desPos;
	WORD m_showWidth;
	WORD m_showHeight;
	TSTRING m_name;
	TSTRING m_path;
	COLORREF m_colRef;
	D3DXVECTOR3 m_center;
	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotateMatrix;
	D3DXMATRIX transMatrix;
	D3DXMATRIX matMatrix;
	float m_xScale;
	float m_yScale;
	float m_angle;
	int m_moveX;
	int m_moveY;
	long m_transparent;
	long m_addColor;
};

