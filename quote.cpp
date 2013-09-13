#include "quote.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <sqlite3.h>


quote::quote(std::string this_symbol, int order_num, std::string db_connection )	{
	_symbol=this_symbol;
	_order_num=order_num;

	std::cout << _symbol << " created, order: " << _order_num <<std::endl;

	if (!db_connection.empty())	{

		int rc = sqlite3_open(db_connection.c_str(), &db);
		if (rc)	{
			std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);

		}
	}
}

quote::~quote()	{
	std::cout << _symbol << " destroyed." <<std::endl;
}

void quote::ask(double ask)	{
	_ask=ask;
}

void quote::bid(double bid)	{
	_bid=bid;
}

void quote::last(double trade)	{
	_pct_chg= (trade-_prior_trade)/_prior_trade;
	_prior_trade=_trade;
	_trade=trade;
}

std::string quote::symbol(void)	{
	return _symbol;
}

double quote::pct_chg(void)	{
	return _pct_chg;
}


int quote::order(void) {
	return _order_num;
}

void quote::date(std::string date_value)	{
	_date=date_value;
}
void quote::time(std::string time_value)	{
	_time=time_value;
}

int quote::save(std::string tick_type)	{
	//write current value of quote or trade out to database
	if (db)	{

		std::stringstream ss;
		if (tick_type=="trade")	{
			ss << "insert into quote (date,time,symbol,type,value) values";
			ss << "('" << _date <<  "','" << _time << "','" << _symbol << "','last'," << _trade << ")";
			std::string quote_sql=ss.str();
			//std::cout << quote_sql << std::endl;
			int retval = sqlite3_exec(db, quote_sql.c_str(), NULL, 0, &zErrMsg);
			if (retval){
				std::cerr << "Error writing to db: " << zErrMsg << std::endl;
			}
		}
		if (tick_type=="quote")	{
			int retval = 0;
			std::string quote_sql;
			ss << "insert into quote (date,time,symbol,type,value) values";
			ss << "('" << _date <<  "','" << _time << "','" << _symbol << "','bid'," << _bid << ")";
			quote_sql=ss.str();
			//std::cout << quote_sql << std::endl;
			retval = sqlite3_exec(db, quote_sql.c_str(), NULL, 0, &zErrMsg);
			if (retval){
				std::cerr << "Error writing to db: " << zErrMsg << std::endl;
			}
			ss.str("");
			ss << "insert into quote (date,time,symbol,type,value) values";
			ss << "('" << _date <<  "','" << _time << "','" << _symbol << "','ask'," << _ask << ")";
			quote_sql=ss.str();
			//std::cout << quote_sql << std::endl;
			retval = sqlite3_exec(db, quote_sql.c_str(), NULL, 0, &zErrMsg);
			if (retval){
				std::cerr << "Error writing to db: " << zErrMsg << std::endl;
			}

		}

	} else	{
		//no db connection, write to console instead
		if (tick_type=="quote")	{
			std::cout << _symbol << ",bid," << _bid << "," << _date << "," << _time << std::endl;
			std::cout << _symbol << ",ask," << _ask << "," << _date << "," << _time << std::endl;
		} else	{
			std::cout << _symbol << ",trade," << _trade << "," << _date << "," << _time << std::endl;
		}
	}

	return 0;
}
