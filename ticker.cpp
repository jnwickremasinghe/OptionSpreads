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
static float last_tick;
static float bid;
static float ask;
static std::string symbol;
static std::string timestamp;

ticker::ticker(void)	{
	cout <<"Ticker created" << endl;
}

void ticker::init(std::string symbol)	{


    m_Thread = boost::thread(&ticker::last, this, symbol);
	//start(c_key, c_secret, t_key, t_secret, uri, symbol_list);

};


void ticker::start(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list)	{

//	cout << cons_key << endl;
	cout << c_key << endl;

	cons_key=c_key;
	cons_secret=c_secret;
	token_key=t_key;
	token_secret=t_secret;
	url_base=uri;
	symbols=symbol_list;



}

ticker::~ticker()	{
	  // Always cleanup
	curl_easy_cleanup(curl);
	cout<< "ticker destroyed" << endl;
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

		XMLElement* xmlvalue;
		XMLHandle xml_handle(xmlreply);
		XMLElement* xml_eml;
		xml_eml = xml_handle.FirstChildElement().ToElement();
		std::string ElementName = xml_eml->Name();

		if (ElementName=="status")	{
			cout << *buffer << endl;
		}
		//cout << *buffer << endl;
		buffer->clear();
		if (ElementName=="quote")	{
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

			xmlvalue= xml_handle.FirstChildElement("quote").FirstChildElement("timestamp").ToElement();
			if (xmlvalue!=0)	{
				timestamp=xmlvalue->GetText();
			}

			cout << "Time: " <<  timestamp << " Symbol: " << symbol << " Bid: " << bid << " Ask: " << ask << endl;
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
				strValue >> last_tick;
			}

			xmlvalue= xml_handle.FirstChildElement("trade").FirstChildElement("timestamp").ToElement();
			if (xmlvalue!=0)	{
				timestamp=xmlvalue->GetText();
			}

			cout << "Time: " <<  timestamp << " Symbol: "<< symbol << " Trade: " << last_tick << " Ask: " << ask << endl;
		}


	}
	else {
		cout <<"Incomplete payload..." << endl;
	}



	// How much did we write?
	result = size * nmemb;
	}

  return result;
}



float ticker::last(std::string symbol) {

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
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ticker::writer);
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
