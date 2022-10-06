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

void Animator::ActivateRenderLoop(bool on){
    if(on && !rendering)
    {   
        std::cout << "\n--> Activated! \n\n";
        Connect( wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(Animator::Render) );
        rendering = true;
    }
    else if(!on && rendering)
    {   
        std::cout << "\n--> Stoped! \n\n";
        Disconnect( wxEVT_IDLE, wxIdleEventHandler(Animator::Render) );
        rendering = false;
    }
}

int r = 2, step = 2;

void Animator::Render(wxIdleEvent& event){
    if(rendering){
        std::cout << " \n---> Animating ... \n\n";

        wxClientDC clientdc(this->window);

        clientdc.SetBrush(wxBrush(wxColor(150, 150, 150)));
        clientdc.SetPen(wxPen(wxColor(150, 150, 150)));
        clientdc.DrawRectangle(50, 450, 100, 100);

        clientdc.SetBrush(wxBrush(wxColor(200, 10, 10)));
        clientdc.SetPen(wxPen(wxColor(200, 10, 10)));
        clientdc.DrawCircle(100, 500, r);

        if(r>= 50 || r<=0)
            step=-step;

        r+=step;

        event.RequestMore();
    }
}