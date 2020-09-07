// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#include "bass.h"
#include"Audio4Bass.h"
#pragma comment(lib,"bass.lib")
#include <iostream>
using namespace std;
#include <time.h>
#include <map>
#include <vector>
#include "Tool.h"
//#pragma comment(lib,"ConsoleApplication1.lib")
#include "tinystr.h"
#include "tinyxml.h"
#include  "math.h"
// TODO:  在此处引用程序需要的其他头文件
#include "Macro.h"
#include"Node.h"
#include"AStar.h"
#include "Singleton.h"
#include "Platform.h"
#include "Res.h"
#include "Picture.h"
#include "StaticImg.h"
#include "SingleImg.h"
#include "MulImg.h"
#include "ResManager.h"
#include "SEvent.h"
#include "Listener.h"
#include "InputManager.h"
#include "Map.h"
#include "Player.h"
#include "PlayerHead.h"
#include "PlayerBody.h"
#include "SelectFile.h"
#include "StartSurface.h"
#include "SelectPlayer.h"
#include "NewGame.h"
#include "Bullet.h"
#include "BulletPoolManager.h"
#include "Building.h"
#include "Feces.h"
#include "Fly.h"
#include "FlyMonster.h"
#include"Transition.h"
#include"Fire.h"
#include "Door.h"
#include"FlyDuke.h"
#include "Guide.h"
#include "Heart.h"
#include "BombExplode.h"
#include"Tile.h"
#include"Mask.h"
#include"MaskHeart.h"
#include"Bob.h"
#include "MonsterDead.h"
#include"FeceMonster.h"
#include"MatherHeart.h"
#include "End.h"
#include"Goods.h"
#include"Mushroom.h"
#include"Plat.h"
#include "Shoe.h"
#include "Eye.h"
#include "Bomb.h"
#include "Leg.h"
#include"Angel.h"
#include "HP.h"
#include "Money.h"
#include "Stage.h"
#include "GameManager.h"
