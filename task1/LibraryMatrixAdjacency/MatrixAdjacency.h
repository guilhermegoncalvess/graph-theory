typedef struct graph {
    int V;
    int E;
    int **adj;
    int* degreeSequence;
} Graph;

// Question 01.a)
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

// Question 01.a)
Graph *createGraph( int V ) {
  Graph* G = ( Graph* )malloc( sizeof( Graph ));
  G->V = V;
  G->E = 0;
  G->degreeSequence = ( int* )malloc( V * sizeof( int ));
  G->adj = allocateMatrixAdj(V, V, 0);

  return G;
}

// Question 01.a)
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

// Question 01.b)
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

// Question 01.d)
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

// Question 01.c)
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

// Question 01.e)
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

// Question 01.f)
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