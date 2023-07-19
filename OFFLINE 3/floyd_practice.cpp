#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;

int main()
{
  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> distance(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        distance[u][v] = w;
        distance[u][u] = 0;
        distance[v][v] = 0;
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {

                int cur_dist = distance[i][k] + distance[k][j];
                if(distance[i][k]!=INF && distance[k][j]!=INF)
                distance[i][j] = min(cur_dist, distance[i][j]);
            }
        }
    }

    for (int i = 1; i < distance.size(); i++)
    {
        for (int j = 1; j < distance[1].size(); j++)
        {
            if (distance[i][j] == INF)
                cout << "INF"
                    << " ";
            else
                cout << distance[i][j] << " ";
        }
        cout << endl;

}
}
