/*
 * hworld.cpp
 * Hello world sample by Robert Roebling
 * Adapted for unicode by Max Berger
 */

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
/*
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Quit, MainFrame::OnQuit)
    EVT_MENU(ID_About, MainFrame::OnAbout)
END_EVENT_TABLE()
*/
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(NULL,-1, wxT("Hello World"),
         wxPoint(50,50), wxSize(1700,1340) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}
