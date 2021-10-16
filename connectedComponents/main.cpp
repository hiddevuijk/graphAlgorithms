
#include "graphBag.h"
#include "connectedComponents.h"

#include <iostream>
#include <vector>


using namespace std;

int main()
{

	GraphBag graph(10);

	graph.add(0,2);
	graph.add(0,6);
	graph.add(2,6);
	graph.add(6,7);

	graph.add(1,8);
	graph.add(1,5);
	graph.add(5,8);

	graph.add(4,9);


	CC cc(graph);


	vector<int> cindices = cc.getComponentIndices();

	for( vector<int>::size_type i =0; i<cindices.size(); ++i) {
		cout << i << "\t" << cindices[i] << endl;
	}


	cout << endl;
	cout << cc.getNumberOfComponents() << endl;
	return 0;
}

