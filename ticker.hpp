/*
 * quote.hpp
 *
 *  Created on: Feb 9, 2013
 *      Author: joseph
 */

#ifndef QUOTE_HPP_
#define QUOTE_HPP_

#include <string>
#include "quote.hpp"
#include <curl/curl.h>

static void* this_quote;

class ticker {

public:
	ticker(void);
	void init(quote* quote_ptr);
	void start(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string symbol_list);
	~ticker(void);
	float last(std::string);
	void stop(void);

	// Our curl objects
	CURL *curl;
	CURLcode result;


private:
	std::string cons_key;
	std::string cons_secret;
	std::string token_key;
	std::string token_secret;
	std::string url_base;
	std::string symbols;



	char errorBuffer[256];
	// Write all expected data in here
	static int writer(char *data, size_t size, size_t nmemb,
            std::string *buffer);

};
#endif /* QUOTE_HPP_ */
