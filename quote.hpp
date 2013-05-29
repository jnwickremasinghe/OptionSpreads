
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
	void date(std::string date_value);
	void time(std::string time_value);
	int save(void);


private:

	double _trade;
	double _ask;
	double _bid;
	std::string _symbol;
	int _order_num;
	std::string _date;
	std::string _time;
};

#endif // quote_h
