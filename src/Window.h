#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "audio/WAVReader.h"

class Window : public wxFrame
{
public:
    Window();

private:
    WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;

    void OnExit(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Hello = 1
};