

#include "queue.h"

#include <iostream>

using namespace std;


int main()
{

	Queue<int> q;
	q.push(0);
	q.push(1);
	q.push(2);
	q.push(3);

	Queue<int> q2;
	q2= q;

	while( !q2.isEmpty() ) cout << q2.pop() << endl;	


	return 0;
}
