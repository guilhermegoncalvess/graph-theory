#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
  int node;
  struct vertex *next;
} Vertex;

typedef struct graph
{
  int V;
  int E;
  Vertex *adj;
} Graph;

Graph* createGraph( int V )
{
  Graph *G = ( Graph* )malloc( sizeof( Graph ));
  G->V = V;
  G->E = 0;
  G->adj = ( Vertex* )calloc( V, sizeof( Vertex ));

  return G;
}

Vertex* newVertex( int x )
{
  Vertex* new = ( Vertex* )malloc( sizeof( Vertex ));

  if( new == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  new->node = x;
  new->next = NULL;

  return new;
}

void insertEdge( Graph* G, int v, int w )
{
  if( v != w )
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
        Vertex* new = newVertex( w );
        new->next = G->adj[v].next;
        G->adj[v].next = new;
        G->E++;
    }
    p = G->adj[w].next;
    while ( p != NULL )
    {
        if( p->node == v )
            break;
        p = p->next;
    }
    if( p == NULL )
    {
        Vertex* new = newVertex( v );
        new->next = G->adj[w].next;
        G->adj[w].next = new;
        G->E++;
    }
  }
}

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

void imprimeGraph( Graph* G )
{
  int v;
  Vertex* w;

  for( v = 0; v < G->V; v++ )
  {
    printf( "%2d:", v );
    w = G->adj[v].next;

    while ( w != NULL )
    {
        printf( "%d", w->node );
        w = w->next;
    }
    printf("\n");
  }
}
int main()
{
  int nVertex, vertex, nEdge, Edge, result, i, rem;

  scanf( "%d%d", &nVertex, &nEdge );

  Graph* G = createGraph( nVertex );

  for ( i = 0; i < nEdge; i++ )
  {
    scanf( "%d%d", &vertex, &Edge );
    insertEdge( G, vertex, Edge );
  }

  showGraph( G );

  return 0;
}
