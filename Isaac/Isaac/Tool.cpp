#include "stdafx.h"
#include "Tool.h"


CTool::CTool(void)
{
}

CTool::~CTool(void)
{
}

wchar_t* CTool::CU_A2U(const char* c)
{
	wchar_t* m_wchar = NULL;
	int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0); 
	m_wchar=new wchar_t[len+1]; 
	MultiByteToWideChar(CP_ACP,0,c,strlen(c),m_wchar,len); 
	m_wchar[len]='\0'; 
	return m_wchar; 
}

char* CTool::CU_U2A(const wchar_t* wc)
{
	char *m_char =NULL;
	int len= WideCharToMultiByte(CP_ACP,0,wc,wcslen(wc),NULL,0,NULL,NULL); 
	m_char=new char[len+1]; 
	WideCharToMultiByte(CP_ACP,0,wc,wcslen(wc),m_char,len,NULL,NULL); 
	m_char[len]='\0'; 
	return m_char; 
}

void CTool::StaticImg(TiXmlDocument *document, int imgType, string name, string path, int r, int g, int b)
{
	TiXmlElement *element = new TiXmlElement("STATICIMAGE");
	element->SetAttribute("imgType" , imgType);
	element->SetAttribute("name",name.c_str());
	element->SetAttribute("path",path.c_str());  
	element->SetAttribute("colorR",r); 
	element->SetAttribute("colorG",g); 
	element->SetAttribute("colorB",b); 
	document->LinkEndChild(element);
}

void CTool::SingleImg(TiXmlDocument *document,  int imgType, string name, string path, int countFrame, int countDir, int r, int g, int b)
{
	TiXmlElement *element = new TiXmlElement("SINGLEIMAGE");
	element->SetAttribute("imgType" , imgType);
	element->SetAttribute("name",name.c_str());
	element->SetAttribute("path",path.c_str());  
	element->SetAttribute("countFrame",countFrame);  
	element->SetAttribute("countDir",countDir);  
	element->SetAttribute("colorR",r); 
	element->SetAttribute("colorG",g); 
	element->SetAttribute("colorB",b); 
	document->LinkEndChild(element);
}

void CTool::MulImg(TiXmlDocument *document,  int imgType, string *name, string *path, int countFrame, int r, int g, int b)
{
	TiXmlElement *element = new TiXmlElement("MULIMAGE");
	element->SetAttribute("imgType" , imgType);
	element->SetAttribute("countFrame",countFrame);  
	element->SetAttribute("colorR",r); 
	element->SetAttribute("colorG",g); 
	element->SetAttribute("colorB",b); 
	for (int i = 0;i<countFrame;i++)
	{
		TiXmlElement *childElement = new TiXmlElement("child");
		childElement->SetAttribute("name",name[i].c_str());
		childElement->SetAttribute("path",path[i].c_str());
		element->LinkEndChild(childElement);
	}
	document->LinkEndChild(element);
}

void CTool::ComputeLine(Line *line,D3DXVECTOR2  pos1,D3DXVECTOR2  pos2)
{
	D3DXVECTOR2 vec;
	vec = pos2 - pos1;
	D3DXVECTOR2 normalVec;
	D3DXVec2Normalize(&normalVec, &vec);
	D3DXVECTOR2 p1To0;
	p1To0=-pos1;
	D3DXVECTOR2 verLine = D3DXVec2Dot(&normalVec, &p1To0)*normalVec + pos1;

	line->fDistance = D3DXVec2Length(&verLine);
	D3DXVec2Normalize(&line->vNormal, &verLine);
}

float CTool::DistancePointToLine(D3DXVECTOR2* vPoint, Line* line)
{
	int a = D3DXVec2Dot(vPoint, &line->vNormal) - line->fDistance;
	return D3DXVec2Dot(vPoint, &line->vNormal) - line->fDistance;
}

D3DXVECTOR2 CTool::MinDistancePointToLine(D3DXVECTOR2* vInput, Line* line)
{
	return *vInput - line->vNormal * DistancePointToLine(vInput, line);
}

void CTool::Vector2Reflect(D3DXVECTOR2* vOutput, D3DXVECTOR2* vReflect, D3DXVECTOR2* vInput)
{
	D3DXVECTOR2 vReflectTmp;
	D3DXVec2Normalize(&vReflectTmp, vReflect);
	float dot = D3DXVec2Dot(vInput, &vReflectTmp);
	vReflectTmp = vReflectTmp * dot * 2;
	vOutput->x = vInput->x - vReflectTmp.x;
	vOutput->y = vInput->y- vReflectTmp.y;
}