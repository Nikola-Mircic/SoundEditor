//
// Created by nikola on 22.3.24..
//

#include "DataPanel.h"

void DataPanel::UseData(WAV_FILE *data) {
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);

    /*  BUTTONS USED TO:
     *      - Play
     *      - Stop
     *      - Continue
     *      - Restart
     *      - Or find a new file
     * */

    std::cout << "Creating control buttons ... " << std::endl;

    auto* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* PlayButton = new wxButton(this, PLAY_BUTTON, _T("Play"),
                                    wxPoint(720, 110), wxSize(200, 50), 0);

    auto* StopButton = new wxButton(this, STOP_BUTTON, _T("Stop"),
                                    wxPoint(720, 170), wxSize(200, 50), 0);

    auto* ContinueButton = new wxButton(this, CONTINUE_BUTTON, _T("Continue"),
                                        wxPoint(720, 230), wxSize(200, 50), 0);

    auto* RestartButton = new wxButton(this, RESTART_BUTTON, _T("Restart"),
                                       wxPoint(720, 290), wxSize(200, 50), 0);

    auto* LoadFileButton = new wxButton(this, LOAD_FILE_BUTTON, _T("Find file"),
                                        wxPoint(720, 350), wxSize(200, 50), 0);

    buttonsSizer->Add(PlayButton, 1, wxEXPAND|wxALL, 10);
    buttonsSizer->Add(StopButton, 1, wxEXPAND|wxALL, 10);
    buttonsSizer->Add(ContinueButton, 1, wxEXPAND|wxALL, 10);
    buttonsSizer->Add(RestartButton, 1, wxEXPAND|wxALL, 10);
    buttonsSizer->Add(LoadFileButton, 1, wxEXPAND|wxALL, 10);

    mainSizer->Add(buttonsSizer, 0, wxEXPAND);

    std::cout << "Creating data fields ... " << std::endl;

    /*  DATA ABOUT A FILE:
     *      - Number of channels
     *      - Sample rate
     *      - Byte rate
     *      - Block align
     *      - Number of bits per sample
     * */

    auto* dataSizer = new wxGridSizer(6, 2, 10, 10);

    addLabelFieldPair(dataSizer, "Channels", std::to_string(data->header->FMT_num_channels));

    addLabelFieldPair(dataSizer, "Sample rate", std::to_string(data->header->FMT_sample_rate));

    addLabelFieldPair(dataSizer, "Byte rate", std::to_string(data->header->FMT_byte_rate));

    addLabelFieldPair(dataSizer, "Block align", std::to_string(data->header->FMT_block_align));

    addLabelFieldPair(dataSizer, "Bits per sample", std::to_string(data->header->FMT_bits_per_sample));

    addLabelFieldPair(dataSizer, "Chunk size", std::to_string(data->header->DATA_chunk_size));

    mainSizer->Add(dataSizer, 0, wxALIGN_CENTER_HORIZONTAL);

    this->SetSizerAndFit(mainSizer);

    std::cout << "Data panel created! " << std::endl;
}

void DataPanel::addLabelFieldPair(wxSizer* sizer, wxString text, wxString value){
    auto* label = new wxStaticText(this, wxID_ANY, text, wxDefaultPosition);
    auto* field = new wxTextCtrl(this, wxID_ANY, value, wxDefaultPosition, wxSize(250, 50));

    sizer->Add(label, 0, wxALIGN_CENTER|wxLEFT|wxBOTTOM, 10);
    sizer->Add(field, 0, wxALIGN_RIGHT|wxRIGHT|wxBOTTOM, 10);
}