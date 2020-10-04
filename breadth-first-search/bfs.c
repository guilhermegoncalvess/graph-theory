#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int no;
    struct list *prox;
    struct list *ant;
} List;

typedef struct edge
{
  int outVertex, inVertex;
} Edge;

typedef struct setEdge
{
  Edge* edge;
  int length;
} setEdge;

typedef struct head 
{
  List* begin;
  List* last;
}Head;

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


List* newNode( int x )
{
  List* novo = ( List* )malloc( 1*sizeof( List ));

  if( novo == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  novo->no = x;
  novo->prox = NULL;
  novo->ant = NULL;

  return novo;
}

void insertList( Head* l, int x )
{
  List *p = l->begin;
  List *u = l->last;
  List* new = newNode( x );
  
  if( new != NULL )
  {
    if( l->begin == NULL && l->last == NULL )
    {
      l->begin = new;
      l->last = new;
    }
    else 
    {
      l->last->prox = new;
      new->ant = l->last;
      l->last = new;
    }
  }
}   

void insertQueue( Head* l, int x )
{
  List *p = l->begin;

  List* new = newNode( x );
  
  if( new != NULL )
  {
    if( p == NULL )
      l->begin = new;
    else 
    {
      while ( p->prox != NULL )
        p = p->prox;
      
      
      new->prox = l->begin;
      l->begin->ant = new;
      l->begin = new;
    }

  }

} 

int searchList( Head* l, int x )
{
  List* p = l->begin;
  List* aux = l ->begin->prox;

  while ( p != NULL && p->no != x)
  { 
    p = p->prox;
  }

  return p == NULL ? 0 : 1;
  
}

void removeList( Head* l, int x )
{
  List* p = l->begin;
  List* aux = l ->begin->prox;

  while ( p != NULL && p->no != x)
  { 
    p = p->prox;
    aux = aux->prox;
  }
  
  if( p == l->begin )
  {
    l->begin = aux;
    free( p );
  }
  else
  {
    if(aux != NULL && p->no == x )
    {
      p->ant->prox = aux;
      aux->ant = p->ant;
      free( p );
    }
    
    if( aux == NULL && p->no == x )
    {
      l->last = p->ant;
      free( p );
    } 
  }
  
}


void bfsGeneric(Grafo* G)
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
    if( G->adj[v].prox != NULL )
    {  
      w = G->adj[v].prox->no;
      removeAresta( G, v, w );

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

setEdge spanningTree(Grafo* G)
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
    if( G->adj[v].prox != NULL )
    {  
      w = G->adj[v].prox->no;
      removeAresta( G, v, w );

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

setEdge bsf(Grafo* G)
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
    if( G->adj[v].prox != NULL )
    {  
      w = G->adj[v].prox->no;
      removeAresta( G, v, w );

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
  int nVertices, vertice, nArestas, aresta, result, i, rem;

  scanf("%d%d", &nVertices, &nArestas );

  Grafo* G = criaGrafo( nVertices);
  Grafo* H = criaGrafo( nVertices);

  // insereAresta( G, 0, 1); 
  // insereAresta( G, 0, 2); 
  // insereAresta( G, 0, 3); 
  // insereAresta( G, 1, 2); 
  // insereAresta( G, 2, 3); 
  // insereAresta( H, 0, 1); 
  // insereAresta( H, 0, 2); 
  // insereAresta( H, 0, 3); 
  // insereAresta( H, 1, 2); 
  // insereAresta( H, 2, 3); 
  
  for ( i = 0; i < nArestas; i++ )
  {
    scanf("%d%d", &vertice, &aresta );
    insereAresta( G, vertice, aresta );
    insereAresta( H, vertice, aresta );
  }

  imprimeGrafo( G );
  imprimeGrafo( H );
  bfsGeneric(G);

  setEdge e = spanningTree(H);

  for( i = 0; i < e.length; i++)
  {
    printf("%d %d", e.edge[i].outVertex, e.edge[i].inVertex );
    printf("\n");
  }

  // Head* l = ( Head* )malloc( 1*sizeof( Head ));
  // l->begin = NULL;  
  // l->last = NULL;  
  

  // insertList( l, 2 );
  // insertList( l, 4 );
  // insertList( l, 6 );

  // List* p = l->begin;
  // while (p != NULL )
  // {
  //   printf("%d", p->no);
  //   p = p->prox;
  // }
  
  // removeList( l, 2);

  // p = l->begin;
  // while (p != NULL )
  // {
  //   printf("%d", p->no);
  //   p = p->prox;
  // }

  // int x = searchList( l, 6);
  // printf("%d", x);

  return 0;
}
