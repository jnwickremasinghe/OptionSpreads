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

//void ticker::init(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list)	{
//
//
//    m_Thread = boost::thread(&ticker::Entry, this, c_key, c_secret, t_key, t_secret, uri, symbol_list);
//	//start(c_key, c_secret, t_key, t_secret, uri, symbol_list);
//
//};


void ticker::start(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list)	{

	cons_key=c_key;
	cons_secret=c_secret;
	token_key=t_key;
	token_secret=t_secret;
	url_base=uri;
	symbols=symbol_list;

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
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ticker::writer);
	  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	}
	buffer.clear();
	result = curl_easy_perform(curl);
//	if (result == CURLE_OK)
//	{
//		XMLDocument xmlreply;
//		XMLElement* xmllast;
//		XMLNode *xmlfirstnode;
//		xmlreply.Parse(buffer.c_str());
//
//		xmlfirstnode=xmlreply.FirstChild();
//		xmlfirstnode=xmlfirstnode->FirstChild();
//		xmllast=xmlreply.FirstChildElement("response")->FirstChildElement("quotes")->FirstChildElement("quote")->FirstChildElement("last");
//
//		std::stringstream strValue;
//
//		strValue << (xmllast->GetText());
//		strValue >> last;
////		return last;
//	}
//  else
//  {
//	cout << "Error: [" << result << "] - " << errorBuffer;
//
//  }
}

ticker::~ticker()	{
	  // Always cleanup
	  curl_easy_cleanup(curl);
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
		XMLElement* xmllast;
		cout << *buffer << endl;
		XMLHandle xml_handle(xmlreply);

		xmllast=xml_handle.FirstChildElement("response").FirstChildElement("quotes").FirstChildElement("quote").FirstChildElement("last").ToElement();

		if (xmllast!=0)	{
			std::stringstream strValue;

			strValue << (xmllast->GetText());
			strValue >> last_tick;
			buffer->clear();
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

	return last_tick;

//	char *req_url = NULL;
//	float last;
//
//	std::string full_url=url_base+symbol;
//
//    req_url = oauth_sign_url2(full_url.c_str(), NULL, OA_HMAC, NULL, cons_key.c_str(), cons_secret.c_str(), token_key.c_str(), token_secret.c_str());
//
//    std::string url_string(req_url);
//
//	cout << "Retrieving " << url_string << endl;
//
//
//
//
//	if (curl)
//	{
//		curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
//		// Attempt to retrieve the remote page
//		buffer.clear();
//		result = curl_easy_perform(curl);
//
//		// Did we succeed?
//		if (result == CURLE_OK)
//		{
//			XMLDocument xmlreply;
//			XMLElement* xmllast;
//			XMLNode *xmlfirstnode;
//			xmlreply.Parse(buffer.c_str());
//
//			xmlfirstnode=xmlreply.FirstChild();
//			xmlfirstnode=xmlfirstnode->FirstChild();
//			xmllast=xmlreply.FirstChildElement("response")->FirstChildElement("quotes")->FirstChildElement("quote")->FirstChildElement("last");
//
//			std::stringstream strValue;
//
//			strValue << (xmllast->GetText());
//			strValue >> last;
//			return last;
//		}
//	  else
//	  {
//		cout << "Error: [" << result << "] - " << errorBuffer;
//		return -1;
//	  }
//	}
//	else
//		return -1;




}
