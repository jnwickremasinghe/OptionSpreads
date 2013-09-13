//quote object that retrieves market data
//with TradeKing, uses oauth
#include <iostream>
#include <oauth.h>
#include <sstream>
#include "tinyxml2.h"
#include "ticker.hpp"




using namespace tinyxml2;
using namespace std;

static std::string buffer;
static std::string symbol;
static std::string timestamp;

ticker::ticker(wxFrame* parent)	{
	m_parent=parent;
	that_quote=(void*) parent;
	cout <<"ticker created" << endl;
}

//void ticker::init(quote* quote_ptr)	{
//se
//	std::string symbol;
//
//};


void ticker::init(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list)	{

	cons_key=c_key;
	cons_secret=c_secret;
	token_key=t_key;
	token_secret=t_secret;
	url_base=uri;
	symbols=symbol_list;

}

void ticker::get_data(std::string url_base,std::string symbols) {
	//function to make synchronous call to curl


	char *req_url = NULL;
	std::string full_url=url_base+symbols;

	req_url = oauth_sign_url2(full_url.c_str(), NULL, OA_HMAC, NULL, cons_key.c_str(), cons_secret.c_str(), token_key.c_str(), token_secret.c_str());

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
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ticker::writer);
	  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

	}
	buffer.clear();

	result = curl_easy_perform(curl);
	if (result != CURLE_OK) {
		cout << buffer << endl;
	}

}


// This is the writer call back function used by curl
int ticker::writer(char *data, size_t size, size_t nmemb,
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

		wxFrame* myself = (wxFrame*) that_quote;
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED);


		if (ElementName=="status")	{
			event.SetId(Status);
			event.SetInt(Status);
		} else

		if (ElementName=="quote" || ElementName=="trade" )	{
			event.SetId(QUOTE_CALLBACK);
			event.SetInt(Stream);

		} else

		if (ElementName=="response"  )	{
			xml_eml = xml_handle.FirstChildElement().FirstChildElement().ToElement();
			std::string SecondElementName = xml_eml->Name();
//			cout << SecondElementName << endl;
			if (SecondElementName=="prices")	{
				event.SetId(Strikes_Callback);

				}
			else {

				event.SetId(QUOTE_CALLBACK);
				event.SetInt(Stream);
			}
		}

		else {
			cout << ElementName << endl;
			event.SetId(QUOTE_CALLBACK);
			event.SetInt(Unknown);
		}

		wxString mystring(buffer->c_str(),wxConvUTF8);
		event.SetString(mystring);  // pass back the XML snippet
		myself->GetEventHandler()->AddPendingEvent( event );
		buffer->clear();
	}



	// How much did we write?
	result = size * nmemb;
	}

  return result;
}

wxThread::ExitCode ticker::Entry()	{

	char *req_url = NULL;
	std::string full_url=url_base+symbols;

	req_url = oauth_sign_url2(full_url.c_str(), NULL, OA_HMAC, NULL, cons_key.c_str(), cons_secret.c_str(), token_key.c_str(), token_secret.c_str());

	std::string url_string(req_url);

	cout << url_string << endl;

	for (int retry=0;retry<10;retry++)	{
		curl = curl_easy_init();
		if (curl)
		{
		  curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
		  // Now set up all of the curl options
		  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		  curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ticker::writer);
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		}
		buffer.clear();


		result = curl_easy_perform(curl);
		if (result != CURLE_OK) {
			//error in curl - need to notify main thread
			wxString errorstring(errorBuffer,wxConvUTF8);
			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, ERR_CALLBACK);
			event.SetString(errorstring);  // pass back the error message
			event.SetInt(result); //pass back error message
			wxFrame* myself = (wxFrame*) that_quote;
			myself->GetEventHandler()->AddPendingEvent( event );
			cout << "Error: [" << result << "] - " << errorBuffer << endl;
			cout <<"Cleaning up curl" << endl;
			curl_easy_cleanup(curl);
			cout << "Waiting 10 seconds before retrying" << endl;
			cout << "Retry #" << retry << endl;
			sleep(10); //wait for 10 seconds - not portable!!
		}
	}


	return 0;

}

ticker::~ticker()	{
	  // Always cleanup
	curl_easy_cleanup(curl);
	cout<< "ticker destroyed" << endl;
}
