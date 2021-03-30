/*
 * Structures.h
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_


#define Debug(...) {fprintf(stderr, __VA_ARGS__);}

#ifdef __ILP32__
   #define PTR unsigned long
#else
   #define PTR uint64_t
#endif

enum Trade {
   T_None,
   T_Buy,
   T_Sell
};

struct TradeMessage {

	TradeMessage()
	:tradeQty(0),
	 tradePrice(0)
	{}

   uint32_t tradeQty;
   float tradePrice;

   void printContent() {
	   Debug("TradeMessage QTY: %u. PRICE: %f.\n",
    		  tradeQty,
    		  tradePrice);
   }
};

struct OrderBookEntry
{
	OrderBookEntry()
	: orderID(0)
	   , orderPrice(0)
	   , qty(0)
	   , orderType(T_None),
	   Next(0),
	   Prev(0)
	   {}

	//unsigned long OrderID;
    //string OrderSide;
    //float LimitPrice;
    //int Quantity;

	   void printContent() {
		   Debug("OrderBookEntry orderID: %u. orderPrice: %f. qty: %u.\n",
				   orderID,
				   orderPrice,
				   qty);
	   }

	   uint32_t orderID;
	   float orderPrice;
	   uint32_t qty;
	   Trade orderType;

	   OrderBookEntry *Next;
	   OrderBookEntry *Prev;
};

#endif /* STRUCTURES_H_ */
