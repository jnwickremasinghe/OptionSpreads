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
	int id=-1;
	if (wxApp::argc==2)	{
		id=1;
	}
    MainFrame *frame = new MainFrame(NULL,id, wxT("Option Spreads"),
         wxPoint(50,50), wxSize(900,1140) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}
