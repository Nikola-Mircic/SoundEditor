#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/stattext.h>

#include "audio/WAVReader.h"

#include <thread>

#define PLAY_BUTTON 0xb1


void PlaySoundSDL2(const char* FILE_PATH);

class Window : public wxFrame
{
public:
    Window();

    void Play(wxCommandEvent& event );

private:
    WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;

    void DrawSoundData(WAV_FILE* sound);

    DECLARE_EVENT_TABLE();
};