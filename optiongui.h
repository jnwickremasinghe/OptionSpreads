// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Dec 25 13:08:40 2012

#include <wx/wx.h>
#include <wx/image.h>
// begin wxGlade: ::dependencies
#include <wx/grid.h>
#include "ticker.hpp"
#include "wxticker.hpp"
#include "quote.hpp"
#include <boost/shared_ptr.hpp>
// end wxGlade

#ifdef wxUSE_UNICODE
#define _U(x) wxString((x),wxConvUTF8)
#define _UU(x,y) wxString((x),y)
#define _CC(x,y) (x).mb_str((y))
#else
#define _U(x) (x)
#define _UU(x,y) (x)
#define _CC(x,y) (x)
#endif

#define _C(x) _CC((x),wxConvUTF8)


#ifndef OPTION_H
#define OPTION_H




// begin wxGlade: ::extracode
// end wxGlade


class MyFrame1: public wxFrame {
public:
    // begin wxGlade: MyFrame1::ids
    // end wxGlade

    MyFrame1(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
    void OnQuit(wxCommandEvent & event);
    void onQuoteUpdate(wxCommandEvent & event);

    boost::shared_ptr<quote> quote_ptr;
    quote* std_quote;
    wxticker* mywxtick;
    quote* wxquote;
private:
    // begin wxGlade: MyFrame1::methods
    void set_properties();
    void do_layout();

    void get_quote(wxCommandEvent& WXUNUSED(event));
    // end wxGlade
    enum
    {
    	BUTTON_GetQuote = wxID_HIGHEST + 1
    };


//	ticker mytick;
//	wxticker mywxtick(this);
protected:
    // begin wxGlade: MyFrame1::attributes
    wxMenuBar* frame_1_menubar;
    wxStaticText* label_1;
    wxStaticText* label_2;
    wxStaticText* label_3;
    wxStaticText* label_4;
    wxStaticText* label_5;

    wxButton* wxButtonOK;

    wxTextCtrl* txtctrlConsumerKey;
    wxTextCtrl* txtctrlConsumerSecret;
    wxTextCtrl* txtctrlTokenKey;
    wxTextCtrl* txtctrlTokenSecret;
    wxTextCtrl* txtctrlURI;
    wxGrid* grid_1;
    // end wxGlade
}; // wxGlade: end class



#endif // OPTION_H
