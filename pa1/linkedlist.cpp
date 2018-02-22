//Implementation of LinkedList class
#include "linkedlist.h"
#include <iostream>


// helper function for deep copy
// Used by copy constructor and operator=
// should create new Kebab objects
void LinkedList::copyList(const LinkedList& ll){
	deleteList();
	if(ll.isEmpty()){return;}
	for(Node* current = ll.front; current != NULL; current = current->next){
		Kebab* newKebab = new Kebab;
		newKebab->buildKebab(current->data->listIngredients());
		insertBack(newKebab);
	}
}

// helper function for deep delete
// Used by destructor and copy/assignment
// Deallocates Nodes and the Kebabs inside
void LinkedList::deleteList(){
	
	while(front != NULL){
		Node* toDelete = front;
		front = toDelete->next;
		delete toDelete;
	}
	back = NULL;
	length = 0;
}

// default constructor
LinkedList::LinkedList(){
	length = 0;
	front = NULL;
	back = NULL;
}

// copy constructor, performs deep copy of list elements
LinkedList::LinkedList(const LinkedList& ll){
	length = 0;
	front = NULL;
	back = NULL;
	copyList(ll);
}

// destructor
LinkedList::~LinkedList(){
	deleteList();
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
void LinkedList::insertFront(Kebab* item){
	if (isEmpty()) {
		front = new Node(item);
		back = front;
		length++;
	} else {
		Node* newNode = new Node(item);
		newNode->next = front;
		front = newNode;
		length++;
	}
	return;
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
void LinkedList::insertBack(Kebab* item){
	if(isEmpty()){
		insertFront(item);
	} else {
		Node* newNode = new Node(item);
		back->next = newNode;
		back = newNode;
		length++;
	}
	return;
}

// Inserts an item in position p (0-indexed)
// Returns false for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
bool LinkedList::insertAt(Kebab* item, unsigned int p){
	//special cases
	if(p > size()){return false;}
	//if p = 0, equiv. to insertFront
	if(isEmpty() || p == 0){
		insertFront(item);
		return true;
	}
	//if p = size(), equiv. to insertBack
	if(p == size()){
		insertBack(item);
		return true;
	}

	Node* newNode = new Node(item);
	Node* current = front;

	//find Node p - 1
	for(size_t currentP = 0; currentP != p - 1; currentP++){
		current = current->next;
	}

	//insert Node
	newNode->next = current->next;
	current->next = newNode;
	length++;
	return true;
}

// Removes and returns an item from position p (0-indexed)
// Return NULL if index is invalid
// PRE:   0 <= p < size
// POST:  Item is removed from list.
//        Node is deallocated but Kebab should in memory
//        Thus set data to NULL before deleting
// PARAM: p = position from where item will be removed
Kebab* LinkedList::removeAt(unsigned int p){
	//deal with special cases...
	if (p >= size() || isEmpty()){return NULL;}
	//if size = 1, return data from first node, empty-tize list
	if(size() == 1){
		Kebab* retval = front->data;
		front->data = NULL;
		delete front;
		front = NULL;
		back = NULL;
		length--;
		return retval;
	}

	Node* current = front;
	Kebab* retval;
	//if removing from first node, return first node's data
	//make front point to appropriate node
	if(p == 0){
		retval = front->data;
		front->data = NULL;
		front = front->next;
		delete current;
		length--;
		return retval;
	}
	//if removing from p > 0, find node before p
	for(size_t currentP = 0; currentP != p - 1; currentP++){
		current = current->next;
	}
	//return appropriate value, link node p-1 to node p+1, delete node p 
	retval = current->next->data;
	current->next->data = NULL;
	Node* toDelete = current->next;
	current->next = toDelete->next;
	if(toDelete == back){back = current;}
	delete toDelete;
	length--;
	return retval;
}

// ACCESSORS

// Returns size of list
unsigned int LinkedList::size() const{
	return length;
}

// Returns whether the list is empty
bool LinkedList::isEmpty() const{
	return (size() == 0) ? true : false;
}

// Returns existence of a Kebab that has at least
//   all the same ingredients as k, in any order
//   i.e. the list has a Kebab whose ingredients
//   are a super-multiset of k's ingredients
bool LinkedList::contains(Kebab& k) const{
	//handle special cases
	if(isEmpty()){return false;}
	if(front->data->hasSameIngredients(k)){return true;}
	if(front->next == NULL){return false;}
	
	//handle general case
	Node* current = front;

	//move to next node, check
	do{
		current = current->next;
		if(current->data->hasSameIngredients(k)){return true;}
	}while(current != back);
	
	//if not found return false
	return false;
}

// Returns item at index (0-indexed)
// Returns NULL if index is invalid
Kebab* LinkedList::elementAt(unsigned int p) const{
	if (p >= size()){return NULL;}
	Node* current = front;
	size_t currentP = 0;
	while(currentP != p){
		current = current->next;
		currentP++;
	}
	return current->data;
}

// OVERLOADED OPERATORS

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
LinkedList& LinkedList::operator=(const LinkedList& ll){
	if(this == &ll){return *this;}
	copyList(ll);
	return *this;
}






