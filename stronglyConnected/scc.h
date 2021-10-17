#ifndef GUARD_SCC_H
#define GUARD_SCC_H

#include "graphBag.h"
#include "topologicalSort.h"

#include <stack>

class SCC {
  public:
	SCC(const GraphBag &graph);

	bool stronglyConnected(int i, int j) const
			{ return index[i] == index[j]; }

	std::vector<int> getIndex() const { return index; }

  private:
	std::vector<bool> marked;
	std::vector<int> index;

	int index_counter;

	std::stack<int> postOrder;
	void dfs(const GraphBag &graph, int vi);

};


SCC::SCC(const GraphBag &graph)
: marked(graph.V(), false), index(graph.V(), -1),
  index_counter(0)
{
	TopSort ts( graph.reverse() );
	std::stack<int> postOrder = ts.getOrder();
	

	while( !postOrder.empty() ) {
		int vi = postOrder.top();
		postOrder.pop();
		if( !marked[vi] ){
			dfs( graph, vi);
			++index_counter;
		}
	}

}

void SCC::dfs(const GraphBag &graph, int vi)
{
	marked[vi] = true;
	index[vi] = index_counter;


	for( GraphBag::EdgeIter iter = graph.getEdgeIter(vi);
				iter.isvalid(); ++iter) {
		if( !marked[*iter] ) dfs(graph, *iter);
	}	

}


#endif
