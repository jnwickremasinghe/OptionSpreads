// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Dec 25 13:08:40 2012
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/version.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <string>
#include <oauth.h>

#include <fstream>
#include <sstream>

#include "optiongui.h"
#include "tinyxml2.h"

#define CONFIG_FILE "/home/joseph/workspace2/OptionSpreads/keys.txt"

using namespace std;
using namespace tinyxml2;





MyFrame1::MyFrame1(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MyFrame1::MyFrame1
    frame_1_menubar = new wxMenuBar();
    wxMenu* wxglade_tmp_menu_1 = new wxMenu();
    wxglade_tmp_menu_1->Append(wxID_EXIT, wxT("Quit"), wxEmptyString, wxITEM_NORMAL);
    frame_1_menubar->Append(wxglade_tmp_menu_1, wxT("File"));
    SetMenuBar(frame_1_menubar);

    ifstream parameters;
    parameters.open("" CONFIG_FILE);

    //initialize oauth credentials as empty, try to read them in
    wxString cons_key=wxEmptyString;
    wxString cons_secret=wxEmptyString;
    wxString token_key=wxEmptyString;
    wxString token_secret=wxEmptyString;

    if (parameters.is_open())
		{
    	std::string line;
    	getline(parameters, line);
    	cons_key=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	cons_secret=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	token_key=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	token_secret=wxString::FromAscii(line.c_str());


		}

    label_1 = new wxStaticText(this, wxID_ANY, wxT("Consumer Key"));
    txtctrlConsumerKey = new wxTextCtrl(this, wxID_ANY, cons_key);

    label_2 = new wxStaticText(this, wxID_ANY, wxT("Consumer Secret"));
    txtctrlConsumerSecret = new wxTextCtrl(this, wxID_ANY,cons_secret);

    label_3 = new wxStaticText(this, wxID_ANY, wxT("Token Key"));
    txtctrlTokenKey = new wxTextCtrl(this, wxID_ANY, token_key);

    label_4 = new wxStaticText(this, wxID_ANY, wxT("Token Secret"));
    txtctrlTokenSecret = new wxTextCtrl(this, wxID_ANY, token_secret);

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

    sizer_4->Add(ConsKeySizer, 1,wxEXPAND,0);
    sizer_4->Add(ConsSecretSizer, 1,wxEXPAND,0);
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

	std::string URLBase = "https://api.tradeking.com/v1/market/ext/quotes.xml?symbols=";

	//get Consumer Key as ASCII const char*
	wxString ctrl_value=txtctrlConsumerKey->GetValue();
	std::string ConsumerKey;
	ConsumerKey = ctrl_value.mb_str();


	//get Consumer Secret as ASCII const char*
	ctrl_value=txtctrlConsumerSecret->GetValue();
	std::string ConsumerSecret;
	ConsumerSecret = ctrl_value.mb_str();

	//get Token Key as ASCII const char*
	ctrl_value=txtctrlTokenKey->GetValue();
	std::string TokenKey;
	TokenKey = ctrl_value.mb_str();

	//get Token Secret as ASCII const char*
	ctrl_value=txtctrlTokenSecret->GetValue();
	std::string TokenSecret;
	TokenSecret = ctrl_value.mb_str();

	//get URI as an ASCII const char*
	ctrl_value=txtctrlURI->GetValue();
	std::string symbol;
	symbol=ctrl_value.mb_str();

	float last_float;

	//create quote object with oauth credentials & pass in symbol & URI
	quote ticker = quote(ConsumerKey, ConsumerSecret, TokenKey, TokenSecret, URLBase);

//	last_float=ticker.last(symbol);
//
//	std::ostringstream buff;
//	buff<<last_float;
//	std::string last_str=buff.str();
//
//	grid_1->SetCellValue(0,2,wxString::FromAscii(last_str.c_str()));

	newquote ticker2;

	ticker2.set_newquote_params(ConsumerKey, ConsumerSecret, TokenKey, TokenSecret, URLBase,"api.tradeking.com");

	ticker2.start(1);

	boost::posix_time::seconds workTime(3);
    boost::this_thread::sleep(workTime);



}
