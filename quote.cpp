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
	std::cout << _symbol << _ask << std::endl;
}

void quote::bid(double bid)	{
	_bid=bid;
	std::cout << _symbol << _bid << std::endl;
}

void quote::last(double trade)	{
	_trade=trade;
	std::cout << _symbol << _trade << std::endl;
}

std::string quote::symbol(void)	{
	return _symbol;
}


int quote::order(void) {
	return _order_num;
}
