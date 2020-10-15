#include <stdio.h>
#include <stdlib.h>
#include "../Libraries/ListAdjacency.h"
#include "../Libraries/List.h"

typedef struct edge
{
  int outVertex, inVertex;
} Edge;

typedef struct setEdge
{
  Edge* edge;
  int length;
} setEdge;

void bfsGeneric(Graph* G)
{
  int i, j, v, w;
  Head *notExplored =  ( Head* )malloc( 1*sizeof( Head ));
  Head *achieve =  ( Head* )malloc( 1*sizeof( Head ));
  Head *explored =  ( Head* )malloc( 1*sizeof( Head ));

  notExplored->begin = NULL;
  explored->begin = NULL;
  achieve->begin = NULL;


  for( i = 0; i < G->V; i++ )
    insertList(notExplored, i);

  int r = notExplored->begin->no;

  insertList( achieve, r );
  removeList(notExplored, r);

  while ( achieve->begin != NULL )
  {
    v = achieve->begin->no;
    if( G->adj[v].next != NULL )
    {  
      w = G->adj[v].next->node;
      removeEdge( G, v, w );

      if( !searchList( achieve, w ))
      {
        insertList( achieve, w );
        removeList(notExplored, w);
      }
    }
    else
    {
      insertList( explored, v );
      removeList( achieve, v );
    }
  }
}

setEdge spanningTree(Graph* G)
{
  int i, v, w;
  Head *notExplored = ( Head* )malloc( 1*sizeof( Head ));
  Head *achieve = ( Head* )malloc( 1*sizeof( Head ));
  Head *explored =  ( Head* )malloc( 1*sizeof( Head ));

  
  notExplored->begin = NULL;
  explored->begin = NULL;
  achieve->begin = NULL;

  setEdge setEdge;
  setEdge.edge = (Edge*)malloc( 1*sizeof( Edge ));
  setEdge.length = 0;

  for( i = 0; i < G->V; i++ )
    insertList(notExplored, i);

  int r = notExplored->begin->no;

  insertList( achieve, r );
  removeList(notExplored, r);

  while ( achieve->begin != NULL )
  {
    v = achieve->begin->no;
    if( G->adj[v].next != NULL )
    {  
      w = G->adj[v].next->node;
      removeEdge( G, v, w );

      if( !searchList( achieve, w ))
      {
        insertList( achieve, w );
        removeList(notExplored, w);
        setEdge.edge = ( Edge* )realloc( setEdge.edge, (setEdge.length+1)*sizeof( Edge ));
        setEdge.edge[setEdge.length].outVertex = v;
        setEdge.edge[setEdge.length].inVertex = w;
        setEdge.length++;
      }
    }
    else
    {
      insertList( explored, v );
      removeList( achieve, v );
    }
  }

  return setEdge;
}

setEdge bfs(Graph* G)
{
  int i, v, w;
  Head *notExplored = ( Head* )malloc( 1*sizeof( Head ));
  Head *achieve = ( Head* )malloc( 1*sizeof( Head ));
  Head *explored =  ( Head* )malloc( 1*sizeof( Head ));

  
  notExplored->begin = NULL;
  explored->begin = NULL;
  achieve->begin = NULL;
  setEdge setEdge;
  setEdge.length = 1;

  for( i = 0; i < G->V; i++ )
    insertList(notExplored, i);

  int r = notExplored->begin->no;

  insertList( achieve, r );
  removeList(notExplored, r);

  while ( achieve->begin != NULL )
  {
    v = achieve->begin->no;
    if( G->adj[v].next != NULL )
    {  
      w = G->adj[v].next->node;
      removeEdge( G, v, w );

      if( !searchList( achieve, w ))
      {
        insertList( achieve, w );
        removeList(notExplored, w);
        setEdge.edge = ( Edge* )realloc( setEdge.edge, (setEdge.length)*sizeof( Edge ));
        setEdge.edge[setEdge.length].outVertex = v;
        setEdge.edge[setEdge.length].inVertex = w;
        setEdge.length++;
      }
    }
    else
    {
      insertList( explored, v );
      removeList( achieve, v );
    }
  }

  return setEdge;
}

int main()
{
  int nVertices, vertice, nEdges, Edge, result, i, rem;

  scanf("%d%d", &nVertices, &nEdges );

  Graph* G = createGraph( nVertices);
  Graph* H = createGraph( nVertices);

  // insertEdge( G, 0, 1); 
  // insertEdge( G, 0, 2); 
  // insertEdge( G, 0, 3); 
  // insertEdge( G, 1, 2); 
  // insertEdge( G, 2, 3); 
  // insertEdge( H, 0, 1); 
  // insertEdge( H, 0, 2); 
  // insertEdge( H, 0, 3); 
  // insertEdge( H, 1, 2); 
  // insertEdge( H, 2, 3); 
  
  for ( i = 0; i < nEdges; i++ )
  {
    scanf("%d%d", &vertice, &Edge );
    insertEdge( G, vertice, Edge );
    insertEdge( H, vertice, Edge );
  }

  showGraph( G );
  showGraph( H );
  bfsGeneric(G);

  setEdge e = spanningTree(H);

  for( i = 0; i < e.length; i++)
  {
    printf("%d %d", e.edge[i].outVertex, e.edge[i].inVertex );
    printf("\n");
  }
 

  return 0;
}
