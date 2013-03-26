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

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
//#include "boost_example.hpp"


class client
{
public:
  client(boost::asio::io_service& io_service, boost::asio::ssl::context& context, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : socket_(io_service, context)
  {
    socket_.set_verify_mode(boost::asio::ssl::context::verify_peer);
    socket_.set_verify_callback(boost::bind(&client::verify_certificate, this, _1, _2));

    boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
  }

  bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
  {
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying:\n" << subject_name << std::endl;

    return true;
  }

  void handle_connect(const boost::system::error_code& error)
  {
    if(!error){
      std::cout << "Connection OK!" << std::endl;
      socket_.async_handshake(boost::asio::ssl::stream_base::client, boost::bind(&client::handle_handshake, this, boost::asio::placeholders::error));
    }else{
      std::cout << "Connect failed: " << error.message() << std::endl;
    }
  }


private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  char reply_[0x1<<16];
  std::string new_url_base;
  std::string new_cons_key;
  std::string new_cons_secret;
  std::string new_token_key;
  std::string new_token_secret;
  std::string new_server;

public:

  void handle_handshake(const boost::system::error_code& error)
  {
    if(!error){
      std::cout << "Sending request: " << std::endl;

      std::stringstream request_;

      request_ << "GET " << new_url_base << " HTTP/1.1\r\n";
      request_ << "Host: " << new_server << "\r\n";
      request_ << "Accept-Encoding: *\r\n";
      request_ << "\r\n";

      std::cout << request_.str() << std::endl;

      boost::asio::async_write(socket_, boost::asio::buffer(request_.str()), boost::bind(&client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }else{
      std::cout << "Handshake failed: " << error.message() << std::endl;
    }
  }

  void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error){
      std::cout << "Sending request OK!" << std::endl;
      boost::asio::async_read(socket_, boost::asio::buffer(reply_, bytes_transferred), boost::bind(&client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }else{
      std::cout << "Write failed: " << error.message() << std::endl;
    }
  }

  void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error){
      std::cout << "Reply: ";
      std::cout <<"No error!" << endl;
      //std::cout << reply_ << endl;
      std::cout.write(reply_, bytes_transferred);
      std::cout << "\n";

    }else{
      std::cout << "Read failed: " << error.message() << std::endl;
    }
  }


void set_new_params(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string server) {
		new_cons_key=c_key;
		new_cons_secret=c_secret;
		new_token_key=t_key;
		new_token_secret=t_secret;
		new_url_base=uri;
		new_server=server;
	}



};

newquote::newquote()	{

}

void newquote::set_newquote_params(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string server)	{

	new2_cons_key=c_key;
	new2_cons_secret=c_secret;
	new2_token_key=t_key;
	new2_token_secret=t_secret;
	new2_url_base=uri;
	new2_server=server;
};

void newquote::start(int N)
{
    m_Thread = boost::thread(&newquote::run, this);
}

void newquote::run() {


	    	try{
	    			boost::asio::io_service io_service;

	    			boost::asio::ip::tcp::resolver resolver(io_service);
	    			boost::asio::ip::tcp::resolver::query query(new2_server, "443");
	    			boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
	    			boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
	    			context.add_verify_path("/home/joseph/workspace2/BoostExamples/certs");

	    		//    context.load_verify_file("/home/mint/workspace/BoostExamples/certs/verisign.pem");

	    			client c(io_service, context, iterator);

	    			c.set_new_params( new2_cons_key, new2_cons_secret, new2_token_key, new2_token_secret,new2_url_base.substr(25,std::string::npos), new2_server);
	    			//boost::asio::io_service::work work(io_service);
	    			io_service.run();
	    		    boost::posix_time::seconds workTime(3);
	    		}
	    		catch (std::exception& e){
	    			std::cerr << "Exception: " << e.what() << "\n";
	    		}


	  };


newquote::~newquote()	{
	std::cout <<"We outta here" << endl;
}


int main2(int argc, char* argv[])
{
  try{
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query("google.com", "443");
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
    context.add_verify_path("/home/joseph/workspace2/BoostExamples/certs");

//    context.load_verify_file("/home/mint/workspace/BoostExamples/certs/verisign.pem");
    client c(io_service, context, iterator);
    io_service.run();


  }catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  std::cin.get();
  return 0;
}



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




//(std::string c_key, std::string c_secret, std::string t_key, std::string t_secret, std::string uri, std::string server) {


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



