#pragma once

#include <iostream>
#include <iterator>
#include <list>
#include <mutex>
#include <cmath>

#include "wx/wx.h"

#define val(s) (s).first // Macro for sample value
#define freq(s) (s).second // Macro for sample freq

typedef std::pair<double, double> sample; // Sample definition

class Animator : public wxPanel{
public:
    Animator(wxFrame* window);
    Animator(wxFrame* window, wxPoint pos, wxSize size);
    ~Animator();

    void RenderLoop();
    void ActivateRenderLoop(bool on);

    void PaintEvent(wxPaintEvent & evt);
    void PaintNow();

    void Draw(wxDC& dc);

    struct TSList{
        std::mutex dataMutex;

        std::list<sample> samples;

        void push(sample& s);

        void remove_front();

        void clearAll();

        sample& back();

        void forEach(std::function<void(sample, int)> func);

        size_t size();
    } tslist;

    wxWindow *getWindow() const;
    void setWindow(wxWindow *window);

    DECLARE_EVENT_TABLE();
private:
    wxPanel* panel;
    wxWindow* window;

    bool rendering = false;
};