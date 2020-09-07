#include "stdafx.h"
#include "MulImg.h"


CMulImg::CMulImg()
{
	m_countFrame = 0;
	m_curFrame = 0;
}

CMulImg::~CMulImg()
{
	for (int i = 0; i < m_countFrame; i++)
	{
		delete m_pPic[i];
	}
	delete[] m_pPic;
	delete[] m_path;
}

void CMulImg::Init()
{
	m_pPic = new CPicture*[m_countFrame];
	for (int i = 0; i < m_countFrame; i++)
	{
		m_pPic[i] = new CPicture;
		m_pPic[i]->Init(m_path[i],GetColRef());
	}
}

void CMulImg::InitPath()
{
	m_path = new TSTRING[m_countFrame];
}

void CMulImg::Draw()
{
	m_pPic[m_curFrame]->Draw(GetSrcPos(), GetDesPos(), GetShowWidth(), GetShowHeight(), matMatrix, m_center,m_transparent,m_addColor);
}

void CMulImg::Update()
{
	m_curFrame = (m_curFrame == m_countFrame - 1 ? 0 : m_curFrame + 1);
}

void CMulImg::SetPath(TSTRING path, WORD index)
{
	m_path[index] = path;
}

void CMulImg::SetCountFrame(WORD countFrame)
{
	m_countFrame = countFrame;
}

void CMulImg::SetCurFrame(WORD curFrame)
{
	m_curFrame = curFrame;
}

WORD CMulImg::GetCurFrame()
{
	return m_curFrame;
}

WORD CMulImg::GetCountFrame()
{
	return m_countFrame;
}
