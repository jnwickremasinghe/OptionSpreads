//quote object that retrieves market data
//with TradeKing, uses oauth
#include <iostream>
#include <oauth.h>
#include <sstream>
#include "tinyxml2.h"
#include "wxticker.hpp"

const int QUOTE_CALLBACK = 100000;

using namespace tinyxml2;
using namespace std;

static std::string buffer;
static float last_tick;
static std::string symbol;
static std::string timestamp;

wxticker::wxticker(wxFrame* parent)	{
	m_parent=parent;
	that_quote=(void*) parent;
	cout <<"wxticker created" << endl;
}

void wxticker::init(quote* quote_ptr)	{

	std::string symbol;

	//initialize callback point.
//	that_quote=(void*) quote_ptr;
//	symbol = quote_ptr->symbol();
//    m_Thread = boost::thread(&wxticker::last, this, symbol);
	//start(c_key, c_secret, t_key, t_secret, uri, symbol_list);

};

wxThread::ExitCode wxticker::Entry()	{

	last("test");

	return 0;

}


void wxticker::start(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list)	{

	cons_key=c_key;
	cons_secret=c_secret;
	token_key=t_key;
	token_secret=t_secret;
	url_base=uri;
	symbols=symbol_list;

}

wxticker::~wxticker()	{
	  // Always cleanup
	curl_easy_cleanup(curl);
	cout<< "wxticker destroyed" << endl;
}

// This is the writer call back function used by curl
int wxticker::writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
{
  // What we will return
  int result = 0;

  // Is there anything in the buffer?
  if (buffer != NULL)	{
	// Append the data to the buffer
	buffer->append(data, size * nmemb);
	//try to parse this as an complete XML, if not, let it go.
	XMLDocument xmlreply;
	int parse_success;

	parse_success=xmlreply.Parse(buffer->c_str());
	if (parse_success==tinyxml2::XML_NO_ERROR)	{

		XMLHandle xml_handle(xmlreply);
		XMLElement* xml_eml;
		xml_eml = xml_handle.FirstChildElement().ToElement();
		std::string ElementName = xml_eml->Name();

		if (ElementName=="status")	{
			cout << *buffer << endl;
			buffer->clear();
		}
		wxFrame* myself = (wxFrame*) that_quote;
		//cout << *buffer << endl;

		if (ElementName=="quote" || ElementName=="trade" )	{
			wxString mystring(buffer->c_str(),wxConvUTF8);

			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, QUOTE_CALLBACK);
			event.SetString(mystring);  // pass back the XML snippet
//			m_parent->GetEventHandler()->AddPendingEvent( event );
			myself->GetEventHandler()->AddPendingEvent( event );

			buffer->clear();

//			xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("symbol").ToElement();
//			if (xmlvalue!=0)	{
//				symbol=xmlvalue->GetText();
//			}
//			xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("bid").ToElement();
//			if (xmlvalue!=0)	{
//				std::stringstream strValue;
//
//				strValue << (xmlvalue->GetText());
//				strValue >> bid;
//			}
//
//			xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("ask").ToElement();
//			if (xmlvalue!=0)	{
//				std::stringstream strValue;
//
//				strValue << (xmlvalue->GetText());
//				strValue >> ask;
//			}
//
//			xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("timestamp").ToElement();
//			if (xmlvalue!=0)	{
//				timestamp=xmlvalue->GetText();
//			}


//			myself->ask(ask);
//			myself->bid(bid);
			//cout << "Time: " <<  timestamp << " Symbol: " << symbol << " Bid: " << bid << " Ask: " << ask << endl;
		}



//		if (ElementName=="trade")	{
//			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("symbol").ToElement();
//			if (xmlvalue!=0)	{
//				symbol=xmlvalue->GetText();
//			}
//			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("last").ToElement();
//			if (xmlvalue!=0)	{
//				std::stringstream strValue;
//
//				strValue << (xmlvalue->GetText());
//				strValue >> last_tick;
//			}
//
//			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("datetime").ToElement();
//			if (xmlvalue!=0)	{
//				timestamp=xmlvalue->GetText();
//			}
//			int last_int;
//
//			last_int=int(last_tick*100);
//
//			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, QUOTE_CALLBACK);
//			event.SetInt(last_int);  // pass some data along the event, a number in this case
//			m_parent->GetEventHandler()->AddPendingEvent( event );
//			myself->GetEventHandler()->AddPendingEvent( event );
//
//			//cout << "Time: " <<  timestamp << " Symbol: "<< symbol << " Trade: " << last_tick << " Ask: " << ask << endl;
//		}


	}
	else {
		cout <<"Incomplete payload..." << endl;
	}



	// How much did we write?
	result = size * nmemb;
	}

  return result;
}



float wxticker::last(std::string symbol) {

	char *req_url = NULL;
	std::string full_url=url_base+symbols;

	req_url = oauth_sign_url2(full_url.c_str(), NULL, OA_HMAC, NULL, cons_key.c_str(), cons_secret.c_str(), token_key.c_str(), token_secret.c_str());
	cout << req_url << endl;
	std::string url_string(req_url);

	curl = curl_easy_init();
	if (curl)
	{
	  curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
	  // Now set up all of the curl options
	  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	  curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &wxticker::writer);
	  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	}
	buffer.clear();
	result = curl_easy_perform(curl);
	if (result != CURLE_OK)
	{
	cout << "Error: [" << result << "] - " << errorBuffer << endl;
	}

	return last_tick;



}
