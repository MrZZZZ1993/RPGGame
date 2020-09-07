#include "stdafx.h"
#include "Picture.h"


CPicture::CPicture()
{
	m_pTexture = nullptr;
	m_pSprite = nullptr;
	m_picWidth = 0;
	m_picHeight = 0;
	m_colRef = 0xffffff;
}

CPicture::~CPicture()
{
	m_pSprite->Release();
	m_pTexture->Release();
}

void CPicture::Init(TSTRING path, COLORREF color)
{
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)CPlatform::GetInstance()->GetPlatData(_T("pDev"));
	if (FAILED(D3DXCreateTextureFromFileEx(pDev, path.c_str(), D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,color, 0, 0, &m_pTexture)))
		return;
	D3DSURFACE_DESC desc;
	m_pTexture->GetLevelDesc(0, &desc);
	m_picHeight = desc.Height;
	m_picWidth = desc.Width;
	D3DXCreateSprite(pDev, &m_pSprite);
}

void CPicture::Draw(POINT srcPos, POINT desPos, WORD width, WORD height, D3DXMATRIX matMatrix, D3DXVECTOR3 m_center,long color,long aColor)
{
	m_pSprite->SetTransform(&matMatrix);


	RECT rect = { srcPos.x, srcPos.y, srcPos.x + width, srcPos.y + height };
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->Draw(m_pTexture, &rect, &m_center, &D3DXVECTOR3(desPos.x, desPos.y, 0), color+aColor);
	m_pSprite->End();
}

void CPicture::SetColRef(COLORREF color)
{
	m_colRef = color;
}

void CPicture::SetPicWidth(WORD width)
{
	m_picWidth=width;
}

void CPicture::SetPicHeight(WORD height)
{
	m_picHeight=height;
}

WORD CPicture::GetPicHeight()
{
	return m_picHeight;
}

WORD CPicture::GetPicWidth()
{
	return m_picWidth;
}

COLORREF CPicture::GetColRef()
{
	return m_colRef;
}

DWORD CPicture::GetColorValue(POINT pos)
{
	D3DLOCKED_RECT pValue;
	m_pTexture->LockRect(0, &pValue, NULL, 0);

	DWORD color;
	DWORD *pColor = (DWORD*)pValue.pBits;
	color = *(pColor + pos.x + pos.y*pValue.Pitch / 4);

	m_pTexture->UnlockRect(0);
	return color;
}