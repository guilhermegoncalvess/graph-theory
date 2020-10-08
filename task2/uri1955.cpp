#include <bits/stdc++.h>
    using namespace std;


bool recognizeGraphBipartite( vector<vector<int>> G, int N )
{
    queue<int> vertex;
    int r, v, w, i;
    int Achieved[N], Level[N];

    for( i = 0; i< N; i++ )
    {
        Achieved[i] = 0;
    }

    r = 0;
    vertex.push( r );
    int achieved = 1;
    Achieved[r] = 1;
    Level[r] = 1;

    while ( !vertex.empty() )
    {
        v = vertex.front();

        for( w = 0; w < N; w++ )
        {
            if(G[v][w] == 1 )
            {    
                if( Achieved[w] == 0 )
                {
                    vertex.push( w );
                    achieved++;
                    Achieved[w] = achieved;
                    Level[w] = Level[v]+1;
                }
                if( Achieved[v] < Achieved[w] )
                {   
                    if(Level[v] == Level[w])    
                        return false;
                }
            }
        }

        vertex.pop();
    }

    return true;
}

int main()
{
    int N, n, i, j, x = 0;
    cin >> N;

    vector<vector<int>> matrix(N);

    for( i = 0; i < N; i++ )
    {
        for( j = 0; j < N; j++ )
        {
            cin >> n;
            n == 1 ? matrix[i].push_back(0) : matrix[i].push_back(1);
        }   
    }

    recognizeGraphBipartite( matrix, N) ? cout << "Fail!" << endl : cout << "Bazinga!" << endl;

    return 0;
}