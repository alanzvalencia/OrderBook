/*
 * Parser.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */

#ifndef PARSER_H_
#define PARSER_H_

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

#include "Structures.h"

using namespace std;

class Parser
{
public:
	Parser();

	void ParseLine(string line, OrderBookEntry &entry);

	vector<string> split(const string str, const string delimiters);

	virtual ~Parser();
};

#endif /* PARSER_H_ */
