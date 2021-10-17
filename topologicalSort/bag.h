#ifndef GUARD_BAG_H
#define GUARD_BAG_H

template<class T>
class Bag {
  public:

	Bag();
	Bag( const Bag &rhs_bag);
	~Bag() { clear(); delete tail; }


	Bag& operator=( const Bag &rhs_bag);

	class Iter;

	bool isEmpty() const { return head == tail; }

	void push_back(const T& v);
	void add(const T& v){ push_back(v); }
	void push_front(const T& v);

	Iter start() const { Iter iter(head,tail); return iter; }
	Iter end() const { Iter iter(tail,tail); return iter; }

	Iter find(const T& val) const {
		Iter iter = start();
		while( iter != end() && *iter != val ) ++iter;
		return iter;
	}

	
	bool contains( const T& val) const
	{ return end() != find(val); }

	void remove( Iter iter);
	void removeValue(const T&);
	void clear();

  private:
	class Link;

	Link* head;
	Link* tail;

	void remove(Link* l);
};


template<class T>
class Bag<T>::Link {
  public:
	Link(): next(nullptr), prev(nullptr) {};
	Link(const T& v) : next(nullptr), prev(nullptr), value(v) {}

	Link* next;
	Link* prev;

	T value;

};

template<class T>
class Bag<T>::Iter {
	friend Bag;
  public:
	Iter(): l(nullptr) {}
	Iter(Bag<T>::Link* link, Bag<T>::Link* tail_of_bag)
	: l(link), tail_of_bag(tail_of_bag)  {}	

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

	bool operator==(  const Iter& rhs)
	{ return l == rhs.l; }

	bool operator!=(  const Iter& rhs)
	{ return l != rhs.l; }

	bool hasnext() const { return l->next != nullptr; }
	bool hasprev() const { return l->prev != nullptr; }
	bool isvalid() const { return (l != nullptr && l != tail_of_bag); }
	bool istail()  const { return l == tail_of_bag; }
  private:
	Link* l;
	Link* tail_of_bag;
};



template<class T>
Bag<T>::Bag()
: head(new Link), tail(head) {}


template<class T>
Bag<T>::Bag( const Bag<T> &rhs_bag)
: head(new Link), tail(head)
{

	Bag<T>::Iter rhs_iter = rhs_bag.start();
	while( rhs_iter != rhs_bag.end() ) {
		push_back( *rhs_iter );
		++rhs_iter;
	}
}

template<class T>
Bag<T>& Bag<T>::operator=(const Bag<T> & rhs_bag)
{
	this->clear();

	Bag<T>::Iter rhs_iter = rhs_bag.start();
	while( rhs_iter != rhs_bag.end() ) {
		push_back( *rhs_iter );
		++rhs_iter;
	}
	return *this;
}

template<class T>
void Bag<T>::clear()
{
	Link* sent;
	while( head != tail ){
		sent = head;	
		head = head->next;
		delete sent;
	}
}

template<class T>
void Bag<T>::push_back(const T& v)
{
	Link* newlink = new Link(v);
	if( head == tail ) {

		head = newlink;
		head->next = tail;
		head->prev = nullptr;
		tail->prev = head;

	} else {
		newlink->next = tail;
		newlink->prev = tail->prev;
		tail->prev->next = newlink;
		tail->prev = newlink;
	}	
}

template<class T>
void Bag<T>::push_front( const T& v)
{

	Link* newlink = new Link(v);
	if( head == tail ) {
		head = newlink;
		head->next = tail;
		head->prev = nullptr;
		tail->prev = head;
	} else {
		newlink->prev = nullptr;
		newlink->next = head;
		head->prev = newlink;
		head = newlink;	
	}
}

template<class T>
void Bag<T>::remove(Iter iter)
{ remove( iter.l ); }

template<class T>
void Bag<T>::removeValue(const T& v)
{
	Bag<T>::Iter iter = find(v);
	while( iter != end() ) {
		Link* l = iter.l;
		++iter;
		remove(l);
		iter = find(v);
	}
}

template<class T>
void Bag<T>::remove(Link* l)
{

	if( l == tail) return;
	if(l == head ) {
		head = head->next;
		head->prev = nullptr;
	} else {
		l->prev->next = l->next;
		l->next->prev = l->prev;
	}
	delete l;
}

#endif
