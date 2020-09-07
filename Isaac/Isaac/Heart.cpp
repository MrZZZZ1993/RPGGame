#include "stdafx.h"
#include "Heart.h"


CHeart::CHeart(void)
{
	m_pPic=nullptr;
}

CHeart::~CHeart(void)
{
	delete m_pPic;
}

void CHeart::Init(TSTRING name)
{
	m_pPic=(CSingleImg*)CResManager::GetInstance()->GetRes(name);
	m_pPic->Init();
	m_pPic->SetShowWidth(m_pPic->GetFrameWidth());
	m_pPic->SetShowHeight(m_pPic->GetFrameHeight());
	m_pPic->UpdateMAatrix();
}

void CHeart::Draw()
{
	m_pPic->SetDesPos(m_desPos);
	m_pPic->SetSrcPos(m_srcPos);
	m_pPic->Draw();
}

void CHeart::SetDesPos(POINT pos)
{
	m_desPos=pos;
}

void CHeart::SetSrcPos(POINT pos)
{
	m_srcPos=pos;
}

int CHeart::GetFrameWidth()
{
	return m_pPic->GetFrameWidth();
}