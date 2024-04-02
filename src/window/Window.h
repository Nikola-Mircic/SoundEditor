#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/stattext.h>
#include <wx/filedlg.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "../audio/Player.h"
#include "./panels/Animator.h"
#include "./panels/DataPanel.h"

#define PARENT NULL
#define ID wxID_ANY
#define TITLE "Sound Editor"
#define WINODW_POSITION wxDefaultPosition
#define WINDOW_SIZE wxSize(1000, 700) 
#define WINDOW_STYLE wxDEFAULT_FRAME_STYLE | wxMAXIMIZE

class Window : public wxFrame
{
public:
    Window();
    ~Window();

    void Play(wxCommandEvent& event );
    void Restart(wxCommandEvent& event );
    void Continue(wxCommandEvent& event );
    void Stop(wxCommandEvent& event );
    void LoadFile(wxCommandEvent& event );
private:
    WAVReader* reader = nullptr;
	WAV_FILE* sound = nullptr;

    Player* player;
    Animator* animator;
    DataPanel* dataPanel;

    wxSizer* mainSizer;

    void DrawLayout(WAV_FILE* sound);

    DECLARE_EVENT_TABLE();
};