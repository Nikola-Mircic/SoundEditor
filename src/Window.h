#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>
#include <future>

#include <wx/stattext.h>

#include "audio/WAVReader.h"
#include "audio/Player.h"

#define PLAY_BUTTON 0xb1
#define RESTART_BUTTON 0xb2
#define CONTINUE_BUTTON 0xb3
#define STOP_BUTTON 0xb4

#define PARENT NULL
#define ID wxID_ANY
#define TITLE "Sound Editor"
#define WINODW_POSITION wxDefaultPosition
#define WINDOW_SIZE wxSize(1000, 700) 

class Window : public wxFrame
{
public:
    Window();
    ~Window();

    void Play(wxCommandEvent& event );
    void Restart(wxCommandEvent& event );
    void Continue(wxCommandEvent& event );
    void Stop(wxCommandEvent& event );

private:
    WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;

    Player* player;

    void DrawSoundData(WAV_FILE* sound);

    DECLARE_EVENT_TABLE();
};