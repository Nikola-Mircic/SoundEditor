#pragma once

#include "wx/wx.h"
#include "Window.h"

class SoundEditor : public wxApp
{
public:
	SoundEditor();
	~SoundEditor();

public:
	Window* window;

	virtual bool OnInit();
};

