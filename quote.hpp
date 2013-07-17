
#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <sqlite3.h>

class quote {
public:
	quote(std::string symbol, int order_num, std::string db_connection);
	~quote();
	void last( double last_value);
	void bid( double bid_value);
	void ask (double ask_value);
	std::string symbol(void);
	double last(void);
	double pct_chg(void);

	int order(void);
	void date(std::string date_value);
	void time(std::string time_value);
	int save(std::string tick_type);


private:

	double _trade;
	double _prior_trade;
	double _pct_chg;
	double _ask;
	double _bid;
	std::string _symbol;
	int _order_num;
	std::string _date;
	std::string _time;

	sqlite3 *db;
	char *zErrMsg;
	sqlite3_stmt *insert_stmt;

};

#endif // quote_h
