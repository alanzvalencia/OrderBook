

//#include <bits/stdc++.h>
#include <iostream>

#include <exception>
#include <vector>
#include <memory>
#include <algorithm>

#include <sched.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>

#include "Parser.h"
#include "OrderBook.h"

#include "Structures.h"

#define BOOST_TEST_MODULE MyTest

#define TEST_MAIN


#ifdef TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#endif

using namespace std;


#ifdef TEST_MAIN
BOOST_AUTO_TEST_CASE( main_test )
#else
int main()
#endif
{

  uint32_t counter = 0;
  size_t len;
  string line="";

  Parser parser;
  OrderBook orderBook;

  ifstream pFile("test-orders.log");

  if (pFile){

	  cout<<"---------Parsing Order Book-------"<<endl;

	   while (getline( pFile, line ))
	   {
		  OrderBookEntry * entry = new OrderBookEntry();
	      parser.ParseLine(line, * entry);

	      orderBook.AddOrder(entry);

	   }

	   cout << endl;

	   cout<<"---------Testing Order Book-------"<<endl;

	   orderBook.ProcessOrderBook();


  }
  else
  {
	    printf("Error occured opening test-orders.log file\n");
#ifndef TEST_MAIN
	   //  return -1;
#endif

  }

  pFile.close();

#ifdef TEST_MAIN

  BOOST_CHECK(orderBook.GetOrderBookCount() > 0 );

  BOOST_CHECK(orderBook.GetFirstTradeSide()==T_Buy);

#endif

#ifndef TEST_MAIN
  return 0;
#endif
}



