#include <stdio.h>
#include <stdlib.h>
#include "./LibraryDigraph/Digraph.h"


// Question 02.g)
int main()
{
  int nVertex, nEdgeG, nEdgeH, outVertex, inVertex, weight, i=0;

  scanf("%d%d", &nVertex, &nEdgeG);
  Graph* G = createGraph( nVertex );

  scanf("%d%d", &nVertex, &nEdgeH);
  Graph* H = createGraph( nVertex );

  while (scanf("%d%d%d", &outVertex, &inVertex, &weight) != EOF)
  {
      if( i < nEdgeG )
          insertEdge( G, outVertex, inVertex, weight );
      else
          insertEdge( H, outVertex, inVertex, weight );
      i++;
  }

  showGraph( G, 'G' );
  showGraph( H, 'H' );


  Edge* edgesG = graphEdges(G);
  Edge* edgesH = graphEdges(H);

  printf("G edges:\n");
  for ( i = 0; i < nEdgeG; i++ )
  {
    printf("%d ", edgesG[i].outVertex);
    printf("%d ", edgesG[i].inVertex);
    printf(" %d ", edgesG[i].weight);
    printf("\n");
  }

  printf("\nH edges:\n");
  for ( i = 0; i < nEdgeH; i++ )
  {
    printf("%d ", edgesH[i].outVertex);
    printf("%d ", edgesH[i].inVertex);
    printf(" %d ", edgesH[i].weight);
    printf("\n");
  }
  
  printf("\n");
  
  verifyDegreeSequence( G, H );
  printf("\n");

  return 0;
}
