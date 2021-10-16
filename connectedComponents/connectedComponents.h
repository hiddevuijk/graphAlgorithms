#ifndef GUARD_CONNECTEDCOMPONETS_H
#define GUARD_CONNECTEDCOMPONETS_H

#include "graphBag.h"


class CC {
  public:
	CC(const GraphBag& graph);

	std::vector<int> getComponentIndices() const
		{ return component_index;}

	unsigned int getComponentIndex(unsigned int vi) const
		{ return component_index[vi]; }

	unsigned int getNumberOfComponents() const 
		{ return numberOfComponents; }


  private:
	std::vector<bool> marked;
	std::vector<int>  component_index;
	unsigned int numberOfComponents;

	void dfs(const GraphBag &graph, int vi, int ci);

};


CC::CC(const GraphBag& graph)
: marked(graph.V(), false), component_index(graph.V(), -1)
{
	int NV = graph.V();
	
	int ci = 0;

	// source of the connected component
	int source = 0;


	while( source < NV ) {
		dfs(graph,source, ci);

		++ci;
		//find next source
		while( marked[source] == true ) ++source;
	}
	
	numberOfComponents = ci;
}


void CC::dfs(const GraphBag& graph, int vi, int ci)
{

	marked[vi] = true;
	component_index[vi] = ci;
	for( GraphBag::EdgeIter iter = graph.getEdgeIter(vi);
					iter.isvalid(); ++iter ) {

		if( !marked[*iter] ) {
			dfs(graph, *iter, ci);
		}
	}
			
}




#endif
