#include "quote.hpp"
#include <iostream>
#include <string>


quote::quote(std::string this_symbol, int order_num )	{
	_symbol=this_symbol;
	_order_num=order_num;
	std::cout << _symbol << " created, order: " << _order_num <<std::endl;
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
	_trade=trade;
}

std::string quote::symbol(void)	{
	return _symbol;
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

int quote::save(void)	{
	//write current value of quote out to database
	//for now just dump to file :)
	std::cout << _symbol << "," << _bid << "," << _ask << "," << _trade << "," << _date	<< "," << _time << std::endl;

	return 0;
}
