#pragma once
#include<windows.h>
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
using namespace std;

struct Line
{
	D3DXVECTOR2 vNormal;
	float fDistance;
};

class CTool
{
public:
	CTool();
	~CTool();
	static wchar_t* CU_A2U(const char* c);
	static char* CU_U2A(const wchar_t* wc);
	static void StaticImg(TiXmlDocument *document,  int imgType, string name, string  path, int r, int g, int b); //静态图片
	static void SingleImg(TiXmlDocument *document,  int imgType, string  name, string  path, int countFrame, int countDir, int r, int g, int b);  //单张多帧
	static void MulImg(TiXmlDocument *document, int imgType, string  *name, string *path, int countFrame, int r, int g, int b); //多张多帧
	static void ComputeLine(Line *line,D3DXVECTOR2  pos1,D3DXVECTOR2  pos2);
	static float DistancePointToLine(D3DXVECTOR2* vPoint, Line* line);
	static D3DXVECTOR2 MinDistancePointToLine(D3DXVECTOR2* vInput, Line* line);
	static void Vector2Reflect(D3DXVECTOR2* vOutput, D3DXVECTOR2* vReflect, D3DXVECTOR2* vInput);
};

