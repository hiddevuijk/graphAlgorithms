#ifndef GUARD_TOPOLOGICALSORT_H
#define GUARD_TOPOLOGICALSORT_H

#include "graphBag.h"

#include <vector>
#include <stack>

class TopSort {
  public:
	TopSort(const GraphBag &graph);
	
	std::stack<int> getOrder() const { return postOrder; }

  private:
	std::vector<bool> marked;
	std::stack<int> postOrder;

	void dfs(const GraphBag &graph, int vi);
	

};

TopSort::TopSort(const GraphBag &graph)
: marked(graph.V(), false)
{
	for(int source = 0; source < graph.V(); ++source ) {
		if( !marked[source] ) dfs(graph,source);
	}
}

void TopSort::dfs(const GraphBag &graph, int vi)
{
	marked[vi] = true;
	for( GraphBag::EdgeIter iter = graph.getEdgeIter(vi);
			iter.isvalid(); ++iter ) {

		if( !marked[*iter] ) dfs(graph, *iter);
	}
	postOrder.push(vi);
}

#endif
