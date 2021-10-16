#ifndef GUARD_LINKED_LIST_H
#define GUARD_LINKED_LIST_H


template<class T>
class LinkedList {
  public:
	LinkedList() : head(nullptr), tail(nullptr) {}
	LinkedList( const LinkedList &rhs_list);
	~LinkedList();

	LinkedList& operator=( const LinkedList &rhs_list);

	bool isEmpty() const { return head == nullptr; }

	void push( T v);
	T& peeki;

	class Iter;

	void insert( Iter iter, T v);
	void insert_after( Iter iter, T v);
	
	Iter start() const { Iter iter(head); return iter; }
	Iter end() const { Iter iter(tail); return iter; }

	Iter find(T val) const {
		Iter iter = this->start();
		while( iter.isvalid() && *iter != val ) ++iter;
		return iter;
	}

	void remove(Iter iter);
	void removeValue( const T&);
	void clear();

  private:
	class Link;

	Link* head;
	Link* tail;

	void insert(Link* l, T v);
	void insert_after(Link* l, T v);
	void remove(Link* l);
};


template<class T>
class LinkedList<T>::Link {
  public:
	Link(T v) : next(nullptr), prev(nullptr), value(v) {}

	Link* next;
	Link* prev;

	T value;

};


template<class T>
class LinkedList<T>::Iter {
	friend LinkedList;
  public:
	Iter(LinkedList<T>::Link* link): l(link) {}	

	Iter operator++() {
		l = l->next;
		return *this;
	}
	Iter operator--() {
		l = l->prev;
		return *this;
	}

	T& operator*() {
		return l->value;
	}

	bool hasnext() const { return l->next != nullptr; }
	bool hasprev() const { return l->prev != nullptr; }
	bool isvalid() const { return l != nullptr; }
  private:
	Link* l;
};

template<class T>
LinkedList<T>::LinkedList( const LinkedList<T> &rhs_list)
: head(nullptr), tail(nullptr)
{
	LinkedList<T>::Iter rhs_iter = rhs_list.start();	
	while( rhs_iter.isvalid() ) {
		this->push_back(*rhs_iter);
		++rhs_iter;
	}

}

template<class T>
LinkedList<T>& LinkedList<T>::operator=( const LinkedList<T> &rhs_list)
{
	this->clear();	
	LinkedList<T>::Iter iter = rhs_list.start();		
	while( iter.isvalid() ) {
		push_back( *iter );
		++iter;
	}
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	Link* sent = head;
	while( head != nullptr ) {
		sent = head;
		head = head->next;
		delete sent;
	}	
}

template<class T>
bool LinkedList<T>::contains(const T& val) const
{
	Iter iter = start();
	while( iter.isvalid() ) {
		if( *iter == val ) return true;
		++iter;
	}

	return false;
}

template<class T>
void LinkedList<T>::push_back(T v)
{
	Link* newlink = new Link(v);
	if( tail != nullptr ) {
		tail->next = newlink;	
		newlink->prev = tail;
		tail = newlink;
	} else {
		tail = newlink;
		head = newlink;
	}

}

template<class T>
void LinkedList<T>::push_front(T v)
{
	Link* newlink = new Link(v);
	if( head != nullptr ){
		head->prev = newlink;
		newlink->next = head;
		head = newlink;
	} else {
		tail = newlink;
		head = newlink;
	}

}


template<class T>
void LinkedList<T>::insert( Iter iter, T v)
{ insert(iter.l, v); }

template<class T>
void LinkedList<T>::insert_after( Iter iter, T v)
{ insert_after(iter.l, v); }


template<class T>
void LinkedList<T>::insert( Link* l, T v)
{
	Link* newlink = new Link(v);
	if( head == nullptr ) {
		head = newlink;
		tail = newlink;
	} else if(  l == head ) {
		l->prev = newlink;
		newlink->next = head;
		head = newlink;
	} else {
		newlink->prev = l->prev;	
		newlink->next = l;
		newlink->prev->next = newlink;
		l->prev = newlink;
	}
}
template<class T>
void LinkedList<T>::insert_after( Link* l, T v)
{
	Link* newlink = new Link(v);
	if( l == tail ) {
		newlink->prev = tail;
		tail->next = newlink;
		tail = newlink;
	} else {
		newlink->next = l->next;
		newlink->prev = l;
		l->next->prev = newlink;
		l->next = newlink;
	}
}

template<class T>
void LinkedList<T>::remove(Iter iter)
{ remove(iter.l); }

template<class T>
void LinkedList<T>::removeValue(const T& v)
{

	LinkedList<T>::Iter iter = find(v);
	
	while( iter.isvalid() ) {
		LinkedList<T>::Iter temp = iter;
		++iter;
		remove(temp);
		while( iter.isvalid() && *iter != v) ++iter;
	}
	

}

template<class T>
void LinkedList<T>::remove(Link* l)
{
	if(l == nullptr) return;
	if( l == head && l == tail ) {
		head = nullptr;	
		tail = nullptr;
	} else if( l == head ) {
		head = l->next;
		head->prev = nullptr;
	} else if( l == tail ) {
		tail = l->prev;
		tail->next = nullptr;
	} else {
		l->prev->next = l->next;
		l->next->prev = l->prev;
	}	
	delete l;
}

template<class T>
void LinkedList<T>::clear()
{
	Link* sent = head;
	while( head != nullptr ) {
		sent = head;
		head = head->next;
		delete sent;
	}	

	head = nullptr;
	tail = nullptr;

}


#endif
