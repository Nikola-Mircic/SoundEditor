#include "Window.h"

#define FRAME_PARENT nullptr
#define FRAME_ID wxID_ANY
#define FRAME_TITLE "Sound editor v0.0.1"
#define FRAME_POSITION wxPoint(20, 20)
#define FRAME_SIZE wxSize(800, 600) 
#define FRAME_STYLE wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL

Window::Window() : wxFrame(FRAME_PARENT, FRAME_ID, FRAME_TITLE, FRAME_POSITION, FRAME_SIZE, FRAME_STYLE) {
	reader = new WAVReader();
	sound = reader->ReadFileData("E:/Programing/Projects/SoundEditor/src/audio/","sample.wav");

	wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 30), wxSize(300, 50));
	text->SetValue(std::to_string(sound->header->DATA_chunk_size));
	wxTextCtrl* text2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 90), wxSize(300, 50));
	text2->SetValue(std::to_string(sound->data->size()));

}

Window::~Window() {
	delete reader;
	delete sound;
}