#ifdef _QUEUE_H_

// default constructor
template <typename T>
Queue<T>::Queue() : front(0), _size(0){
}

// copy constructor
template <typename T>
Queue<T>::Queue(const Queue& qq){
	ac = ArrayClass<T>(qq.ac);
	front = qq.front;
	_size = qq._size;
}

// assignment operator
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& qq){
	if(this == &qq){ return *this; }
	ArrayClass<T> newAC(qq.ac);
	ac = newAC;
	front = qq.front;
	_size = qq._size;
	return *this;
}

///////////////
// accessors //
///////////////

// Return true if the queue contains no items
template <typename T>
bool Queue<T>::isEmpty() const{
	return _size == 0;
}

// Returns the number of items stored in the queue
template <typename T>
unsigned int Queue<T>::size() const{
	return _size;
}

// Return a reference to the front item of the queue
// Throws an out_of_range exception if the queue is empty
template <typename T>
T& Queue<T>::peek(){
	if(isEmpty()){
		throw std::out_of_range("Queue<T>::peek() : peek called on empty queue.");
	}
	return ac[front];
}

//////////////
// mutators //
//////////////

// Inserts an item to the back of the queue
template <typename T>
void Queue<T>::enqueue(const T item){
	ac.pushBack(item);
	_size++;
}

// Removes and returns (a copy of) the front item of the queue
// Throws an out_of_range exception if the queue is empty
template <typename T>
T Queue<T>::dequeue(){
	if(isEmpty()){
		throw std::out_of_range("Queue<T>::dequeue() : dequeue called on empty queue.");
	}
	T retval = ac[front];
	_size--;
	front++;
	if(_size <= ac.capacity()/4){
		ac.startFrom(front);
		front = 0;
		ac.resize(_size);
	}
	if(_size == 0){
		ac = ArrayClass<T>();
		front = 0;
	}
	return retval;
}
#endif