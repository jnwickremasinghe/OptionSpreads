// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Dec 25 13:08:40 2012

#include "optiongui.h"
#include "tinyxml2.h"
#include <oauth.h>
#include <string>
using namespace std;
using namespace tinyxml2;

// begin wxGlade: ::extracode
// end wxGlade
/*
public class MyFrame12
{
	//class level variables
	private  wxTextCtrl text_ctrl_1;
	public MyFrame12()	{
		text_ctrl_1=1
	}

}
*/

MyFrame1::MyFrame1(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MyFrame1::MyFrame1
    frame_1_menubar = new wxMenuBar();
    wxMenu* wxglade_tmp_menu_1 = new wxMenu();
    wxglade_tmp_menu_1->Append(wxID_EXIT, wxT("Quit"), wxEmptyString, wxITEM_NORMAL);
    frame_1_menubar->Append(wxglade_tmp_menu_1, wxT("File"));
    SetMenuBar(frame_1_menubar);

    label_1 = new wxStaticText(this, wxID_ANY, wxT("Consumer Key"));
    //txtctrlConsumerKey = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    txtctrlConsumerKey = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_2 = new wxStaticText(this, wxID_ANY, wxT("Consumer Secret"));
    txtctrlConsumerSecret = new wxTextCtrl(this, wxID_ANY,wxEmptyString);
    //txtctrlConsumerSecret = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_3 = new wxStaticText(this, wxID_ANY, wxT("Token Key"));
    txtctrlTokenKey = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    //txtctrlTokenKey = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_4 = new wxStaticText(this, wxID_ANY, wxT("Token Secret"));
    txtctrlTokenSecret = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    //txtctrlTokenSecret = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_5 = new wxStaticText(this, wxID_ANY, wxT("URI"));
    txtctrlURI = new wxTextCtrl(this, wxID_ANY, wxT("MSTR"));
    wxButtonOK = new wxButton(this, BUTTON_GetQuote, wxT("Get Quote"));
    grid_1 = new wxGrid(this, wxID_ANY);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
    Connect(BUTTON_GetQuote,wxEVT_COMMAND_BUTTON_CLICKED , wxCommandEventHandler(MyFrame1::get_quote));



    set_properties();
    do_layout();


    // end wxGlade
}

void MyFrame1::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MyFrame1::set_properties()
{
    // begin wxGlade: MyFrame1::set_properties
    SetTitle(wxT("Option Spreads"));
    grid_1->CreateGrid(10, 5);
    grid_1->SetColLabelValue(0, wxT("Strike"));
    grid_1->SetColLabelValue(1, wxT("Symbol"));
    grid_1->SetColLabelValue(2, wxT("Last"));
    grid_1->SetColLabelValue(3, wxT("Date time"));
    grid_1->SetColLabelValue(4, wxT("Open Interest"));
    // end wxGlade
}


void MyFrame1::do_layout()
{
    // begin wxGlade: MyFrame1::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* ConsKeySizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* ConsSecretSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* TokenKeySizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* TokenSecretSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* URISizer = new wxBoxSizer(wxHORIZONTAL);

    ConsKeySizer->Add(label_1, 0, wxRIGHT, 8);
    ConsKeySizer->Add(txtctrlConsumerKey, 1,0,10);

    ConsSecretSizer->Add(label_2, 0, wxRIGHT, 8);
    ConsSecretSizer->Add(txtctrlConsumerSecret, 1,0,10);

    TokenKeySizer->Add(label_3, 0, wxRIGHT, 8);
    TokenKeySizer->Add(txtctrlTokenKey, 1,0,10);

    TokenSecretSizer->Add(label_4, 0, wxRIGHT, 8);
    TokenSecretSizer->Add(txtctrlTokenSecret, 1,0,10);
    URISizer->Add(label_5,0,wxRIGHT,10);
    URISizer->Add(txtctrlURI,1,0,10);
    URISizer->Add(wxButtonOK,0,0,10);

    sizer_4->Add(ConsSecretSizer, 1,wxEXPAND,0);
    sizer_4->Add(ConsKeySizer, 1,wxEXPAND,0);
    sizer_4->Add(TokenKeySizer, 1,wxEXPAND,0);
    sizer_4->Add(TokenSecretSizer, 1,wxEXPAND,0);
    sizer_4->Add(URISizer,1,wxEXPAND,0);

//    sizer_1->Add(ConsSecretSizer, 1, wxEXPAND, 10);
    sizer_1->Add(sizer_4, 1, wxALL|wxEXPAND, 10);
    sizer_1->Add(grid_1, 1, wxALL|wxEXPAND, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    Layout();
    // end wxGlade
}

void MyFrame1::get_quote(wxCommandEvent& WXUNUSED(event))
{


	char test_call_uri[255] = "https://api.tradeking.com/v1/market/ext/quotes.xml?symbols=";

	//get Consumer Key as ASCII const char*
	const wxCharBuffer pbuff = _C(txtctrlConsumerKey->GetValue());
	const char *c_key = pbuff.data();

	//get Consumer Secret as ASCII const char*
	const wxCharBuffer pbuff2 = _C(txtctrlConsumerSecret->GetValue());
	const char *c_secret = pbuff2.data();

	//get Token Key as ASCII const char*
	const wxCharBuffer pbuff4 = _C(txtctrlTokenKey->GetValue());
	const char *t_key = pbuff4.data();

	//get Token Secret as ASCII const char*
	const wxCharBuffer pbuff5 = _C(txtctrlTokenSecret->GetValue());
	const char *t_secret = pbuff5.data();


	//get URI as an ASCII const char*
	const wxCharBuffer pbuff3 = _C(txtctrlURI->GetValue());
	const char *symbol = pbuff3.data();
	strcat(test_call_uri,symbol);

//	const char *test_call_uri="https://api.tradeking.com/v1/member/profile.xml" ;


	char *req_url = NULL;
	char *postarg = NULL;
	char *reply   = NULL;

    req_url = oauth_sign_url2(test_call_uri, NULL, OA_HMAC, NULL, c_key, c_secret, t_key, t_secret);
    reply = oauth_http_get(req_url,postarg);


    XMLDocument xmlreply;
    XMLElement* xmllast;
    XMLNode *xmlfirstnode;
    xmlreply.Parse(reply);

    xmlfirstnode=xmlreply.FirstChild();
    xmlfirstnode=xmlfirstnode->FirstChild();
    xmllast=xmlreply.FirstChildElement("response")->FirstChildElement("quotes")->FirstChildElement("quote")->FirstChildElement("last");

    grid_1->SetCellValue(0,1,txtctrlURI->GetValue());

    const char *last;
    last=xmllast->GetText();

    grid_1->SetCellValue(0,2,wxString::FromAscii(last));

}