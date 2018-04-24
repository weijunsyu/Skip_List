#ifndef SLIST_H
#define SLIST_H


#include <string>
#include <fstream>
#include <iostream>

/*
* Two level Skip List that keeps the values in ascending order.
*/
class SList {
   public:
      SList();
      // insert an element in ascending order
      // postcondition: the number of traversals done in this call to
      // insert is added to the number of traversals so far
      // Note: to get the number of traversals, including the
      // traversals needed when adjusting the pointers of the top list,
      // call getTraversals()
      void insert(int x);

      // returns the TOTAL number of traversals done in order to build
      // the skip list so far
      //
      // the skip list is sorted in ascending order and the number of
      // traversals continues increasing -- it is never reset
      //
      // the total number of traversals depends on the number of calls
      // to the function insert and on how the top list is build and
      // the pointers adjusted
      int getTraversals() const;

      // return true if x is found in the list, false otherwise
      // postcondition: the number of comparisons done in this call to
      // found is updated
      // Note: if the number of comparisons made in found is needed,
      // call getComparisons() after found is called
      bool found(int x);

      // returns the number of comparisons done when found is called
      //
      // every time that found is called, the number of comparisons is
      // first reset to zero and the number comparisons is calculated
      int getComparisons() const;

      // output all the elements of the list in order (i.e. in ascending order)
      // separate the elements with the defined delimeter
      // which currently has an intial value of "  \n" (may be changed)
      void printAllInOrder(std::ostream&) const;

      // delimeter is used to separate the elements in printAllInOrder
      void setOutputDelimeter(std::string delimeter);

      // return the number of elements in the skip list
      int numberOfElements() const;

      // delete/deallocate the skip list and reset to the initial values
      // of the instance variables
      void reset();

      // overloaded assignment operator
      SList& operator = (const SList&);

      // copy constructor
      SList(const SList&);

      // destructor
      ~SList();

      // for debugging purpose, print the top list exclusively
      // not part of a 'real skip list' but we want to debug our assignment
      void dumpTopList(std::ostream& out);

   private:
	   struct L1 { //L1 node; bottem list
		   int item;
		   L1* next;
	   };
	   struct L2 { //L2 node; top list
		   L2* next;
		   L1* down;
	   };

	   L2* head;

	   int sizeL1; //length of L1

	   //The number of L1 nodes between each L2 node (including the L2 node)
	   //starting from 2; the spacing when sizeL1>1 (when L2 exists)
	   int spacing;

	   int numTraversals;
	   int numComparisons;

	   std::string delimeter;

	   //reconstsruct L2
	   void reconstructL2();

	   //delete the entire list
	   void deleteALL();

	   //construct a new L2 Node
	   static L2* consL2(L2* x, L1* y);

	   //construct a new L1 Node
	   static L1* consL1(int item, L1* x);

	   //delete all of L2 list
	   //precondition: pointer passed is to a list of L2 nodes
	   //              such that list does NOT start from a dummy node
	   //NOTE: if given from head (dummy node) will cause
	   //      memory leak given L1 will not be accessible after
	   //      deletion.
	   static void deleteL2(L2* &list);

	   //delete all of L1 list
	   static void deleteL1(L1* &list);

	   //return a deep copy of L1 list other
	   static L1* copyL1(L1* other);
};
#endif  // SLIST_H
