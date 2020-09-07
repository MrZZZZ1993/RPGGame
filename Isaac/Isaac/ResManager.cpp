#include "stdafx.h"
#include "ResManager.h"


CResManager::CResManager()
{
}

CResManager::~CResManager()
{
	map<TSTRING, CRes*>::iterator it = m_res.begin();
	for (; it != m_res.end(); it++)
		delete it->second;
	m_res.clear();
}

void CResManager::LoadResFromFile(TSTRING fileName)
{
#ifdef UNICODE
	char*file = CTool::CU_U2A(fileName.c_str());
#else
	const char*file=fileName.c_str();
#endif
	TiXmlDocument *doc = new TiXmlDocument(file);
	doc->LoadFile();
	TiXmlElement*element = doc->FirstChildElement();
	while (element)
	{
		int imgType;
		element->Attribute("imgType", &imgType);
		switch ((IMG_TYPE)imgType)
		{
		case eSTATIC_IMG:
		{
#ifdef UNICODE
							wchar_t*name, *path;
							name = CTool::CU_A2U(element->Attribute("name"));
							path = CTool::CU_A2U(element->Attribute("path"));
#else
							const char*name = element->Attribute("name");
							const char*path = element->Attribute("path");
#endif
							CRes*pRes = new CStaticImg;
							pRes->SetName(name);
							pRes->SetPath(path);
							AddRes(name, pRes);
		}
			break;
		case eSINGLE_IMG:
		{
#ifdef UNICODE
							wchar_t*name, *path;
							name = CTool::CU_A2U(element->Attribute("name"));
							path = CTool::CU_A2U(element->Attribute("path"));
#else
							const char*name = element->Attribute("name");
							const char*path = element->Attribute("path");
#endif
							CRes*pRes = new CSingleImg;
							int countFrame;
							int countDir;
							element->Attribute("countFrame", &countFrame);
							element->Attribute("countDir", &countDir);
							pRes->SetName(name);
							pRes->SetPath(path);
							((CSingleImg*)pRes)->SetCountFrame(countFrame);
							((CSingleImg*)pRes)->SetCountRow(countDir);
							AddRes(name, pRes);
		}
			break;
		case eMUL_IMG:
		{
#ifdef UNICODE
						 wchar_t* title;
						 title = CTool::CU_A2U(element->Attribute("title"));
#else
						 const char*title = element->Attribute("title");
#endif
						 CRes *pRes= new CMulImg;
						 int countFrame;
						 element->Attribute("countFrame", &countFrame);
						 pRes->SetName(title);
						 ((CMulImg*)pRes)->SetCountFrame(countFrame);
						 ((CMulImg*)pRes)->InitPath();
						 TiXmlElement*child = element->FirstChildElement();
						 int count = 0;
						 while (child)
						 {
#ifdef UNICODE
							 wchar_t* path;
							 path = CTool::CU_A2U(child->Attribute("path"));
#else
							 const char* path = element->Attribute(" path");
#endif
							 ((CMulImg*)pRes)->SetPath(path, count);
							 count++;
							 child=child->NextSiblingElement();
						 }
						 AddRes(title, pRes);
		}
			break;
		}
	element = element->NextSiblingElement();
	}
}

void CResManager::AddRes(TSTRING name, CRes*res)
{
	m_res[name] = res;
}

CRes*CResManager::GetRes(TSTRING name)
{
	map<TSTRING, CRes*>::iterator it = m_res.find(name);
	if (it != m_res.end())
		return it->second;
	else
		return nullptr;
}
