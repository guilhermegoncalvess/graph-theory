#include <bits/stdc++.h>
// #include "../Libraries/ListAdjacency.h"

using namespace std;

typedef struct edge
{
  int outVertex, inVertex;
} Edge;
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
  Vertex* newNode = ( Vertex* )malloc( sizeof( Vertex ));

  if( newNode == NULL )
  {
    printf("ERRO \n");
    exit(1);
  }

  newNode->node = x;
  newNode->next = NULL;

  return newNode;
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
        Vertex* newNode = newVertex( w );
        newNode->next = G->adj[v].next;
        G->adj[v].next = newNode;
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
        Vertex* newNode = newVertex( v );
        newNode->next = G->adj[w].next;
        G->adj[w].next = newNode;
        G->E++;
    }
  }
}


vector<vector<int>> depthFirstSearch(Graph* G)
{
    Vertex *p;
    stack<int> vertex;
    int r, v, w, alc=0, exp=0, bridges=0, atual, edges=0, x, y;
    vector<int> Alc, Exp, tal(G->V);
    vector<vector<int>> notExplored(G->V,vector<int>(G->E/2));

    for( int i= 0; i < G->V; i++)
    {
        Alc.push_back(0);
        Exp.push_back(0); 
    }

    r = 0;
    vertex.push(r);
    alc=1;
    Alc[r] = alc;
    tal[r] = 0;
    while ( !vertex.empty())
    {
        v = vertex.top();
        p = G->adj[v].next;
        
        while( p != NULL )
        {
            w = p->node;
            if( notExplored[v][w] == 0 )
            {
                notExplored[v][w] = 1;
                notExplored[w][v] = 1;

                if( Alc[w] == 0)
                {
                    vertex.push(w);
                    alc++;
                    Alc[w] = alc;
                }
                else 
                {
                  notExplored[v][w] = -1;
                  notExplored[w][v] = -1;

                  stack<int> Copyvertex = vertex;
                  do
                  {
                    y = Copyvertex.top();
                    Copyvertex.pop();
                    x = Copyvertex.top();
                    notExplored[y][x] = -1;
                    notExplored[x][y] = -1;
                  } while ( x != w);
                }
                break;
            } 
            p = p->next;            
            
        }
        if( p == NULL )
        {
            vertex.pop();
            exp++;
            Exp[v] = exp;
            
        }
    }
    return notExplored;
}

int main()
{
    int nVertex, outVertex, nEdges, inVertex, i, rem;     
    
    vector<vector<int>> result;
        
    while (scanf("%d%d", &nVertex, &nEdges )!= EOF){
        
        if( nEdges >= nVertex )
        {
          Graph* G = createGraph( nVertex);

          for (int i = 0; i < nEdges; i++)
          {
              cin >> outVertex;
              cin >> inVertex;
              
              insertEdge( G, outVertex-1, inVertex-1 );
          }

          int count=0;
          result = depthFirstSearch( G );
          for (int i = 0; i < G->V; i++)
          {
            for (int j = 0; j < G->V; j++)    
              result[i][j] == -1 ? count +=1: count+=0;
          }
          cout << ((G->E)-count)/2 << endl;
        }
        else
        {
          
          cout << nVertex-1 << endl;
          for (int i = 0; i < nEdges; i++)
          {
              cin >> outVertex;
              cin >> inVertex;
          }
          
        }
    }
        
    return 0;
}