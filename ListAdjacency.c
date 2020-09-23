#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
  int no;
  struct vertice *prox;
} Vertice;

typedef struct grafo
{
  int V;
  int E;
  Vertice *adj;
} Grafo;

Grafo* criaGrafo( int V )
{
  Grafo *G = ( Grafo* )malloc( sizeof( Grafo ));
  G->V = V;
  G->E = 0;
  G->adj = ( Vertice* )calloc( V, sizeof( Vertice ));

  return G;
}

Vertice* novoVertice( int x )
{
  Vertice* novo = ( Vertice* )malloc( sizeof( Vertice ));

  if( novo == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  novo->no = x;
  novo->prox = NULL;

  return novo;
}

void insereAresta( Grafo* G, int v, int w )
{
  if( v != w )
  {
    Vertice *p = G->adj[v].prox;

    while ( p != NULL )
    {
        if( p->no == w )
            break;
        p = p->prox;
    }
    if( p == NULL )
    {
        Vertice* novo = novoVertice( w );
        novo->prox = G->adj[v].prox;
        G->adj[v].prox = novo;
        G->E++;
    }
    p = G->adj[w].prox;
    while ( p != NULL )
    {
        if( p->no == v )
            break;
        p = p->prox;
    }
    if( p == NULL )
    {
        Vertice* novo = novoVertice( v );
        novo->prox = G->adj[w].prox;
        G->adj[w].prox = novo;
        G->E++;
    }
  }
}

void removeAresta( Grafo* G, int v, int w )
{
  if( G->adj[v].prox != NULL )
  {
    Vertice* aux = G->adj[v].prox;
    Vertice* preaux = &(G->adj[v]);

    while ( aux != NULL)
    {
        if( aux->no == w )
            break;
        preaux = aux;
        aux = aux->prox;
    }
    if ( aux != NULL)
    {
        G->E--;
        preaux->prox = aux->prox;
        free(aux);
    }
  }
  if ( G->adj[w].prox != NULL )
  {
    Vertice* aux = G->adj[w].prox;
    Vertice* preaux = &(G->adj[w]);

    while ( aux != NULL)
    {
        if( aux->no == v )
            break;
        preaux = aux;
        aux = aux->prox;
    }
    if ( aux != NULL)
    {
        G->E--;
        preaux->prox = aux->prox;
        free(aux);
    }
  }
}

void imprimeGrafo( Grafo* G )
{
  int v;
  Vertice* w;

  for( v = 0; v < G->V; v++ )
  {
    printf( "%2d:", v );
    w = G->adj[v].prox;

    while ( w != NULL )
    {
        printf( "%d", w->no );
        w = w->prox;
    }
    printf("\n");
  }
}
int main()
{
  int nVertices, vertice, nArestas, aresta, result, i, rem;

  scanf( "%d%d", &nVertices, &nArestas );

  Grafo* G = criaGrafo( nVertices );

  for ( i = 0; i < nArestas; i++ )
  {
    scanf( "%d%d", &vertice, &aresta );
    insereAresta( G, vertice, aresta );
  }

  imprimeGrafo( G );

  return 0;
}
