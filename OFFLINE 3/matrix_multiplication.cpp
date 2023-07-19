#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;

vector<vector<int>> PseudoMatrixMultiplication(vector<vector<int>> cur, vector<vector<int>> weight)
{
    int n = weight.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                cur[i][j] = min(cur[i][j], cur[i][k] + weight[k][j]);
            }
        }
    }
    return cur;
}

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
    vector<vector<int>> finaldistance = distance;

    for (int i = 0; i < n - 1; i++)
    {
        finaldistance = PseudoMatrixMultiplication(finaldistance, distance);
    }

    cout << "Shortest distance matrix" << endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (finaldistance[i][j] == INF)
                cout << "INF ";
            else
                cout << finaldistance[i][j] << " ";
        }
        cout << endl;
    }
}
