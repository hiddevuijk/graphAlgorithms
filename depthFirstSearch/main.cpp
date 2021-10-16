

#include "graphBag.h"
#include "dfs.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{

	GraphBag g(5);



	vector<vector<int> > edges = g.getEdges();
	for(vector<vector<int> >::size_type i = 0; i < edges.size(); ++i) {
		cout << edges[i][0] << "\t" << edges[i][1] << endl;
	}
	cout << endl;

	DFS dfs(g, 1);
	for(int i=0;i <5; ++i) cout << dfs.hasPathTo(i) << endl;

	return 0;
}
