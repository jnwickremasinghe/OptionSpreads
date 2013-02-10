//quote object that retrieves market data
//with TradeKing, uses oauth
#include <iostream>
#include <oauth.h>
#include <sstream>
#include "tinyxml2.h"
#include "quote.hpp"


using namespace tinyxml2;
using namespace std;

static std::string buffer;

quote::quote(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri)	{

	cons_key=c_key;
	cons_secret=c_secret;
	token_key=t_key;
	token_secret=t_secret;
	url_base=uri;

	curl = curl_easy_init();
	if (curl)
	{
	  // Now set up all of the curl options
	  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	  curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &quote::writer);
	  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	}
}

quote::~quote()	{
	  // Always cleanup
	  curl_easy_cleanup(curl);
}

// This is the writer call back function used by curl
int quote::writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
{
  // What we will return
  int result = 0;

  // Is there anything in the buffer?
  if (buffer != NULL)
  {
    // Append the data to the buffer
    buffer->append(data, size * nmemb);

    // How much did we write?
    result = size * nmemb;
  }

  return result;
}


void quote::start(void)	{



}

float quote::last(std::string symbol) {

	char *req_url = NULL;
	float last;

	std::string full_url=url_base+symbol;

    req_url = oauth_sign_url2(full_url.c_str(), NULL, OA_HMAC, NULL, cons_key.c_str(), cons_secret.c_str(), token_key.c_str(), token_secret.c_str());

    std::string url_string(req_url);

	cout << "Retrieving " << url_string << endl;




	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
		// Attempt to retrieve the remote page
		buffer.clear();
		result = curl_easy_perform(curl);

		// Did we succeed?
		if (result == CURLE_OK)
		{
			XMLDocument xmlreply;
			XMLElement* xmllast;
			XMLNode *xmlfirstnode;
			xmlreply.Parse(buffer.c_str());

			xmlfirstnode=xmlreply.FirstChild();
			xmlfirstnode=xmlfirstnode->FirstChild();
			xmllast=xmlreply.FirstChildElement("response")->FirstChildElement("quotes")->FirstChildElement("quote")->FirstChildElement("last");

			std::stringstream strValue;

			strValue << (xmllast->GetText());
			strValue >> last;
			return last;
		}
	  else
	  {
		cout << "Error: [" << result << "] - " << errorBuffer;
		return -1;
	  }
	}
	else
		return -1;




}
