#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;

int main()
{
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("Floyd_Warshall.txt");
    int n, m;
    in >> n >> m;
    vector<vector<int>> distance(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        in >> u >> v >> w;
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
                distance[i][j] = min(cur_dist, distance[i][j]);
            }
        }
    }
    out << "Shortest distance matrix" << endl;

    for (int i = 1; i < distance.size(); i++)
    {
        for (int j = 1; j < distance[1].size(); j++)
        {
            if (distance[i][j] == INF)
                out << "INF"
                    << " ";
            else
                out << distance[i][j] << " ";
        }
        out << endl;
    }
    in.close();
    out.close();
}