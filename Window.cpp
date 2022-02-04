#include "Window.h"

#define FRAME_PARENT nullptr
#define FRAME_ID wxID_ANY
#define FRAME_TITLE "Sound editor"
#define FRAME_POSITION wxPoint(20, 20)
#define FRAME_SIZE wxSize(800, 600) 
#define FRAME_STYLE wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL

Window::Window() : wxFrame(FRAME_PARENT, FRAME_ID, FRAME_TITLE, FRAME_POSITION, FRAME_SIZE, FRAME_STYLE) {

}

Window::~Window() {

}