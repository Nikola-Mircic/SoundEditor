#include <functional>
#include <thread>

#include "Animator.h"

BEGIN_EVENT_TABLE(Animator, wxPanel)
    EVT_PAINT(Animator::PaintEvent) // catch paint events
END_EVENT_TABLE()

Animator::Animator(wxFrame* window) : wxPanel(window){
    this->window = window;

    this->rendering = false;
}

Animator::Animator(wxFrame *window, wxPoint pos, wxSize size) : wxPanel(window, wxID_ANY, pos, size){
    this->window = window;

    this->rendering = false;
}

Animator::~Animator(){
    
}

void renderLoop(bool* rendering, Animator* animator) {
    std::cout << "In the render loop function" << std::endl;
    while(*rendering){
        animator->Refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    std::cout << "Closing render loop..." << std::endl;
}

void Animator::ActivateRenderLoop(bool on){
    if(on && !rendering)
    {
        std::cout << "Activating render loop ... " << std::endl;
        rendering = true;

        std::thread t(renderLoop, &rendering, this);

        t.detach();
    }
    else if(!on && rendering)
    {
        std::cout << "Deactivating render loop ... " << std::endl;
        tslist.clearAll();

        rendering = false;
    }
}

void Animator::PaintEvent(wxPaintEvent & evt)
{
    std::cout << "Pain event cought " << std::endl;
    wxPaintDC dc(this);
    Draw(dc);
}

void Animator::PaintNow()
{
    std::cout << "Pain event ordered " << std::endl;
    wxClientDC dc(this);
    Draw(dc);
}

double last_r=0;

void Animator::Draw(wxDC& dc){
    if(rendering){

        wxSize size = this->GetSize();

        std::cout << "Rednering [ " << size.GetWidth() << ", " << size.GetHeight() << " ]" << std::endl;

        static int width = 2;

        wxColor bckg = window->GetBackgroundColour();
        bckg.Set(bckg.Red(), bckg.Green(), bckg.Blue(), wxALPHA_OPAQUE);
        dc.SetBrush(wxBrush(bckg));
        dc.SetPen(wxPen(bckg, 3));
        dc.DrawRectangle(50, 0, 200, 50);

        tslist.forEach([&dc](sample s, int idx){
            int height = std::min(50, (int)(200*val(s)/__SHRT_MAX__));

            int green = 150+freq(s)*25;
            int blue = std::min(255, std::max(green-255, 0));
            green = std::min(green, 255);

            dc.SetBrush(wxBrush(wxColor(0, green, blue)));
            dc.SetPen(wxPen(wxColor(0, green, blue)));
            dc.DrawRectangle(50+idx*width, 50-height, width, height);
        });

        sample s = tslist.back();
        int r = std::min(150, (int) std::abs(val(s)/40));

        int green = 150+freq(s)*25;
        int blue = std::min(255, std::max(green-255, 0));
        green = std::min(green, 255);

        dc.SetBrush(wxBrush(window->GetBackgroundColour()));
        dc.SetPen(wxPen(window->GetBackgroundColour(), 3));
        dc.DrawCircle(150, 200, last_r);

        dc.SetBrush(wxBrush(wxColor(0, green, blue)));
        dc.SetPen(wxPen(wxColor(0, green, blue)));
        dc.DrawCircle(150, 200, r);

        last_r = r;
    }
}

wxWindow *Animator::getWindow() const {
    return window;
}

void Animator::setWindow(wxWindow *window) {
    Animator::window = window;
}

void Animator::TSList::push(sample& s){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    if(samples.size() >= 100)
        samples.pop_front();

    samples.push_back(s);
}

void Animator::TSList::remove_front(){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    samples.pop_front();
}

void Animator::TSList::clearAll(){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    samples.clear();
}

sample& Animator::TSList::back(){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    return samples.back();
}

void Animator::TSList::forEach(std::function<void(sample, int)> func){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    int idx = 0;

    for (auto it = samples.begin(); it != samples.end(); ++it)
        func(*it, idx++);

    std::cout << "[ " << idx << " ] samples iterated!" << std::endl;
}

size_t Animator::TSList::size(){
    std::lock_guard<std::mutex> dataGuard(dataMutex);

    return samples.size();
}
