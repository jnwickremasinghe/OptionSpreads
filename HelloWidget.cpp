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


class MyFrame2: public wxFrame
{
public:

    MyFrame2(const wxString& title,
           const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
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
/*
MyFrame2::MyFrame2(const wxString& title,
       const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append( ID_About, wxT("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, wxT("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, wxT("&File") );

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( wxT("Welcome to wxWindows!") );
}


void MyFrame2::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame2::OnAbout(wxCommandEvent& WXUNUSED(event))
{

    wxMessageBox(wxT("This is a wxWindows Hello world sample"),
        wxT("About Hello World"), wxOK | wxICON_INFORMATION, this);
}
*/
