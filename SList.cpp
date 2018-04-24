
#include "SList.h"

//#define NDEBUG

SList::SList() {
	//init to 2 dummy nodes as empty
	head = consL2(nullptr, consL1(0, nullptr));
	sizeL1 = 0;
	spacing = 2;
	numTraversals = 0;
	delimeter = "  \n";
}

void SList::insert(int x) {
	L2* currL2 = head; //start at L2 dummy node
	while (currL2->next != nullptr && x > (currL2->next->down)->item) {
		numTraversals++;
		currL2 = currL2->next;
	}
	L1* currL1 = currL2->down; //move down into L1
	while (currL1->next != nullptr && x > (currL1->next)->item) {
		numTraversals++;
		currL1 = currL1->next;
	}
	//currL1 should be now at the node prev to where I need to insert x
	L1* temp = currL1->next;
	currL1->next = consL1(x, temp);
	sizeL1++;
	//reconstruct L2
	reconstructL2();
}

int SList::getTraversals() const {
	return numTraversals;
}

bool SList::found(int x) {
	numComparisons = 0;

	L2* currL2 = head;
	while (currL2->next != nullptr && x >= (currL2->next->down)->item) {
		numComparisons++;
		if (currL2->next->down->item == x) { //exit on first occurence in case of duplicates
			return true;
		}
		currL2 = currL2->next;
	}
	L1* currL1 = currL2->down;
	while (currL1->next != nullptr && x >= (currL1->next)->item) {
		numComparisons++;
		if (currL1->next->item == x) { //exit on first occurence in case of duplicates
			return true;
		}
		currL1 = currL1->next;
	}
	return false;
}

int SList::getComparisons() const {
	return numComparisons;
}

void SList::printAllInOrder(std::ostream& out) const {
	if (sizeL1 == 0) { //list is empty
		out << "List is empty!\n";
		return;
	}
	L1* current = head->down->next; //skip over dummy node
	while (current->next != nullptr) {
		out << current->item << delimeter;
		current = current->next;
	}
	out << current->item << "\n"; //last item ends with \n not delimeter
}

void SList::setOutputDelimeter(std::string delimeter) {
	this->delimeter = delimeter;
}

int SList::numberOfElements() const {
	return sizeL1;
}

void SList::reset() {
	deleteALL();

	head = consL2(nullptr, consL1(0, nullptr));
	sizeL1 = 0;
	spacing = 2;
	numTraversals = 0;
	delimeter = "  \n";
}

SList& SList::operator = (const SList& rtSide) {
	if (this != &rtSide) {
		deleteALL();
		sizeL1 = rtSide.sizeL1;
		spacing = rtSide.spacing;
		numTraversals = rtSide.numTraversals;
		delimeter = rtSide.delimeter;
		head = consL2(nullptr, copyL1(rtSide.head->down));
		reconstructL2();
	}
	return *this;
}

SList::SList(const SList& rtSide) {
	sizeL1 = rtSide.sizeL1;
	spacing = rtSide.spacing;
	numTraversals = rtSide.numTraversals;
	delimeter = rtSide.delimeter;
	head = consL2(nullptr, copyL1(rtSide.head->down));
	reconstructL2();
}

SList::~SList() {
#ifndef NDEBUG
	std::cout << "destructor called\n";
#endif
	deleteALL();
}

void SList::dumpTopList(std::ostream& out) {
	if (head->next == nullptr) { //L2 is empty
		out << "[ ]\n";
		return;
	}
	L2* current = head->next; //skip over dummy node
	out << "[ ";
	while (current->next != nullptr) {
		out << current->down->item << " ";
		current = current->next;
	}
	out << current->down->item << " ]\n";
}

SList::L2* SList::consL2(L2* x, L1* y) {
	return new L2{ x, y };
}

SList::L1* SList::consL1(int item, L1* x) {
	return new L1{ item, x };
}

void SList::reconstructL2() {
	//if list has less than 2 elements no L2 list is needed
	if (sizeL1 < 2) { //not required to break out here but do so anyways
		return;
	}
	//(n*n) + n gives the closed form of the sequence:
	// 6,12,20,30,...,a_n such that a is the length of the list
	//    at which the spacing of L2 needs to be increased and n is the spacing.
	else if (sizeL1 == (spacing * spacing) + spacing) {
		spacing++;
	}
	//delete all L2 nodes
	deleteL2(head->next);
	//2 pointers one from L2 one from L1
	L2* l2 = head; //start at dummy node; index 0
	L1* l1 = (head->down)->next; //start at index 1 since sizeL1 > 1
	//travel down L1 and every numRestruct nodes add one L2 node
	int counter = 1;
	while (l1 != nullptr) {
		if (counter % (spacing) == 0) {
			l2->next = consL2(nullptr, l1);
			l2 = l2->next;
		}
		counter++;
		numTraversals++;
		l1 = l1->next;
	}
}

void SList::deleteL2(L2* &list) {

	L2* current = list;
	while (current != nullptr) {
		L2* next = current->next;
		delete current;
		current = next;
	}
	list = nullptr;
}

void SList::deleteL1(L1* &list) {

	L1* current = list;
	while (current != nullptr) {
		L1* next = current->next;
		delete current;
		current = next;
	}
	list = nullptr;
}

void SList::deleteALL() {
	//delete L1 list from the dummy node
	deleteL1(head->down);
	//delete L2 list
	deleteL2(head); //safe operation assuming L1 was deleted correctly
	head = nullptr;
}

SList::L1* SList::copyL1(L1* other) {
	if (other == nullptr) {
		return nullptr;
	}
	L1* copy = consL1(other->item, copyL1(other->next));
	return copy;
}
