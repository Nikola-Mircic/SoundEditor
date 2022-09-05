#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>
#include <future>

#include <wx/stattext.h>

#include "audio/WAVReader.h"

#define PLAY_BUTTON 0xb1

#define PARENT NULL
#define ID wxID_ANY
#define TITLE "Sound Editor"
#define WINODW_POSITION wxDefaultPosition
#define WINDOW_SIZE wxSize(1000, 700) 

void PlaySoundSDL2(const char* FILE_PATH);

class Window : public wxFrame
{
public:
    Window();

    void Play(wxCommandEvent& event );

private:
    WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;

    std::future<void> futurePlay;

    void DrawSoundData(WAV_FILE* sound);

    DECLARE_EVENT_TABLE();
};