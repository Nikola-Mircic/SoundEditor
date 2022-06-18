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
    
	wxTextCtrl* RIFF_chunk_ID = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 30), wxSize(300, 50));
	RIFF_chunk_ID->SetValue(std::to_string(sound->header->RIFF_chunk_ID));
	
    wxTextCtrl* RIFF_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 90), wxSize(300, 50));
	RIFF_chunk_size->SetValue(std::to_string(sound->header->RIFF_chunk_size));

    wxTextCtrl* RIFF_format = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 150), wxSize(300, 50));
	RIFF_format->SetValue(std::to_string(std::hex(sound->header->RIFF_format)));

    wxTextCtrl* FMT_chunk_ID = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 30), wxSize(300, 50));
	FMT_chunk_ID->SetValue(std::to_string(sound->header->FMT_chunk_ID));

    wxTextCtrl* FMT_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 90), wxSize(300, 50));
	FMT_chunk_size->SetValue(std::to_string(sound->header->FMT_chunk_size));

    wxTextCtrl* FMT_audio_format = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 150), wxSize(300, 50));
	FMT_audio_format->SetValue(std::to_string(sound->header->FMT_audio_format));

    wxTextCtrl* FMT_num_channels = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 210), wxSize(300, 50));
	FMT_num_channels->SetValue(std::to_string(sound->header->FMT_num_channels));

    wxTextCtrl* FMT_sample_rate = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 270), wxSize(300, 50));
	FMT_sample_rate->SetValue(std::to_string(sound->header->FMT_sample_rate));

    wxTextCtrl* FMT_byte_rate = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 330), wxSize(300, 50));
	FMT_byte_rate->SetValue(std::to_string(sound->header->FMT_byte_rate));

    wxTextCtrl* FMT_block_align = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 390), wxSize(300, 50));
	FMT_block_align->SetValue(std::to_string(sound->header->FMT_block_align));

    wxTextCtrl* FMT_bits_per_sample = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 450), wxSize(300, 50));
	FMT_bits_per_sample->SetValue(std::to_string(sound->header->FMT_bits_per_sample));

    wxTextCtrl* DATA_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 510), wxSize(300, 50));
	DATA_chunk_size->SetValue(std::to_string(sound->header->DATA_chunk_size));
}
