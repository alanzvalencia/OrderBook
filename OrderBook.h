

/*
 * OrderBook.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */

#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "Logger.h"
#include <memory>
#include <vector>

#include <stdlib.h>
#include <cassert> // for assert()
#include <exception>
#include <sys/time.h>

#include <stdexcept>

#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>

#include "Structures.h"

#include "OrderList.h"

using namespace std;

class OrderBook
{
public:

	typedef map<float, OrderList<OrderBookEntry>> OrderCollection;
	typedef unordered_map<uint32_t, OrderBookEntry*> OrderHash;

	OrderBook();
	void LoadOrderBook();
	void AddOrder(OrderBookEntry* ole) ;
	void ProcessOrderBook();
	void DisplayMatch(OrderBookEntry* buy, OrderBookEntry* sell);
	void DisplayOrderBook();
	unsigned long getuseconds();
	unsigned long GetOrderBookCount();
	Trade GetFirstTradeSide();
	void PrintBook();
	void growBuffer(char *&buf, int &max_buffer);
	void safeCopyToBuffer(char *&dest_root, const char *source, int &index, int &max_buffer);
	virtual ~OrderBook();

private:

	OrderCollection buy_book_map_;
	OrderCollection sell_book_map_;

	Logger logger_;

	OrderHash orders_;

	unsigned long long recent_trade_price_;
	uint32_t recent_trade_qty_;

	unsigned long execution_id;

	void checkCross();
};

#endif /* ORDERBOOK_H_ */
