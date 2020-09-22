#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int V;
    int E;
    int **adj;
    int* degreeSequence;
} Graph;

int **allocateMatrixAdj(int r, int c, int value)
{
  int i, j;
  int **m = (int**)malloc( r * sizeof( int * ));

  for( i = 0; i < r; i++ )
    m[i] = ( int *)malloc( c * sizeof( c *  sizeof ( int )));
  for( i = 0; i < r; i++ )
    for( j = 0; j < r; j++ )
        m[i][j] = value;

  return m;
}

Graph *createGraph( int V ) {
  Graph* G = ( Graph* )malloc( sizeof( Graph ));
  G->V = V;
  G->E = 0;
  G->degreeSequence = ( int* )malloc( V * sizeof( int ));
  G->adj = allocateMatrixAdj(V, V, 0);

  return G;
}

void insertEdge( Graph* G, int v, int w )
{
  if (v != w && G->adj[v][w] == 0 )
  {
    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
    G->E++;
  }
}

void removeEdge( Graph*G, int v, int w )
{
  if( G->adj[v][w] == 1 )
  {
    G->E--;
    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
  }
}

void showGraph( Graph* G, char name)
{
  int v, w;

  printf("%c\n", name);
  for ( v = 0; v < G->V; v++ )
  {
    printf("%2d:", v);
    for( w = 0; w < G->V; w++ )
        if( G->adj[v][w] == 1 )
            printf("%d ", w);
    printf("\n");
  }
  printf("\n");
}

int vertexDegree( Graph* G, int vertex )
{
  int w, sum=0;

  for( w = 0; w < G->V; w++ )
  {
      if( G->adj[vertex][w] == 1 )
          sum++;
  }

  return sum;
}

int isAdjacent( Graph* G, int firstVertex, int secondVertex )
{
  return G->adj[firstVertex][secondVertex] == 1 ? 1 : 0;
}

void adjacentVertex( Graph* G, int vertex )
{
  int i;

  printf("%d:", vertex);
  for ( i = 0; i < G->V; i++ )
  {
    if( G->adj[vertex][i] == 1 )
        printf("%d ", i);
  }
}

void insertionSort(int* arr, int length){
  int i, key, j;

  for (i = 1; i < length; i++)
  {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] < key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }

    arr[j + 1] = key;
  }
}

void degreeSequence( Graph* G )
{
  int i;

  for( i = 0; i < G->V; i++ )
    G->degreeSequence[i] = vertexDegree( G, i );

  insertionSort( G->degreeSequence, G->V );
}

void showDegreeSequence( int* sequence, int length, char name )
{
  int i;

  printf("%c: ", name);

  for( i = 0; i < length; i++ )
    printf("%d ", sequence[i]);

  printf("\n");

}

void verifyDegreeSequence( Graph* G, Graph* H )
{
  int i;

  degreeSequence( G );
  degreeSequence( H );

  showDegreeSequence(G->degreeSequence, G->V, 'G');
  showDegreeSequence(H->degreeSequence, H->V, 'H');

  if( G->V == H->V )
  {
    for( i = 0; i < G->V; i++ )
    {
      if( G->degreeSequence[i] != H->degreeSequence[i] )
        break;
    }

    if( i != G->V )
      printf("The sequences not equals.");
    else
      printf("The sequences are equals.");
  }
  else
    printf("The sequences must be of equal length.\n");

}

int main()
{
  int nVertex, nEdgeG, nEdgeH, firstVertex, sencondVertex, i=0;

  scanf("%d%d", &nVertex, &nEdgeG);
  Graph* G = createGraph( nVertex );

  scanf("%d%d", &nVertex, &nEdgeH);
  Graph* H = createGraph( nVertex );

  while (scanf("%d%d", &firstVertex, &sencondVertex) != EOF)
  {
      if( i < nEdgeG )
          insertEdge( G, firstVertex, sencondVertex );
      else
          insertEdge( H, firstVertex, sencondVertex );
      i++;
  }

  showGraph(G, 'G');
  showGraph(H, 'H');
  printf("\n");

  verifyDegreeSequence(G, H);
  printf("\n\n");

  int grau = vertexDegree( G, 0 );
  printf("1- %d", grau);
  printf("\n\n");

  int adjacent = isAdjacent(G, 0, 1);
  printf("2- %d", adjacent);
  printf("\n\n");

  removeEdge( G, 0, 1);

  grau = vertexDegree( G, 0 );
  printf("3- %d", grau);
  printf("\n\n");

  adjacent = isAdjacent(G, 0, 1);
  printf("4- %d", adjacent);
  printf("\n\n");

  printf("5- ");
  adjacentVertex( G, 0 );
  printf("\n");

  return 0;
}
