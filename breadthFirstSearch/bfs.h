#ifndef GUARD_BFS_H
#define GUARD_BFS_H

#include "graphBag.h"
#include "queue.h"

#include <vector>

class BFS {
  public:
	BFS( const GraphBag &graph, int source);

	bool hasPathTo(int v) const { return marked[v]; }
	int distanceToSource(int v) const { return distTo[v]; }
	std::vector<int> pathTo(int v) const;
	

  private:
	int source;
	std::vector<bool>  marked;	
	std::vector<int> edgeTo;
	std::vector<int> distTo;

	void bfs(const GraphBag &graph);

};


BFS::BFS(const GraphBag &graph, int source)
:source(source), marked(graph.V(), false),
 edgeTo(graph.V(),-1), distTo(graph.V(), -1)
{ bfs(graph); }


void BFS::bfs( const GraphBag &graph)
{

	Queue<int> queue;
	queue.push(source);

	marked[source] = true;
	distTo[source] = 0;
	edgeTo[source] = source;
	
	while( !queue.isEmpty() ) {
		int vj = queue.pop(); 
		for( GraphBag::EdgeIter iter = graph.getEdgeIter(vj);
									iter.isvalid(); ++iter ) {
			if( !marked[*iter] ) {
				queue.push(*iter);
				marked[*iter] = true;
				edgeTo[*iter] = vj;
				distTo[*iter] = distTo[vj] + 1;
			}
		}
	}
}



std::vector<int> BFS::pathTo(int v) const
{
	std::vector<int> path;
	if( !marked[v] ) return path;
	
	while( edgeTo[v] != source ) {
		path.push_back(edgeTo[v]);
		v = edgeTo[v];
	}
	path.push_back(source);

	return path;	
}

#endif
