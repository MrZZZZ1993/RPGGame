#include "stdafx.h"
#include "Guide.h"


CGuide::CGuide()
{
	m_pPic=nullptr;
	m_pFrame=nullptr;
	m_mapIndex=0;
	m_state=2;
}

CGuide::~CGuide(void)
{
	delete m_pPic;
	delete m_pFrame;
}

void CGuide::Init(TSTRING name)
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->UpdateMAatrix();


	POINT pos={690,40};
	m_pFrame=(CSingleImg*)CResManager::GetInstance()->GetRes(_T("guide1"));
	m_pFrame->Init();
	m_pFrame->SetShowWidth(m_pFrame->GetFrameWidth()*4);
	m_pFrame->SetShowHeight(m_pFrame->GetFrameHeight()*3);
	m_pFrame->SetDesPos(pos);
	m_pFrame->UpdateMAatrix();
}

void CGuide::DrawFrame()
{
	m_pFrame->Draw();
}

void CGuide::DrawTile()
{
	m_pPic->SetSrcPos(m_srcPos);
	m_pPic->SetDesPos(m_desPos);
	m_pPic->Draw();
}

void CGuide::SetDesPos(POINT pos)
{
	m_desPos=pos;;
}

void CGuide::SetShowWidth(int width)
{
	m_pPic->SetShowWidth(width);
}

void CGuide::SetShowHeight(int height)
{
	m_pPic->SetShowHeight(height);
}

void CGuide::SetSrcPos(POINT pos)
{
	m_srcPos=pos;
}

void CGuide::SetMapIndex(int i)
{
	m_mapIndex=i;
}

void CGuide::SetState(int i)
{
	m_state=i;
}

int CGuide::GetState()
{
	return m_state;
}

int CGuide::GetMapIndex()
{
	return m_mapIndex;
}

POINT CGuide::GetPos()
{
	return m_desPos;
}