// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Dec 25 13:08:40 2012

#include "ticker.hpp"
#include "quote.hpp"
#include "optiongui.h"
#include "tinyxml2.h"

#include <oauth.h>
#include <string>
#include <fstream>
#include <sstream>




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
    parameters.open(config_file.c_str());

    //initialize oauth credentials as empty, try to read them in
    wxString cons_key=wxEmptyString;
    wxString cons_secret=wxEmptyString;
    wxString token_key=wxEmptyString;
    wxString token_secret=wxEmptyString;
    wxString watchlist=wxEmptyString;
    wxString option_list=wxEmptyString;
    wxString URL=wxEmptyString;
    wxString DBPath=wxEmptyString;


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
    	getline(parameters, line);
    	URL=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	DBPath=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	watchlist=wxString::FromAscii(line.c_str());
    	getline(parameters, line);
    	option_list=wxString::FromAscii(line.c_str());
		}

    label_1 = new wxStaticText(this, wxID_ANY, wxT("Consumer Key"));
    txtctrlConsumerKey = new wxTextCtrl(this, wxID_ANY, cons_key);

    label_2 = new wxStaticText(this, wxID_ANY, wxT("Consumer Secret"));
    txtctrlConsumerSecret = new wxTextCtrl(this, wxID_ANY,cons_secret);

    label_3 = new wxStaticText(this, wxID_ANY, wxT("Token Key"));
    txtctrlTokenKey = new wxTextCtrl(this, wxID_ANY, token_key);

    label_4 = new wxStaticText(this, wxID_ANY, wxT("Token Secret"));
    txtctrlTokenSecret = new wxTextCtrl(this, wxID_ANY, token_secret);

    label_4a = new wxStaticText(this, wxID_ANY, wxT("URL"));
    txtctrlURL = new wxTextCtrl(this, wxID_ANY, URL);

    label_4b = new wxStaticText(this, wxID_ANY, wxT("Options"));
    txtctrlOption_Symbols = new wxTextCtrl(this, wxID_ANY, option_list);

    label_5 = new wxStaticText(this, wxID_ANY, wxT("Symbols"));
    txtctrlSymbols = new wxTextCtrl(this, wxID_ANY, watchlist);

    label_6 = new wxStaticText(this, wxID_ANY, wxT("DB"));
    txtctrlDBPath= new wxTextCtrl(this, wxID_ANY, DBPath);

    wxButtonOK = new wxButton(this, BUTTON_GetQuote, wxT("Get Quote"));
    grid_1 = new wxGrid(this, wxID_ANY);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::OnQuit));
    Connect(BUTTON_GetQuote,wxEVT_COMMAND_BUTTON_CLICKED , wxCommandEventHandler(MyFrame1::get_quote));
    Connect(QUOTE_CALLBACK, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::onQuoteUpdate));
    Connect(TICKER_INIT, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::OnCurlError));
    set_properties();
    do_layout();
    // end wxGlade

};

void MyFrame1::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
	delete std_quote;
	delete mywxtick;
}

void MyFrame1::set_properties()
{
    // begin wxGlade: MyFrame1::set_properties
    SetTitle(wxT("Option Spreads"));
    grid_1->CreateGrid(15, 7);
    grid_1->SetColLabelValue(0, wxT("Strike"));
    grid_1->SetColLabelValue(1, wxT("Symbol"));
    grid_1->SetColLabelValue(2, wxT("Bid"));
    grid_1->SetColLabelValue(3, wxT("Ask"));
    grid_1->SetColLabelValue(4, wxT("Last"));
    grid_1->SetColLabelValue(5, wxT("% Chg"));
    grid_1->SetColLabelValue(6, wxT("Date time"));
    grid_1->SetColSize(6,120);
    grid_1->SetColSize(1,120);
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
    wxBoxSizer* TokenURLSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* OptionSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* SymbolsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* DBPathSizer = new wxBoxSizer(wxHORIZONTAL);

    ConsKeySizer->Add(label_1, 0, wxRIGHT, 8);
    ConsKeySizer->Add(txtctrlConsumerKey, 1,0,10);

    ConsSecretSizer->Add(label_2, 0, wxRIGHT, 8);
    ConsSecretSizer->Add(txtctrlConsumerSecret, 1,0,10);

    TokenKeySizer->Add(label_3, 0, wxRIGHT, 8);
    TokenKeySizer->Add(txtctrlTokenKey, 1,0,10);

    TokenSecretSizer->Add(label_4, 0, wxRIGHT, 8);
    TokenSecretSizer->Add(txtctrlTokenSecret, 1,0,10);

    TokenURLSizer->Add(label_4a,0,wxRIGHT,10);
    TokenURLSizer->Add(txtctrlURL,1,0,10);

    DBPathSizer->Add(label_6, 0, wxRIGHT, 8);
    DBPathSizer->Add(txtctrlDBPath, 1,0,10);

    OptionSizer->Add(label_4b, 0, wxRIGHT, 8);
    OptionSizer->Add(txtctrlOption_Symbols, 1,0,10);

    SymbolsSizer->Add(label_5, 0, wxRIGHT, 8);
    SymbolsSizer->Add(txtctrlSymbols, 1,0,10);
    SymbolsSizer->Add(wxButtonOK,0,0,10);


    sizer_4->Add(ConsKeySizer, 1,wxEXPAND,0);
    sizer_4->Add(ConsSecretSizer, 1,wxEXPAND,0);
    sizer_4->Add(TokenKeySizer, 1,wxEXPAND,0);
    sizer_4->Add(TokenSecretSizer, 1,wxEXPAND,0);
    sizer_4->Add(TokenURLSizer, 1,wxEXPAND,0);
    sizer_4->Add(DBPathSizer, 1,wxEXPAND,0);
    sizer_4->Add(OptionSizer,1,wxEXPAND,0);
    sizer_4->Add(SymbolsSizer,1,wxEXPAND,0);


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

	//create a quote object for each inputted symbol
	wxString ctrl_value;
	ctrl_value=txtctrlSymbols->GetValue();
	std::string symbol_temp;
	symbol_temp=ctrl_value.mb_str();
	std::string symbol;
	size_t comma_position;
	//comma_position=symbol_list.find(',',comma_position);

	int symbol_order=1;
	do	{
		comma_position=0;
		comma_position=symbol_temp.find(',',comma_position);
		if (comma_position!=string::npos){
			symbol=symbol_temp.substr(0,comma_position);
			symbol_temp=symbol_temp.substr(comma_position+1,string::npos);
		}
		else	{
			symbol=symbol_temp;

		}
		if (!symbol.empty())	{

			std::string db_connection;


			ctrl_value=txtctrlDBPath->GetValue();
			db_connection=ctrl_value.mb_str();

			wxquote = new quote(symbol,symbol_order, db_connection);
			symbols[wxquote->symbol()]=wxquote;
			grid_1->SetCellValue(symbol_order-1,1,wxString::FromAscii(symbol.c_str()));
			symbol_order++;

		}

	} while (comma_position!=string::npos);


	wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, TICKER_INIT);
	event.SetString(wxT("start"));
	event.SetInt(TICKER_INIT);
	this->GetEventHandler()->AddPendingEvent(event);

}

void MyFrame1::onQuoteUpdate(wxCommandEvent& evt)	{

	XMLDocument xmlreply;
	int parse_success;

	parse_success=xmlreply.Parse(evt.GetString().mb_str(wxConvUTF8));

	XMLElement* xmlvalue;
	XMLHandle xml_handle(xmlreply);
	XMLElement* xml_eml;
	xml_eml = xml_handle.FirstChildElement().ToElement();
	std::string ElementName = xml_eml->Name();

	float last;
	float bid;
	float ask;
	std::string symbol;
	std::string timestamp;
	quote* symbol_ptr;

	if (ElementName=="quote" )	{

		xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("symbol").ToElement();
		if (xmlvalue!=0)	{
			symbol=xmlvalue->GetText();
		}
		xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("bid").ToElement();
		if (xmlvalue!=0)	{
			std::stringstream strValue;

			strValue << (xmlvalue->GetText());
			strValue >> bid;
		}

		xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("ask").ToElement();
		if (xmlvalue!=0)	{
			std::stringstream strValue;

			strValue << (xmlvalue->GetText());
			strValue >> ask;
		}

		xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("datetime").ToElement();
		if (xmlvalue!=0)	{
			timestamp=xmlvalue->GetText();
		}

		//split datetime into date & time
		std::string quote_date;
		std::string quote_time;
		int split_pos=timestamp.find('T',0);
		quote_date=timestamp.substr(0,split_pos);
		quote_time=timestamp.substr(split_pos+1,string::npos);

		symbol_ptr=symbols[symbol];
		if (symbol_ptr)	{
			symbols[symbol]->ask(ask);
			symbols[symbol]->bid(bid);
			symbols[symbol]->date(quote_date);
			symbols[symbol]->time(quote_time);
			symbols[symbol]->save("quote");

			int row_num=symbols[symbol]->order()-1;
			grid_1->SetCellValue(row_num,1,wxString::FromAscii(symbol.c_str()));
			grid_1->SetCellValue(row_num,2,wxString::Format(wxT("%f"),bid));
			grid_1->SetCellValue(row_num,3,wxString::Format(wxT("%f"),ask));
	//		grid_1->SetCellValue(row_num,5,wxString::FromAscii(quote_time.c_str()));
		} else	{
			std::cerr <<"Unknown symbol in quote: " << symbol << endl;
		}
	}



	if (ElementName=="trade")	{
			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("symbol").ToElement();
			if (xmlvalue!=0)	{
				symbol=xmlvalue->GetText();
			}
			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("last").ToElement();
			if (xmlvalue!=0)	{
				std::stringstream strValue;

				strValue << (xmlvalue->GetText());
				strValue >> last;
			}

			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("datetime").ToElement();
			if (xmlvalue!=0)	{
				timestamp=xmlvalue->GetText();
			}

		//split datetime into date & time
		std::string quote_date;
		std::string quote_time;
		int split_pos=timestamp.find('T',0);
		quote_date=timestamp.substr(0,split_pos);
		quote_time=timestamp.substr(split_pos+1,string::npos);

		symbol_ptr=symbols[symbol];
		if (symbol_ptr)	{
			symbols[symbol]->last(last);
			symbols[symbol]->date(quote_date);
			symbols[symbol]->time(quote_time);
			symbols[symbol]->save("trade");
			double pct_chg = symbols[symbol]->pct_chg();


			int row_num=symbols[symbol]->order()-1;
			grid_1->SetCellValue(row_num,1,wxString::FromAscii(symbol.c_str()));
			grid_1->SetCellValue(row_num,4,wxString::Format(wxT("%f"),last));
			grid_1->SetCellValue(row_num,5,wxString::Format(wxT("%f"),pct_chg));
			grid_1->SetCellValue(row_num,6,wxString::FromAscii(quote_time.c_str()));

		} else {
			std::cerr <<"Unknown symbol in trade: " << symbol << endl;
		}
	}


}

void MyFrame1::OnCurlError(wxCommandEvent& evt)	{

	std::string message = std::string(evt.GetString().mb_str());
	int call_num=evt.GetInt();

	if (call_num==TICKER_INIT && message=="start")	{
		//initial call to start thread

		std::string URLBase; // = "https://api.tradeking.com/v1/market/ext/quotes.xml?symbols=";
		URLBase=(txtctrlURL->GetValue()).mb_str();


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
		ctrl_value=txtctrlSymbols->GetValue();

		std::string symbol_list;
		symbol_list=ctrl_value.mb_str();

		std::string db_connection;
		ctrl_value=txtctrlDBPath->GetValue();
		db_connection=ctrl_value.mb_str();




		tickthread = new ticker(this);
		tickthread->start(ConsumerKey, ConsumerSecret, TokenKey, TokenSecret, URLBase, symbol_list);

		wxThreadError err = tickthread->Create();

	    if (err != wxTHREAD_NO_ERROR)
	    {
	        wxMessageBox( _("Couldn't create thread!") );

	    }

	    err = tickthread->Run();

	    if (err != wxTHREAD_NO_ERROR)
	    {
	        wxMessageBox( _("Couldn't run thread!") );

	    }




	} else	{
		//callback after an error
		std::cout <<"Curl error:" <<  message <<endl;
		std::cout << "Error #"<< call_num  <<endl;
		std::cout <<"Here's where we'd fire off wxticker again..." <<endl;
	}

}

MyFrame1::~MyFrame1()	{


    std::map<std::string, quote* > ::iterator iter;

    for (iter = symbols.begin(); iter != symbols.end(); ++iter) {
    	quote* symbol_ptr;
    	symbol_ptr=iter->second;
    	delete symbol_ptr;

    }
    tickthread->Delete();
    delete tickthread;

}

