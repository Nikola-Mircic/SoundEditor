#pragma once

#include "wx/wx.h"

#include "audio/WAVReader.h"

class Window : public wxFrame
{
public:
	Window();
	~Window();

private:
	//DrawPanel
	WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;
};

