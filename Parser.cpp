/*
 * Parser.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */

#include "Parser.h"

Parser::Parser()
{
	// TODO Auto-generated constructor stub

}

void Parser::ParseLine(string line, OrderBookEntry &entry)
{
   auto arrayStr=split(line,"|");
   char *eptr;

   if (arrayStr.size()>3)
   {
	   entry.orderID=(uint32_t)atoi((char *) arrayStr[0].c_str());

	   if (arrayStr[1].compare("B")==0)
	   {
		   entry.orderType=T_Buy;
		   printf("orderID: %d T_Buy\n", entry.orderID);
	   }
	   else if (arrayStr[1].compare("S")==0)
	   {
		   entry.orderType=T_Sell;
		   printf("orderID: %d T_Sell\n", entry.orderID);
	   }
	   else
	   {
		   entry.orderType=T_None;
		   printf("orderID: %d T_None\n", entry.orderID);
	   }

	   entry.orderPrice=strtod((char *) arrayStr[2].c_str(), &eptr);
	   entry.qty=(uint32_t)atoi((char *) arrayStr[3].c_str());

	   entry.printContent();
   }

}

vector<string> Parser::split(const string str, const string delimiters){

   vector <string> tokens;
   // Skip delimiters at beginning.
       string::size_type lastPos = str.find_first_not_of(delimiters, 0);
       // Find first "non-delimiter".
       string::size_type pos     = str.find_first_of(delimiters, lastPos);
       //tokens.reserve(20);
       //long WU=0;
       while (string::npos != pos || string::npos != lastPos)
       {
           // Found a token, add it to the vector.
           tokens.push_back(str.substr(lastPos, pos - lastPos));
           // Skip delimiters.  Note the "not_of"
           lastPos = str.find_first_not_of(delimiters, pos);
           // Find next "non-delimiter"
           pos = str.find_first_of(delimiters, lastPos);
       }
	return tokens;
}

Parser::~Parser()
{
	// TODO Auto-generated destructor stub
}
