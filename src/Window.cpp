#include "Window.h"

#include <iostream>

#define PARENT NULL
#define ID wxID_ANY
#define TITLE "Sound Editor"
#define WINODW_POSITION wxDefaultPosition
#define WINDOW_SIZE wxSize(800, 600) 

Window::Window()
    : wxFrame(PARENT, ID, TITLE, WINODW_POSITION, WINDOW_SIZE)
{
    reader = new WAVReader();
	sound = reader->ReadFileData("/home/nikola/Desktop/Projects/SoundEditor/src/audio/","sample.wav");

    WAV_HEADER* header = sound->header;

    printf("%d \n", header->FMT_num_channels); 
    printf("%d \n", header->FMT_sample_rate); 
    printf("%d \n", header->FMT_byte_rate); 
    printf("%d \n", header->DATA_chunk_size); 
    
	wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 30), wxSize(300, 50));
	text->SetValue(std::to_string(sound->header->DATA_chunk_size));
	wxTextCtrl* text2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 90), wxSize(300, 50));
	text2->SetValue(std::to_string(sound->data->size()));
}

void Window::OnExit(wxCommandEvent &event)
{
   Close(true);
}
