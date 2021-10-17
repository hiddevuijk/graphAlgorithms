
#include "graphBag.h"
#include "topologicalSort.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{

	GraphBag graph(7,true);
	graph.add(0,1);
	graph.add(0,2);
	graph.add(0,5);
	graph.add(1,4);
	graph.add(3,2);
	graph.add(3,4);
	graph.add(3,5);
	graph.add(5,2);
	graph.add(6,4);
	graph.add(6,0);

	TopSort ts(graph);
	stack<int> order = ts.getOrder();
	while( !order.empty() ) {
		cout << order.top() << endl;
		order.pop();
	}


	vector<vector<int> > edges = graph.getEdges();
	for(vector<vector<int> >::size_type i = 0; i < edges.size(); ++i) {
		//cout << edges[i][0] << "\t" << edges[i][1] << endl;
	}
	return 0;
}
