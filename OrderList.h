/*
 * OrderList.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */
#ifndef ORDERLIST_H_
#define ORDERLIST_H_

#include <stdint.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "OrderBaseList.h"

#include "Structures.h"

template <typename T>

class OrderList: public OrderBaseList<T>
{
public:
	OrderList()
	  : quantity(0)
	{}

	   void addNode(T *input) {
	      quantity += input->qty;
	      OrderBaseList<T>::addNode(input);
	   }

	   void removeNode(T *input) {
	      quantity -= input->qty;
	      OrderBaseList<T>::removeNode(input);
	   }

	   void changeNodeQuantity(T *input, uint32_t new_quantity) {
	      quantity -= input->qty;
	      quantity += new_quantity;
	      input->qty = new_quantity;
	   }

	   void clearLevel() {
	      T *first = OrderBaseList<T>::getFirst();
	      while (first != OrderBaseList<T>::getLast()) {
	         removeNode(first);
	         first = first->Prev;
	      }
	      removeNode(first);
	   }

	   void printLevel(char tag, char *&buffer, int &index, int &max_buffer) {
	      T *last = OrderBaseList<T>::getLast();
	      while (last != OrderBaseList<T>::getFirst()) {

	         if (index + 50 > max_buffer) growBuffer(buffer, max_buffer);
	         index += sprintf(&buffer[index], "%c %u ", tag, last->qty);

	         last = last->Next;
	      }

	      if (index + 50 > max_buffer) growBuffer(buffer, max_buffer);
	      index += sprintf(&buffer[index], "%c %u ", tag, last->qty);
	   }

	   uint32_t getQuantity() const { return quantity; }


	   void growBuffer(char *&buf, int &max_buffer) {
	      int old_max = max_buffer;
	      max_buffer *= 2;
	      buf = (char *)realloc(buf, max_buffer * sizeof(char));

	      // null terminate the new memory
	      memset(&buf[old_max], '\0', max_buffer - old_max);
	   }

	   //-----------------------------------------------------------------------------
	   void safeCopyToBuffer(char *&dest_root, const char *source, int &index, int &max_buffer) {
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

	//virtual ~OrderList();

private:
   uint32_t quantity;
};

#endif /* ORDERLIST_H_ */
