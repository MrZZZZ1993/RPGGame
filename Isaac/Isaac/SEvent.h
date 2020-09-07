#pragma once
enum EVENT_TYPE{
	eEVENT_NONE = 0,
	eEVENT_KEY = 1,
	eEVENT_MOUSE = 2
};

enum EVENT_INPUT_MOUSE{
	eMOUSE_PRESS_LDOWN = 0,
	eMOUSE_PRESS_RDOWN = 1,
	eMOUSE_PRESS_MDOWN = 2,
	eMOUSE_PRESS_LUP = 3,
	eMOUSE_PRESS_RUP = 4,
	eMOUSE_PRESS_MUP = 5,
	eMOUSE_MOVE = 6,
	eMOUSE_WHEEL = 7
};

struct SMouseInput{
	int x;
	int y;
	EVENT_INPUT_MOUSE mouseEvent;
};

struct SKeyInput{
	char key;
	bool pressedDown;
};

struct SEvent{
	EVENT_TYPE eventType;
	union 
	{
		SKeyInput keyInput;
		SMouseInput mouseInput;
	};
};