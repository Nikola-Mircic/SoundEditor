#pragma once

#include <iostream>

#include <mutex>

#include "wx/wx.h"

class Animator : public wxTimer{
public:
    Animator(wxWindow* window);
    ~Animator();

    void SetData(long long value, double freq);
    void ActivateRenderLoop(bool on);

    void Notify();
    void TimerStart();

    void Draw();
private:
    std::mutex dataMutex;

    long long value;
    double freq;

    wxWindow* window;
    bool rendering = false;
};