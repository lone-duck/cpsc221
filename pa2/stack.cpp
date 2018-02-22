#ifdef _STACK_H_

// default constructor
template <typename T>
Stack<T>::Stack(){
}

// copy constructor
template <typename T>
Stack<T>::Stack(const Stack& st){
	ac = ArrayClass<T>(st.ac);
}

// assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& st){
	if(this == &st){ return *this; }
	ArrayClass<T> newAC(st.ac);
	ac = newAC;
	return *this;
}

///////////////
// accessors //
///////////////

// Return true if the stack contains no items
template <typename T>
bool Stack<T>::isEmpty() const{
	return ac.empty();
}

// Returns the number of items stored in the stack
template <typename T>
unsigned int Stack<T>::size() const{
	return ac.size();
}

// Return a reference to the top item of the stack
// Throws an out_of_range exception if the stack is empty
template <typename T>
T& Stack<T>::peek(){
	if(isEmpty()){
		throw std::out_of_range("Stack<T>::peek() : peek called on empty stack");
	}
	return ac[size() - 1];
}

//////////////
// mutators //
//////////////

// Pushes an item to the top of the stack
template <typename T>
void Stack<T>::push(const T item){
	ac.pushBack(item);
}

// Removes and returns (a copy of) the top item of the stack
// Throws an out_of_range exception if the stack is empty
template <typename T>
T Stack<T>::pop(){
	if(isEmpty()){
		throw std::out_of_range("Stack<T>::pop() : pop called on empty stack");
	}
	T retval = T(ac[size() - 1]);
	ac.popBack();
	return retval;
}

#endif