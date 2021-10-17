
#include "graphBag.h"
#include "scc.h"

#include <iostream>

using namespace std;

int main()
{

	GraphBag graph(13, true);

	graph.add(0,1);
	graph.add(0,5);

	graph.add(2,0);
	graph.add(2,3);

	graph.add(3,2);
	graph.add(3,5);

	graph.add(4,2);
	graph.add(4,3);

	graph.add(5,4);

	graph.add(6,0);
	graph.add(6,4);
	graph.add(6,8);
	graph.add(6,9);

	graph.add(7,6);
	graph.add(7,9);

	graph.add(8,6);

	graph.add(9,10);	
	graph.add(9,11);

	graph.add(10,12);

	graph.add(11,4);
	graph.add(11,12);

	graph.add(12,9);


	SCC scc(graph);	
	vector<int> index = scc.getIndex();
	for(vector<int>::size_type i = 0; i< index.size(); ++i) {
		cout << index[i] << endl;
	}
	

	return 0;
}

