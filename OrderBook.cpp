/*
 * OrderBook.cpp
 *
 *  Created on: Mar 17, 2021
 *      Author: Alan Z. Valencia
 */

#include "OrderBook.h"

OrderBook::OrderBook()
{
	// TODO Auto-generated constructor stub
	execution_id=3000;
}

void OrderBook::LoadOrderBook()
{

}

void OrderBook::AddOrder(OrderBookEntry* entry)
{
   checkCross();

   auto ooit = orders_.find(entry->orderID);
   if (ooit != orders_.end()) {
      printf("Duplicate OrderBookEntry\n");
      delete entry;
      return;
   }

   if (entry->qty==0)
	   return;

   OrderCollection &map = entry->orderType == T_Buy ? buy_book_map_ : sell_book_map_;

   std::pair<typename OrderCollection::iterator, bool> ret;
   ret = map.insert(
      std::pair<float, OrderList<OrderBookEntry>>(
    		  entry->orderPrice, OrderList<OrderBookEntry>()));
   ret.first->second.addNode(entry);
   orders_[entry->orderID] = entry;
}

void OrderBook::ProcessOrderBook()
{
	 uint32_t trade_qty = 0;
     float trade_price=0;
     unsigned long MatchCount=0;

     vector<uint32_t> cleanOrder;

	   //for (auto it = buy_book_map_.rbegin(); it != buy_book_map_.rend(); ++it)
       for (auto &it : orders_)
	   {
		   trade_qty=it.second->qty;
		   trade_price=it.second->orderPrice;

	      if ( (trade_qty != 0) && (it.second->orderType==T_Buy)) {

	    	     //Find the price from Sell
	    	     auto sit = sell_book_map_.find(trade_price);

	    	     if (sit != sell_book_map_.end()) {
	    	        //Price found.
	    	    	 MatchCount++;
	    	    	 cout<<"Found Price: "<<trade_price<<endl;

	    	    	 OrderBookEntry *sell = sit->second.getLast();

	    	    	 DisplayMatch(it.second, sell);

	    	         if (trade_qty <= sell->qty) {

	    	        	cleanOrder.push_back(it.second->orderID);

	    	         }
	    	         else {
	    	        	 it.second->qty-=sell->qty;
	    	        	 //cout<<"it.second->qty: "<<it.second->qty<<endl;
	    	         }


	    	    	//Remove orders as matched if trade depletes them

					while (trade_qty > 0) {
						OrderBookEntry *tail = sit->second.getLast();
						if (tail==0)
							break;

					   if (tail->qty > trade_qty) {
						  trade_qty = 0;
					   }
					   else {
						  trade_qty -= tail->qty;
					   }

					   if (trade_qty >= tail->qty) {
						  sit->second.removeNode(tail);
						  cleanOrder.push_back(tail->orderID);
						  //auto odit = orders_.find(tail->orderID);
						  //delete odit->second;
						  //orders_.erase(odit);
					   }
					   else {
						  sit->second.changeNodeQuantity(tail, tail->qty - trade_qty);
					   }
					}

	    	     }

	      }
	   }

       //cout<<"----------Start Cleaning Order Book------"<<endl;
       for (auto i = cleanOrder.begin(); i != cleanOrder.end(); ++i)
       {
 		  auto odit = orders_.find(*i);
 		  delete odit->second;
 		  orders_.erase(odit);
       }


       if (MatchCount==0)
       {
    	   cout<<"THERE WERE NO MATCHES"<<endl;
       }

       cout<<endl;

       cout<<"----------Order Book Content After Processing------"<<endl;
       DisplayOrderBook();

}

void OrderBook::DisplayMatch(OrderBookEntry* buy, OrderBookEntry* sell)
{
	execution_id++;
	unsigned long id=execution_id + getuseconds();
    printf("Match: %u|B|%f|%u|%lu %u|S|%f|%u|%lu \n", buy->orderID,buy->orderPrice,sell->qty,
    		id, sell->orderID,sell->orderPrice,sell->qty, id);
}

void OrderBook::DisplayOrderBook()
{
	string Side="";

    for (auto &it : orders_)
	{
    	Side=it.second->orderType==T_Buy?"B":"S";
    	printf("%u|%s|%f|%u\n", it.second->orderID, Side.c_str(), it.second->orderPrice, it.second->qty);
	}
}

unsigned long OrderBook::getuseconds()
{
        struct timeval tp;
        gettimeofday(&tp, NULL);
        unsigned long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

        return ms;
}

unsigned long OrderBook::GetOrderBookCount()
{
	return orders_.size();
}

Trade OrderBook::GetFirstTradeSide()
{
	if (orders_.size()>0)
		return orders_.begin()->second->orderType;

	return T_None;
}

void OrderBook::PrintBook() {
   int max_buffer = 500;
   char *buffer = (char*)calloc(max_buffer, sizeof(char));
   int index = 0;

   for (auto it = sell_book_map_.rbegin(); it != sell_book_map_.rend(); ++it) {
      if (it->second.getQuantity() != 0) {

         if (index + 100 > max_buffer) growBuffer(buffer, max_buffer);
         index += sprintf(&buffer[index], "%.2f ", it->first / 100.);

         it->second.printLevel('S', buffer, index, max_buffer);

         if (index + 10 > max_buffer) growBuffer(buffer, max_buffer);
         index += sprintf(&buffer[index], "\n");
      }
   }
   safeCopyToBuffer(buffer, "\n", index, max_buffer);
   for (auto it = buy_book_map_.rbegin(); it != buy_book_map_.rend(); ++it) {
      if (it->second.getQuantity() != 0) {

         if (index + 100 > max_buffer) growBuffer(buffer, max_buffer);
         index += sprintf(&buffer[index], "%.2f ", it->first / 100.);

         it->second.printLevel('B', buffer, index, max_buffer);

         if (index + 10 > max_buffer) growBuffer(buffer, max_buffer);
         index += sprintf(&buffer[index], "\n");
      }
   }

   if (index + 10 > max_buffer) growBuffer(buffer, max_buffer);
   index += sprintf(&buffer[index], "\n");

   logger_.print(buffer);
   free(buffer);
}

void OrderBook::growBuffer(char *&buf, int &max_buffer) {
   int old_max = max_buffer;
   max_buffer *= 2;
   buf = (char *)realloc(buf, max_buffer * sizeof(char));

   // null terminate the new memory
   memset(&buf[old_max], '\0', max_buffer - old_max);
}

void OrderBook::safeCopyToBuffer(char *&dest_root, const char *source, int &index, int &max_buffer) {
   int len = strlen(source);
   if (len == 0) return;

   while (index + len >= max_buffer) {
      int old_max = max_buffer;
      max_buffer *= 2;
      dest_root = (char *)realloc(dest_root, max_buffer * sizeof(char));

      // null terminate the new memory
      memset(&dest_root[old_max], '\0', max_buffer - old_max);
   }

   strncpy(&dest_root[index], source, len);
   index += len;
}

void OrderBook::checkCross()
{
   if (sell_book_map_.empty() || buy_book_map_.empty()) {
      return;
   }
   auto sit = sell_book_map_.begin();
   auto bit = buy_book_map_.end();
   --bit;
   if (sit->first <= bit->first) {
      printf("Crossed Book\n");
   }
}

OrderBook::~OrderBook()
{
	// TODO Auto-generated destructor stub
}


