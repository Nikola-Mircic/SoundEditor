#include "SoundEditor.h"

#include "Window.h"

wxBEGIN_EVENT_TABLE(Window, wxFrame)
    EVT_MENU(wxID_EXIT, Window::OnExit)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(SoundEditor);

bool SoundEditor::OnInit()
{
    this->window = new Window();
    this->window->Show(true);
    return true;
}

