#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;

int main()
{
  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> distance(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        distance[u][v] = w;
        distance[u][u] = 0;
        distance[v][v] = 0;
    }
    bool neg=false;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                int cur_dist = distance[i][k] + distance[k][j];
                if(distance[i][k]!=INF && distance[k][j]!=INF)
                {
                distance[i][j] = min(cur_dist, distance[i][j]);
                }
            }
          
        }
       
    }
    for(int i=0;i<n;i++)
    {
        if(distance[i][i]<0) neg=true;

    }

   if(neg==true) cout<<"Yes"<<endl;
   else cout<<"No"<<endl;
}
