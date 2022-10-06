#include "Animator.h"

Animator::Animator(wxWindow* window){
    this->window = window;

    this->rendering = false;
}

Animator::~Animator(){

}

void Animator::SetData(long long value, double freq){
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

int r = 2, step = 2;

void Animator::Draw(){
    if(rendering){
        wxClientDC dc(window);

        dc.SetBrush(wxBrush(window->GetBackgroundColour()));
        dc.SetPen(wxPen(window->GetBackgroundColour(), 3));
        dc.DrawRectangle(50, 450, 100, 100);

        dc.SetBrush(wxBrush(wxColor(200, 10, 10)));
        dc.SetPen(wxPen(wxColor(200, 10, 10)));
        dc.DrawCircle(100, 500, r);

        if(r>= 50 || r<=0)
            step=-step;

        r+=step;
    }
}