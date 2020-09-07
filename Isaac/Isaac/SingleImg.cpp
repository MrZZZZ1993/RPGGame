#include "stdafx.h"
#include "SingleImg.h"


CSingleImg::CSingleImg()
{
	m_pPic = nullptr;
	m_countRow = 0;
	m_curRow = 0;
	m_countFrame = 0;
	m_curFrame = 0;
	m_frameHeight = 0;
	m_frameWidth = 0;
	m_startFrame=0;
	m_startRow=0;
	m_endFrame=0;
	m_endRow=0;
}

CSingleImg::~CSingleImg()
{
	delete m_pPic;
}

void CSingleImg::Init()
{
	m_pPic = new CPicture;
	SetColRef(NULL);
	m_pPic->Init(GetPath(), GetColRef());
	m_frameWidth = m_pPic->GetPicWidth() / m_countFrame;
	m_frameHeight = m_pPic->GetPicHeight() / m_countRow;
}

void CSingleImg::Draw()
{
	m_pPic->Draw(GetSrcPos(), GetDesPos(), GetShowWidth(), GetShowHeight(), matMatrix, m_center,m_transparent,m_addColor);
}

void CSingleImg::Update()
{
	if (m_startFrame<m_endFrame)
	{
		if (m_curFrame == m_endFrame)
		{
			m_curFrame = m_startFrame;
			if (m_startRow<m_endRow)
			m_curRow = (m_curRow == m_endRow ? m_startRow : m_curRow + 1);
			else
				m_curRow = (m_curRow == m_endRow ? m_startRow : m_curRow - 1);
		}
		else
			m_curFrame++;
	}
	else
	if (m_curFrame == m_endFrame)
	{
		m_curFrame = m_startFrame;
		if (m_startRow<m_endRow)
		m_curRow = (m_curRow == m_endRow ? m_startRow : m_curRow + 1);
		else
			m_curRow = (m_curRow == m_endRow ? m_startRow : m_curRow - 1);
	}
	else
		m_curFrame--;
	POINT pos;
	pos.x = m_curFrame*m_frameWidth;
	pos.y = m_curRow*m_frameHeight;
	SetSrcPos(pos);
}

void CSingleImg::SetCountFrame(WORD countFrame)
{
	m_countFrame = countFrame;
}

void CSingleImg::SetCurFrame(WORD curFrame)
{
	m_curFrame = curFrame;
}

void CSingleImg::SetCountRow(WORD countRow)
{
	m_countRow = countRow;
}

void CSingleImg::SetCurRow(WORD curRow)
{
	m_curRow = curRow;
}

void CSingleImg::UpdateSrcPos(WORD curFrame,WORD curRow)
{
	POINT pos;
	pos.x = curFrame*m_frameWidth;
	pos.y = curRow*m_frameHeight;
	SetSrcPos(pos);
}

void CSingleImg::ReSet(WORD curFrame, WORD curRow, WORD startFrame, WORD endFrame, WORD startRow, WORD endRow)
{
	SetCurFrame(curFrame);
	SetCurRow(curRow);
	SetStartFrame(startFrame);
	SetEndFrame(endFrame);
	SetStartRow(startRow);
	SetEndRow(endRow);
}

WORD CSingleImg::GetCountFame()
{
	return m_countFrame;
}

WORD CSingleImg::GetCurFrame()
{
	return m_curFrame;
}

WORD CSingleImg::GetCountRow()
{
	return m_countRow;
}

WORD CSingleImg::GetCurRow()
{
	return m_curRow;
}

WORD CSingleImg::GetFrameHeight()
{
	return m_frameHeight;
}

WORD CSingleImg::GetFrameWidth()
{
	return m_frameWidth;
}

void CSingleImg::SetStartRow(WORD startRow)
{
	m_startRow=startRow;
}

void  CSingleImg::SetStartFrame(WORD startFrame)
{
	m_startFrame=startFrame;
}

void  CSingleImg::SetEndFrame(WORD endFrame)
{
	m_endFrame=endFrame;
}

void  CSingleImg::SetEndRow(WORD endRow)
{
	m_endRow=endRow;
}

DWORD CSingleImg::GetColorValue(POINT pos)
{
	return m_pPic->GetColorValue(pos);
}

WORD CSingleImg::GetPicWidth()
{
	return m_pPic->GetPicWidth();
}

WORD CSingleImg::GetPicHeight()
{
	return m_pPic->GetPicHeight();
}