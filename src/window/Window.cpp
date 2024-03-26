#include "Window.h"

BEGIN_EVENT_TABLE (Window, wxFrame)
    EVT_BUTTON ( PLAY_BUTTON, Window::Play)
    EVT_BUTTON ( RESTART_BUTTON, Window::Restart)
    EVT_BUTTON ( CONTINUE_BUTTON, Window::Continue)
    EVT_BUTTON ( STOP_BUTTON, Window::Stop)
    EVT_BUTTON ( LOAD_FILE_BUTTON, Window::LoadFile)
END_EVENT_TABLE()


std::future<void> animation;

Window::Window()
    : wxFrame(PARENT, ID, TITLE, WINODW_POSITION, WINDOW_SIZE, WINDOW_STYLE)
{
    reader = new WAVReader();
    sound = nullptr;

    mainSizer = new wxBoxSizer(wxVERTICAL);

    dataPanel = new DataPanel(this, wxDefaultPosition, wxSize(500,900));
    animator = new Animator(this, {30, 250}, {300, 350});
    player = new Player(animator);

    DrawLayout(sound);
}

Window::~Window(){
    delete reader;
    delete player;
    delete sound;

    animator->ActivateRenderLoop(false);
    delete animator;
}

std::string soundPath = "";

void Window::LoadFile(wxCommandEvent& event){
     wxFileDialog 
        openFileDialog(this, _("Load a WAV file"), "", "",
                       "Wav files (*.wav)|*.wav", wxFD_OPEN);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; 

    soundPath = openFileDialog.GetPath().ToStdString();

    sound = reader->ReadFileData(soundPath);

    DrawLayout(sound);
}

void Window::DrawLayout(WAV_FILE* sound){
    wxButton* LoadFileButton = nullptr;
    if(!sound){
        LoadFileButton = new wxButton(this, LOAD_FILE_BUTTON, _T("Find file"),
        wxDefaultPosition, wxSize(200, 50), 0);

        mainSizer->AddStretchSpacer();
        mainSizer->Add(LoadFileButton, 0, wxALIGN_CENTER|wxALL, 10);
        mainSizer->AddStretchSpacer();

        this->SetSizerAndFit(mainSizer);
        return;
    }

    mainSizer->Clear(true);

    std::cout << "Creating data panel... " << std::endl;

    dataPanel->UseData(sound);

    mainSizer->Add(dataPanel, 1, wxALIGN_CENTER|wxALL, 10);

    this->SetSizerAndFit(mainSizer);
}

void Window::Play(wxCommandEvent& event ){
    animator->ActivateRenderLoop(true);

    player->playSound(soundPath.c_str());
}

void Window::Restart(wxCommandEvent& event ){
    player->restartSound();
}

void Window::Continue(wxCommandEvent& event ){
    player->continueSound();
}

void Window::Stop(wxCommandEvent& event ){
    player->stopSound();
}