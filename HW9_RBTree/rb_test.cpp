/*
 * rb_test.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "rbbst.h"
#include <string>
/* -----------------------------------------------------
 * main for testing
 ------------------------------------------------------*/

int main (void)
{
  int a[100];

  // Put the numbers 0..99 in the array in a random order
  for (int i = 0; i < 100; i ++) a[i] = i;
	for (int i = 99; i > 0; i --)
	{ 
		int j = rand () % (i+1);
		int b = a[i]; a[i] = a[j]; a[j] = b;
	}

  RedBlackTree<int, int> *T = new RedBlackTree<int, int> ();
  // Put the numbers (and their squares) into the tree in random order.
 for (int i = 0; i < 100; i ++)
  {
		//std::cout<<"adding"<<a[i]<<std::endl;
      T->add (a[i], a[i]*a[i]);
}

/*T->add(10,10);
T->add(20,20);
T->add(30,30);
T->add(15,15);
T->add(25,25);
T->add(12,12);
T->add(5,5);
T->add(3,3);
T->add(8,8);
T->add(27,27);
T->add(40,40);
T->add(50,50);
T->add(45,45);
*/
  T->print (); // could help with debugging
  string blah, blah2;
//cin>>blah;
  // Test to make sure the iterator prints the items in correct order
  for( RedBlackTree<int, int>::iterator it = T->begin(); it != T->end(); ++it)
     {
		
		//std::cout<<"looping through for loop"<<std::endl;
        std::cout << "(" << it->first << "," << it->second << ") " ;
     
		//std::cout << "marker" << std::endl;
		//cin>>blah2;
	 }
 // std::cout << "MARKER" << std::endl;
//cin>>blah2;
  // Make sure that lookup works correctly by looking for all items.
  std::cout<<endl;
  for (int i = 99; i >= 0; i --) 
 //for (int i=10; i>0; i--)
      std::cout << T->lookup (i) << "\n";

	  
		//std::cout << "FLAG" << std::endl;
  delete T;
  return 0;
}
