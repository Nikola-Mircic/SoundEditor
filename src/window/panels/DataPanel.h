//
// Created by nikola on 22.3.24..
//

#ifndef SOUNDEDITOR_DATAPANEL_H
#define SOUNDEDITOR_DATAPANEL_H

#include "wx/wx.h"
#include "wx/sizer.h"

#include "../../audio/WAVReader.h"

#define PLAY_BUTTON 0xb1
#define RESTART_BUTTON 0xb2
#define CONTINUE_BUTTON 0xb3
#define STOP_BUTTON 0xb4
#define LOAD_FILE_BUTTON 0xb5

class DataPanel : public wxPanel{
public:
    DataPanel(wxFrame* parent, wxPoint pos, wxSize size) : wxPanel(parent, wxID_ANY, pos, size){}
    ~DataPanel(){}

    void UseData(WAV_FILE* data);

private:
    void addLabelFieldPair(wxSizer *sizer, wxString label, wxString value);
};


#endif //SOUNDEDITOR_DATAPANEL_H
