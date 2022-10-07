#pragma once

#include <iostream>
#include <deque>
#include <mutex>

#include "wx/wx.h"

typedef std::pair<double, double> sample;

class Animator : public wxTimer{
public:
    Animator(wxWindow* window);
    ~Animator();

    void SetData(double value, double freq);
    void ActivateRenderLoop(bool on);

    void Notify();
    void TimerStart();

    void Draw();
private:
    std::mutex dataMutex;

    double value;
    double freq;

    std::deque<sample> samples;

    wxWindow* window;
    bool rendering = false;
};