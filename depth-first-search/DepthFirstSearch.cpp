#include <bits/stdc++.h>
#include "../Libraries/ListAdjacency.h"

using namespace std;

typedef struct edge
{
  int outVertex, inVertex;
} Edge;

vector<Edge> depthFirstSearch(Graph* G)
{
    
    Vertex *p;
    stack<int> vertex;
    int r, v, w, alc=0, exp=0;
    vector<int> Alc, Exp;
    vector<vector<int>> notExplored(G->V,vector<int>(G->E/2));
    Edge edge;
    vector<Edge> setEdge;


    for( int i= 0; i < G->V; i++)
    {
        Alc.push_back(0);
        Exp.push_back(0);
            
    }

    r = 0;
    vertex.push(r);
    alc=1;
    Alc[r] = alc;

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
                    edge.outVertex = v;
                    edge.inVertex = w;
                    setEdge.push_back(edge);

                }
                break;
            }
            else
                p = p->next;            
        }
        if( p == NULL )
        {
            vertex.pop();
            exp++;
            Exp[v] = exp;
        }
    }

    return setEdge;
}

int main()
{
    int nVertices, vertice, nEdges, result, i, rem;
    vector<Edge> edges;

    Graph* G = createGraph( 8 );

    // insertEdge(G, 6, 7);
    // insertEdge(G, 0, 5);
    // insertEdge(G, 0, 3);
    // insertEdge(G, 0, 2);
    // insertEdge(G, 0, 1);
    // insertEdge(G, 1, 3);
    // insertEdge(G, 1, 2);
    // insertEdge(G, 2, 3);
    // insertEdge(G, 5, 6);
    // insertEdge(G, 5, 4);
    // insertEdge(G, 4, 6);

    insertEdge(G, 0, 1);
    insertEdge(G, 1, 2);
    insertEdge(G, 2, 3);
    insertEdge(G, 3, 1);

    showGraph( G );
    cout << G->E;

     
    
    edges = depthFirstSearch( G );
    // cout << endl << edges.size() << endl; 
    
    // for (std::map<int,int>::iterator it=edges.begin(); it!=edges.end(); ++it)
    // std::cout << it->first << " => " << it->second << '\n';
    
    // cin >> nVertices;
    // cin >> nEdges;

    // Graph* G = createGraph( nVertices);
    // Graph* H = createGraph( nVertices);

    
    // for ( i = 0; i < nEdges; i++ )
    // {
    //     cin >> vertice;
    //     cin >> Edge;
    //     insertEdge( G, vertice, Edge );
    //     insertEdge( H, vertice, Edge );
    // }

    // showGraph( G );
    // showGraph( H );

    return 0;
}