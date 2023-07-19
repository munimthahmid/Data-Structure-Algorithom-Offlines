#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
const int INF = 1e9 + 10;
vector<pair<int, int>> graph[N];
vector<int> dist(N, INF);
vector<int> parent(N, -1);
int Bellman_Ford(int source, int dest, int v)
{
    dist[source] = 0;
    for (int i = 0; i < v - 1; i++)
    {
        for (int j = 0; j < v; j++)
        {
            for (auto child : graph[j])
            {
                int child_w = child.second;
                int child_v = child.first;
                if ((dist[j] + child_w) < dist[child_v])
                {

                    dist[child_v] = dist[j] + child_w;
                    parent[child_v] = j;
                }
            }
        }
    }
    for (int j = 0; j < v; j++)
    {
        for (auto child : graph[j])
        {
            int child_w = child.second;
            int child_v = child.first;
            if ((dist[j] + child_w) < dist[child_v])
            {

                return -INF;
            }
        }
    }

    return dist[dest];
}
void path(int dest)
{
    if (dest == -1)
        return;
    path(parent[dest]);
    if (parent[dest] != -1)
        cout << "->" << dest;
    else
        cout << dest;
}
int main()
{
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("Bellman_Ford.txt");
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    int source, dest;
    cin >> source >> dest;
    int ans = Bellman_Ford(source, dest, n);
    if (ans == -INF)
        cout << "Negative edge cycle detected" << endl;
    else
    {
        cout << ans << endl;
        path(dest);
    }
    in.close();
    out.close();
}