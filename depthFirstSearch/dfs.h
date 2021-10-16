#ifndef GUARD_DFS_H
#define GUARD_DFS_H

#include "graphBag.h"

class DFS {
  public:
	DFS(const GraphBag &graph, int source)
	: source(source), marked(graph.V(), false), edgeTo(graph.V() )
	{ dfs(graph,source); }

	bool hasPathTo(int v) const { return marked[v];}

  private:
	int source;

	std::vector<bool> marked;
	std::vector<int> edgeTo;

	void dfs(const GraphBag &graph, int vi);
};

void DFS::dfs(const GraphBag &graph, int vi)
{
	marked[vi] = true;
	for( GraphBag::EdgeIter iter = graph.getEdgeIter(vi); 
		iter.isvalid(); ++iter)
	{
		if( !marked[*iter] ) {
			dfs(graph,*iter);
			edgeTo[*iter] = vi;
		}

	}
}

#endif
