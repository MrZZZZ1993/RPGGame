#pragma once
#define TSTRING basic_string<TCHAR>

enum IMG_TYPE
{
	eSTATIC_IMG = 0,
	eSINGLE_IMG = 1,
	eMUL_IMG = 2
};

enum GAME_STATE
{
	eNONE_START = 0, 
	eSTART_SURFACE=1,
	eSELECT_FILE=2,
	eNEW_RUN=3,
	eSELECT_PLAYER=4,
	eGAME_PLAY=5
};

enum DIRECTION
{
	eNONE = 0, 
	eUP = 1, 
	eDOWN = 1 << 1, 
	eLEFT = 1 << 2, 
	eRIGHT = 1 << 3 
};

enum STATE
{
	eSTAND=0,
	eWALK = 1,
	eATTACK = 1<<1
};

enum GUIDE_STATE
{
	eCUR=0,
	eGONE=1,
	eN_GONE=2,
	eBOSS=3
};