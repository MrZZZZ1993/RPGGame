#include "stdafx.h"
#include "Res.h"


CRes::CRes()
{
	POINT pos = { 0, 0 };
	m_srcPos = pos;
	m_desPos = pos;
	m_showWidth = 0;
	m_showHeight = 0;
	m_name = _T("");
	m_path = _T("");
	m_colRef = RGB(255, 255, 255)|(RGB(255, 255, 255)<<8);
	m_xScale = 1;
	m_yScale = 1;
	m_angle = 0;
	m_center.x = 0;
	m_center.y = 0;
	m_center.z = 0;
	m_moveX = 0;
	m_moveY = 0;
	m_transparent = 0xff000000;
	m_addColor = 0xffffff;
}

CRes::~CRes()
{
}

void CRes::SetColRef(COLORREF color)
{
	m_colRef = color;
}

void CRes::SetDesPos(POINT desPos)
{
	m_desPos = desPos;
}

void CRes::SetSrcPos(POINT srcPos)
{
	m_srcPos = srcPos;
}

void CRes::SetName(TSTRING name)
{
	m_name = name;
}

void CRes::SetPath(TSTRING path)
{
	m_path = path;
}

void CRes::SetShowHeight(WORD height)
{
	m_showHeight = height;
}

void CRes::SetShowWidth(WORD width)
{
	m_showWidth = width;
}

void CRes::SetTrasparent(long transparent)
{
	m_transparent = transparent;
}

void CRes::UpdateMAatrix()
{
	D3DXMatrixScaling(&scaleMatrix, m_xScale, m_yScale, 0);
	D3DXMatrixRotationZ(&rotateMatrix, m_angle);
	D3DXMatrixTranslation(&transMatrix, m_moveX, m_moveY, 0);
	D3DXMatrixMultiply(&matMatrix, &scaleMatrix, &rotateMatrix);
	D3DXMatrixMultiply(&matMatrix, &matMatrix, &transMatrix);
}

void CRes::SetCenter(int x, int y)
{
	m_center.x = x;
	m_center.y = y;
}

void CRes::SetMove(int x, int y)
{
	m_moveX = x;
	m_moveY = y;
}

void CRes::SetAngle(float angle)
{
	m_angle = angle;
}

void CRes::SetXScale(float xScale)
{
	m_xScale = xScale;
}

void CRes::SetYScale(float yScale)
{
	m_yScale = yScale;
}

void CRes::SetAddColor(long color)
{
	m_addColor = color;
}

WORD CRes::GetShowHeight()
{
	return m_showHeight;
}

WORD CRes::GetShowWidth()
{
	return m_showWidth;
}

TSTRING CRes::GetName()
{
	return m_name;
}

TSTRING CRes::GetPath()
{
	return m_path;
}

POINT CRes::GetDesPos()
{
	return m_desPos;
}

POINT CRes::GetSrcPos()
{
	return m_srcPos;
}

COLORREF CRes::GetColRef()
{
	return m_colRef;
}

long CRes::GetAddColor()
{
	return m_addColor;
}