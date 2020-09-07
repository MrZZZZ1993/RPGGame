#pragma once

class CMouseListener
{
public:
	virtual void OnMouseDown(SEvent){}
	virtual void OnMouseUp(SEvent){}
	virtual void OnMouseMove(SEvent){}
	virtual void OnMouseWheel(SEvent){}
};

class CKeyListener
{
public:
	virtual void OnKeyDown(SEvent) = 0;
	virtual void OnKeyUp(SEvent){}
};