
#include "bfs.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{

	GraphBag graph(7);
	graph.add(0,1);
	graph.add(0,6);
	graph.add(1,2);
	graph.add(2,4);
	graph.add(2,6);
	graph.add(4,5);
	graph.add(4,6);

	BFS paths(graph, 0);

	cout << paths.distanceToSource(0) << endl;	

	vector<int> p = paths.pathTo(5);
	for( vector<int>::size_type i = 0;i<p.size(); ++i) {
		cout << p[i] << "\t";
	}
	cout << endl;

	return 0;
}
