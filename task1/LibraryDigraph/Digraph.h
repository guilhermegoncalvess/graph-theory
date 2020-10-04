// Question 02.c)
typedef struct edge
{
  int outVertex, inVertex;
  int weight;

} Edge;

typedef struct vertex 
{
  int node;
  int weight;
  struct vertex *next;

} Vertex;

typedef struct degreeVertex
{
  int outDegree;
  int inDegree;

} DegreeVertex;

typedef struct graph
{
  int V;
  int E;
  Vertex *adj;

} Graph;

// Question 02.a)
Graph* createGraph( int V )
{
  Graph *G = ( Graph* )malloc( sizeof( Graph ));
  G->V = V;
  G->E = 0;
  G->adj = ( Vertex* )calloc( V, sizeof( Vertex ));

  return G;
}

// Question 02.a)
Vertex* newVertex( int x, int weight )
{
  Vertex* new = ( Vertex* )malloc( sizeof( Vertex ));

  if( new == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  new->node = x;
  new->weight = weight;
  new->next = NULL;

  return new;
}

// Question 02.a)
void insertEdge( Graph* G, int v, int w , int weight)
{
  Vertex *p = G->adj[v].next;

  while ( p != NULL )
  {
    if( p->node == w )
        break;
    p = p->next;
  }

  if( p == NULL )
  {
    Vertex* new = newVertex( w, weight );
    new->next = G->adj[v].next;
    G->adj[v].next = new;
    G->E++;
  }
  
}

// Question 02.a)
void removeEdge( Graph* G, int v, int w )
{
  if( G->adj[v].next != NULL )
  {
    Vertex* aux = G->adj[v].next;
    Vertex* preaux = &(G->adj[v]);

    while ( aux != NULL)
    {
      if( aux->node == w )
          break;
      preaux = aux;
      aux = aux->next;
    }

    if ( aux != NULL)
    {
      G->E--;
      preaux->next = aux->next;
      free(aux);
    }
  }

  if ( G->adj[w].next != NULL )
  {
    Vertex* aux = G->adj[w].next;
    Vertex* preaux = &(G->adj[w]);

    while ( aux != NULL)
    {
      if( aux->node == v )
          break;
      preaux = aux;
      aux = aux->next;
    }

    if ( aux != NULL)
    {
      G->E--;
      preaux->next = aux->next;
      free(aux);
    }
  }
}

// Question 02.b)
void showGraph( Graph* G, char name )
{
  int v;
  Vertex* w;

  printf("%c\n", name);
  for( v = 0; v < G->V; v++ )
  {
    printf( "%2d: ", v );
    w = G->adj[v].next;

    while ( w != NULL )
    {
        printf( "%d %d  ", w->node, w->weight );
        w = w->next;
    }
    printf("\n");
  }
    printf("\n");
}

// Question 02.d)
Edge* graphEdges(Graph* G)
{
  int v, e=0;
  Vertex* w;
  Edge* edges = ( Edge* )malloc( G->E * sizeof( Edge ));

  for( v = 0; v < G->V; v++ )
  {
    w= G->adj[v].next;
    
    while ( w != NULL )
    {
      edges[e].outVertex = v;
      edges[e].inVertex = w->node;
      edges[e].weight = w->weight;
      e++;
      w = w->next;
    }
  }

  return edges;
}

void insertionSort(DegreeVertex* arr, int length){
  int i, j;
  DegreeVertex key;

  for (i = 1; i < length; i++)
  {
    key.outDegree = arr[i].outDegree;
    key.inDegree = arr[i].inDegree;

    j = i - 1;
    while (j >= 0 && arr[j].outDegree < key.outDegree)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }

    if( j >= 0 && arr[j].outDegree == key.outDegree)
    {
      if( arr[j].inDegree < key.inDegree )
      {
        arr[j + 1] = arr[j];
        j = j - 1;
      }
    }
    arr[j + 1] = key;
  }
}

// Question 02.e)
DegreeVertex* degreeSequence( Graph* G )
{
  int v, outEdge, i;
  Vertex* w;
  DegreeVertex* sequence = ( DegreeVertex* )malloc( G->V * sizeof( DegreeVertex ));

  for( v = 0; v < G->V; v++ )
  {
    w = G->adj[v].next;
    outEdge = 0;

    while ( w != NULL )
    {
      outEdge++;
      sequence[w->node].inDegree += 1;
      w = w->next;
    }

    sequence[v].outDegree = outEdge;
  }

  insertionSort( sequence, G->V );

  for ( i = 0; i < G->V; i++ )
  {
    printf("%d ", sequence[i].inDegree);
    printf("%d ", sequence[i].outDegree);
    printf("\n");
  }
  printf("\n");

  return sequence;
}

// Question 02.f)
void verifyDegreeSequence( Graph* G, Graph* H )
{
  int v;

  DegreeVertex* sequenceOne = degreeSequence( G );
  DegreeVertex* sequenceTwo = degreeSequence( H );

  if( G->V == H->V )
  {
    for( v = 0; v < G->V; v++ )
    {
      if( sequenceOne[v].outDegree != sequenceTwo[v].outDegree || sequenceOne[v].inDegree != sequenceTwo[v].inDegree )
        break;
    }

    if( v != G->V )
      printf("The sequences not equals.");
    else
      printf("The sequences are equals.");
  }
  else
    printf("The sequences must be of equal length.\n");

}