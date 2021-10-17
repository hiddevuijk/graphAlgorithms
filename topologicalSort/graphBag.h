#ifndef GUARD_GRAPHBAG_H
#define GUARD_GRAPHBAG_H


/*
	Guard against double edges, self loop?? 
*/

#include "bag.h"

#include <vector>


class GraphBag {
  public:
	GraphBag(int nv, bool directed=false)
		: vertices(nv), directed(directed) {}

	int V() const { return vertices.size(); }
	void add(int i, int j);
	void remove(int i, int j);

	bool hasEdge(int i, int j) const
		{ return vertices[i].contains(j); }

	// EdgeIter is and iterator over edges
	// use prefix ++ to move foreward
	// as long as .isvalid() = true
	typedef Bag<int>::Iter EdgeIter;
	EdgeIter getEdgeIter(int i)const {return vertices[i].start(); }

	// returns a ( Nvertices x 2 ) vector with the edges
	std::vector<std::vector<int> > getEdges() const;
	

  private:
	std::vector<Bag<int> > vertices;
	bool directed;

};


void GraphBag::add(int i, int j)
{
	vertices[i].add(j);
	if( !directed ) vertices[j].add(i);
}

void GraphBag::remove(int i, int j)
{
	vertices[i].removeValue(j);
	if( !directed ) vertices[j].removeValue(i);
}


std::vector<std::vector<int> > GraphBag::getEdges() const
{
	std::vector<std::vector<int> > edges;
	std::vector<int> edge(2);

	for( std::vector<Bag<int> >::size_type vi=0;
			vi < vertices.size(); ++vi ) {
		for( EdgeIter iter = getEdgeIter(vi); iter.isvalid(); ++iter){
	
			edge[0] = vi;
			edge[1] = *iter;

			if( directed || edge[0] < edge[1] ) {
				edges.push_back( edge );
			}
		}
	}
	return edges;
}
#endif
