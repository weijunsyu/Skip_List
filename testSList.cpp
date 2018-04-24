#include "SList.h"

#include<iostream>


int main() {
	
	SList a;
	a.setOutputDelimeter(" ");
	//random set
	for (int i = 0; i < 100; i++) {
		int num = rand();
		a.insert(num);
	}
	std::cout << "RANDOM: n=100: Traversals: " << a.getTraversals() << "\n";
	a.reset();
	for (int i = 0; i < 1000; i++) {
		int num = rand();
		a.insert(num);
	}
	std::cout << "RANDOM: n=1000: Traversals: " << a.getTraversals() << "\n";
	a.reset();
	for (int i = 0; i < 10000; i++) {
		int num = rand();
		a.insert(num);
	}
	std::cout << "RANDOM: n=10000: Traversals: " << a.getTraversals() << "\n";
	a.reset();

	//sorted set
	for (int i = 0; i < 100; i++) {
		a.insert(i);
	}
	std::cout << "SORTED: n=100: Traversals: " << a.getTraversals() << "\n";
	a.reset();
	for (int i = 0; i < 1000; i++) {
		a.insert(i);
	}
	std::cout << "SORTED: n=1000: Traversals: " << a.getTraversals() << "\n";
	a.reset();
	for (int i = 0; i < 10000; i++) {
		a.insert(i);
	}
	std::cout << "SORTED: n=10000: Traversals: " << a.getTraversals() << "\n";
	a.reset();

	//searching in list of 100 elements from 0-99
	for (int i = 0; i < 100; i++) {
		a.insert(i);
	}
	std::cout << "the following searches performed on a list of 100 elements containing integers from 0-99\n";
	a.found(0);
	std::cout << "comparisons needed to find item at front: " << a.getComparisons() << "\n";
	a.found(50);
	std::cout << "comparisons needed to find item at middle: " << a.getComparisons() << "\n";
	a.found(99);
	std::cout << "comparisons needed to find last item: " << a.getComparisons() << "\n";
	a.found(-1);
	std::cout << "comparisons needed to find item not in list < first item: " << a.getComparisons() << "\n";
	a.found(100);
	std::cout << "comparisons needed to find item not in list > last item: " << a.getComparisons() << "\n";
	
	//searching in list of 100 elements from 0-999
	for (int i = 0; i < 1000; i++) {
		a.insert(i);
	}
	std::cout << "the following searches performed on a list of 1000 elements containing integers from 0-999\n";
	a.found(0);
	std::cout << "comparisons needed to find item at front: " << a.getComparisons() << "\n";
	a.found(500);
	std::cout << "comparisons needed to find item at middle: " << a.getComparisons() << "\n";
	a.found(999);
	std::cout << "comparisons needed to find last item: " << a.getComparisons() << "\n";
	a.found(-1);
	std::cout << "comparisons needed to find item not in list < first item: " << a.getComparisons() << "\n";
	a.found(1000);
	std::cout << "comparisons needed to find item not in list > last item: " << a.getComparisons() << "\n";
	
	int x;
	std::cout << "type anything then press enter to exit\n";
	std::cin >> x;

	return 0;
}