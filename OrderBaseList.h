/*
 * OrderBaseList.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: Alan Z. Valencia
 */

#ifndef ORDERBASELIST_H_
#define ORDERBASELIST_H_

#include <stdio.h>
#include <iostream>

using namespace std;

template <typename T>
class OrderBaseList
{
public:
	OrderBaseList()
	   : first(0)
	   , last(0)
	   {}

	   void addNode(T *input) {
	      if (first == 0) {
	         first = input;
	         last = first;
	         return;
	      }

	      first->Next = input;
	      input->Prev = first;
	      first = input;
	   }

	   void removeNode(T *target) {
	      // Skip self and delete if straddled
	      if (target->Prev != 0 && target->Next != 0) {
	         target->Prev->Next = target->Next;
	         target->Next->Prev = target->Prev;

	    	  //target->Prev=0;
	    	  //target->Next=0;
	      }
	      // Edge - last deleted
	      else if (target == last && target->Next != 0) {
	         last = target->Next;
	         last->Prev = 0;
	      }
	      // Edge - first deleted
	      else if (target == first && target->Prev != 0) {
	         first = target->Prev;
	         if(first!=0)
	        	 first->Next = 0;
	      }
	      // Edge - single element list
	      else {
	         first = 0;
	         last = 0;
	         return;
	      }
	   }

	   T *getFirst() const { return first; }
	   T *getLast() const { return last; }


	#ifdef DEBUG
	   void printList() {
	      T *head = last->Prev;
	      while (head != last) {
	         fprintf(stderr, "NODE: ");
	         head->printSelf();
	         head = head->Prev;
	      }
	      fprintf(stderr, "LAST NODE: ");
	      head->printSelf();
	   }
	#endif

	//virtual ~OrderBaseList();

private:
   T *first;
   T *last;
};

#endif /* ORDERBASELIST_H_ */
