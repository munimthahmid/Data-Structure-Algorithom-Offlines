#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
const int INF = 1e9 + 10;
vector<vector<pair<int, int>>> graph(N);
vector<int> dist(N, INF);
vector<int> parent(N, -1);
int dijkstra(int source, int dest)
{
    vector<bool> visited(N, false);
    set<pair<int, int>> s;
    s.insert({0, source});
    dist[source] = 0;
    while (s.size()>0)
    {
        auto node = *s.begin();
        int wt = node.first;
        int v = node.second;
        s.erase(s.begin());
        if(visited[v]==true) continue;
        visited[v] = true;
        for (auto child : graph[v])
        {
            
            int child_w = child.second;
            int child_v = child.first;
            if ((dist[v] + child_w) < dist[child_v])
            {

                dist[child_v] = dist[v] + child_w;
                s.insert({dist[child_v], child_v});
                parent[child_v] = v;
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
    out.open("Dijkstra.txt");
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, abs(w)});
    }
    int source, dest;
    cin >> source >> dest;
    int ans = dijkstra(source, dest);
    cout << ans << endl;
    path(dest);
    in.close();
    out.close();
}