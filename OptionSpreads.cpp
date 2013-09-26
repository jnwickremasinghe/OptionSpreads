#include "wx/wx.h"
#include "optiongui.h"
#include <oauth.h>

class MyApp: public wxApp
{
    virtual bool OnInit();
};

enum
{
    ID_Quit = 1,
    ID_About,

};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(NULL,-1, wxT("Option Spreads"),
         wxPoint(50,50), wxSize(900,1140) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}
