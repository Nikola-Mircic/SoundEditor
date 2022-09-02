#include "Window.h"

#include <iostream>

#define PARENT NULL
#define ID wxID_ANY
#define TITLE "Sound Editor"
#define WINODW_POSITION wxDefaultPosition
#define WINDOW_SIZE wxSize(1000, 700) 

BEGIN_EVENT_TABLE (Window, wxFrame)
    EVT_BUTTON ( PLAY_BUTTON, Window::Play)
END_EVENT_TABLE()

Window::Window()
    : wxFrame(PARENT, ID, TITLE, WINODW_POSITION, WINDOW_SIZE)
{
    reader = new WAVReader();

	sound = reader->ReadFileData("/home/nikola/Desktop/Projects/SoundEditor/src/audio/","sample.wav");
    
    std::cout << "\n\t Playing sound... \n";

    std::cout << "\t Sound size: " << sound->data->size() << std::endl;

    DrawSoundData(sound);
}

void Window::DrawSoundData(WAV_FILE* sound){
    wxStaticText* staticText = new wxStaticText(this, wxID_ANY, "RIFF_chunk_ID", wxPoint(30, 10));
    wxTextCtrl* RIFF_chunk_ID = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 30), wxSize(300, 50));
	RIFF_chunk_ID->SetValue(std::to_string(sound->header->RIFF_chunk_ID));
	
    wxStaticText* staticText2 = new wxStaticText(this, wxID_ANY, "RIFF_chunk_size", wxPoint(30, 90));
    wxTextCtrl* RIFF_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 110), wxSize(300, 50));
	RIFF_chunk_size->SetValue(std::to_string(sound->header->RIFF_chunk_size));

    wxStaticText* staticText3 = new wxStaticText(this, wxID_ANY, "RIFF_format", wxPoint(30, 170));
    wxTextCtrl* RIFF_format = new wxTextCtrl(this, wxID_ANY, "", wxPoint(30, 190), wxSize(300, 50));
	RIFF_format->SetValue(std::to_string(sound->header->RIFF_format));

    wxStaticText* staticText4 = new wxStaticText(this, wxID_ANY, "FMT_chunk_ID", wxPoint(350, 10));
    wxTextCtrl* FMT_chunk_ID = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 30), wxSize(300, 50));
	FMT_chunk_ID->SetValue(std::to_string(sound->header->FMT_chunk_ID));

    wxStaticText* staticText5 = new wxStaticText(this, wxID_ANY, "FMT_chunk_ID", wxPoint(350, 90));
    wxTextCtrl* FMT_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 110), wxSize(300, 50));
	FMT_chunk_size->SetValue(std::to_string(sound->header->FMT_chunk_size));

    wxStaticText* staticText6 = new wxStaticText(this, wxID_ANY, "FMT_chunk_ID", wxPoint(350, 170));
    wxTextCtrl* FMT_audio_format = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 190), wxSize(300, 50));
	FMT_audio_format->SetValue(std::to_string(sound->header->FMT_audio_format));

    wxStaticText* staticText7 = new wxStaticText(this, wxID_ANY, "FMT_num_channels", wxPoint(350, 250));
    wxTextCtrl* FMT_num_channels = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 270), wxSize(300, 50));
	FMT_num_channels->SetValue(std::to_string(sound->header->FMT_num_channels));

    wxStaticText* staticText8 = new wxStaticText(this, wxID_ANY, "FMT_sample_rate", wxPoint(350, 330));
    wxTextCtrl* FMT_sample_rate = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 350), wxSize(300, 50));
	FMT_sample_rate->SetValue(std::to_string(sound->header->FMT_sample_rate));

    wxStaticText* staticText9 = new wxStaticText(this, wxID_ANY, "FMT_byte_rate", wxPoint(350, 410));
    wxTextCtrl* FMT_byte_rate = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 430), wxSize(300, 50));
	FMT_byte_rate->SetValue(std::to_string(sound->header->FMT_byte_rate));

    wxStaticText* staticText10 = new wxStaticText(this, wxID_ANY, "FMT_block_align", wxPoint(350, 490));
    wxTextCtrl* FMT_block_align = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 510), wxSize(300, 50));
	FMT_block_align->SetValue(std::to_string(sound->header->FMT_block_align));

    wxStaticText* staticText11 = new wxStaticText(this, wxID_ANY, "FMT_bits_per_sample", wxPoint(350, 570));
    wxTextCtrl* FMT_bits_per_sample = new wxTextCtrl(this, wxID_ANY, "", wxPoint(350, 590), wxSize(300, 50));
	FMT_bits_per_sample->SetValue(std::to_string(sound->header->FMT_bits_per_sample));

    wxStaticText* staticText12 = new wxStaticText(this, wxID_ANY, "DATA_chunk_size", wxPoint(670, 10));
    wxTextCtrl* DATA_chunk_size = new wxTextCtrl(this, wxID_ANY, "", wxPoint(670, 30), wxSize(300, 50));
	DATA_chunk_size->SetValue(std::to_string(sound->header->DATA_chunk_size));

    wxButton* PlayButton = new wxButton(this, PLAY_BUTTON, _T("Play sound"),
    wxPoint(720, 110), wxSize(200, 50), 0);
}


void Window::Play(wxCommandEvent& event ){
    PlaySoundSDL2("./sample.wav");
}