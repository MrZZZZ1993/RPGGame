#pragma once
class CPicture
{
public:
	CPicture();
	~CPicture();
	void Init(TSTRING, COLORREF);
	void Draw(POINT, POINT, WORD, WORD, D3DXMATRIX, D3DXVECTOR3,long,long);
	void SetColRef(COLORREF);
	COLORREF GetColRef();
	void SetPicWidth(WORD);
	void SetPicHeight(WORD);
	WORD GetPicWidth();
	WORD GetPicHeight();
	DWORD GetColorValue(POINT);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXSPRITE m_pSprite;
	WORD m_picWidth;
	WORD m_picHeight;
	COLORREF m_colRef;
};

