#include "quote.hpp"
#include <iostream>
#include <string>


quote::quote(std::string this_symbol)	{
	_symbol=this_symbol;
	std::cout << _symbol << " created." <<std::endl;
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
