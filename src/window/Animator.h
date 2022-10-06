#pragma once

#include <iostream>

#include <mutex>

#include "wx/wx.h"

class Animator : wxEvtHandler{
public:
    Animator(wxWindow* window);
    ~Animator();

    void SetData(long long value, double freq);
    void ActivateRenderLoop(bool on);

    void Render(wxIdleEvent& event);
private:
    std::mutex dataMutex;

    long long value;
    double freq;

    wxWindow* window;
    bool rendering;
};