#include "Animator.h"

#include <cmath>

Animator::Animator(wxWindow* window){
    this->window = window;

    this->rendering = false;
}

Animator::~Animator(){

}

void Animator::SetData(double value, double freq){
    std::lock_guard<std::mutex> dataGuard(dataMutex);
    
    this->value = value;
    this->freq = freq;
}

void Animator::TimerStart(){
    Start(30);
}

void Animator::Notify(){
    Draw();
}

void Animator::ActivateRenderLoop(bool on){
    if(on && !rendering)
    {   
        TimerStart();
        rendering = true;
    }
    else if(!on && rendering)
    {   
        Stop();
        rendering = false;
    }
}

double last_r=0;

void Animator::Draw(){
    if(rendering){
        int r = std::abs(value/40);

        int green = 150+freq*25;
        int blue = std::min(255, std::max(green-255, 0));
        green = std::min(green, 255);

        wxClientDC dc(window);

        dc.SetBrush(wxBrush(window->GetBackgroundColour()));
        dc.SetPen(wxPen(window->GetBackgroundColour(), 3));
        dc.DrawCircle(100, 500, last_r);

        dc.SetBrush(wxBrush(wxColor(0, green, blue)));
        dc.SetPen(wxPen(wxColor(0, green, blue)));
        dc.DrawCircle(100, 500, r);

        last_r = r;
    }
}