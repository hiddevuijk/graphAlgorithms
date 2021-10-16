#ifndef GUARD_QUEUE_H
#define GUARD_QUEUE_H

template<class T>
class Queue {
  public:
	Queue();
	Queue( const Queue &rhs_stack);
	~Queue();

	Queue& operator=( const Queue &rhs_bag);

	void push(const T& v);
	T pop();
	T& peek() { return *head; } // throw error stack is empty
	bool isEmpty() const { return head == tail; }

	void clear();

  private:
	class Link;

	Link* head;
	Link* tail;

	void removeHead();
};


	
template<class T>
class Queue<T>::Link {
  public:
	Link(): next(nullptr), prev(nullptr) {};
	Link(const T& v) : next(nullptr), prev(nullptr), value(v) {}

	Link* next;
	Link* prev;

	T value;

};

template<class T>
Queue<T>::Queue()
: head(new Link), tail(head) {}

template<class T>
Queue<T>::Queue( const Queue<T> &rhs)
: head( new Link), tail(head)
{

	Link* sent = rhs.head;
	while( sent != rhs.tail ) {
		push( sent->value );
		sent = sent->next;
	}

}

template<class T>
Queue<T>::~Queue()
{
	Link* temp;	
	while( head!=tail ) {
		temp = head;
		head = head->next;
		delete temp;
	}
	delete tail;
	//head = nullptr;
	//tail = nullptr;
}

template<class T>
Queue<T>& Queue<T>::operator=( const Queue<T> &rhs)
{
	clear();

	Link* sent = rhs.head;
	while( sent != rhs.tail ) {
		push( sent->value );
		sent = sent->next;
	}

	return *this;

}


template<class T>
void Queue<T>::push( const T& v)
{

	Link* newlink = new Link(v);

	if( head == tail ) {
		head = newlink;
		head->next = tail;
		head->prev = nullptr;
		tail->prev = head;
	} else {
		newlink->prev = tail->prev;
		newlink->next = tail;
		tail->prev = newlink;
		newlink->prev->next = newlink;
	}
}

template<class T>
T Queue<T>::pop()
{
	// throw error when stack is empty

	T temp = head->value;
	removeHead();
	return temp;
}

template<class T>
void Queue<T>::removeHead()
{
	if(head == tail) return;
	Link* temp = head;
	head = head->next;
	delete temp;
}

template<class T>
void Queue<T>::clear()
{
	Link* temp;
	while( head != tail ) {
		temp = head;
		head = head->next;
		delete temp;
	}
}


#endif
