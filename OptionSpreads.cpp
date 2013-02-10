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
BEGIN_EVENT_TABLE(MyFrame1, wxFrame)
    EVT_MENU(ID_Quit, MyFrame1::OnQuit)
    EVT_MENU(ID_About, MyFrame1::OnAbout)
END_EVENT_TABLE()
*/
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame1 *frame = new MyFrame1(NULL,-1, wxT("Hello World"),
         wxPoint(50,50), wxSize(1700,1340) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}
