#include <stdio.h>
#include <stdlib.h>
#include "../Libraries/MatrixAdjacency.h"
// Question 01.g)
int main()
{
  int nVertex, nEdgeG, nEdgeH, firstVertex, secondVertex, i=0;

  scanf("%d%d", &nVertex, &nEdgeG);
  Graph* G = createGraph( nVertex );

  scanf("%d%d", &nVertex, &nEdgeH);
  Graph* H = createGraph( nVertex );

  while (scanf("%d%d", &firstVertex, &secondVertex) != EOF)
  {
      if( i < nEdgeG )
          insertEdge( G, firstVertex, secondVertex );
      else
          insertEdge( H, firstVertex, secondVertex );
      i++;
  }

  showGraph(G, 'G');
  showGraph(H, 'H');
  printf("\n");

  verifyDegreeSequence(G, H);
  printf("\n\n");

  int degree = vertexDegree( G, 0 );
  printf("1- %d", degree);
  printf("\n\n");

  int adjacent = isAdjacent(G, 0, 1);
  printf("2- %d", adjacent);
  printf("\n\n");

  removeEdge( G, 0, 1);

  degree = vertexDegree( G, 0 );
  printf("3- %d", degree);
  printf("\n\n");

  adjacent = isAdjacent(G, 0, 1);
  printf("4- %d", adjacent);
  printf("\n\n");

  printf("5- ");
  adjacentVertex( G, 0 );
  printf("\n");

  return 0;
}
