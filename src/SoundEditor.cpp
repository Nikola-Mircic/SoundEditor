#include "SoundEditor.h"

IMPLEMENT_APP(SoundEditor);

SoundEditor::SoundEditor()
{
	/*
	wxFULLSCREEN_NOMENUBAR
	wxFULLSCREEN_NOTOOLBAR
	wxFULLSCREEN_NOSTATUSBAR
	*/

	window = new Window();
}

SoundEditor::~SoundEditor()
{

}

bool SoundEditor::OnInit() {
	window->Show();



	return true;
}