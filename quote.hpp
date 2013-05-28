
#ifndef QUOTE_H
#define QUOTE_H

#include <string>

class quote {
public:
	quote(std::string symbol, int order_num);
	~quote();
	void last( double last_value);
	void bid( double bid_value);
	void ask (double ask_value);
	std::string symbol(void);
	double last(void);
	int order(void);

private:

	double _trade;
	double _ask;
	double _bid;
	std::string _symbol;
	int _order_num;

};

bool operator< (const quote &lhs, quote &rhs);

#endif // quote_h
