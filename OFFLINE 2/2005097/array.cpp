#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define all(x) x.begin(), x.end()
const int N = 10e5 + 10;
const int INF = 1e9 + 10;

typedef long long int ll;
vector<vector<pair<int, int>>> graph(N);
vector<int> dist(N, INF);
vector<int> parent(N, -1);
int dijkstra(int source, int dest)
{
    vector<bool> visited(N, false);
    set<pair<int, int>> s;
    s.insert({0, source});
    dist[source] = 0;
    while (s.size() > 0)
    {
        auto node = *s.begin();
        int wt = node.first;
        int v = node.second;
        s.erase(s.begin());
        if (visited[v] == true)
            continue;
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

    ll n;
    cin >> n;
    vector<ll> num;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        num.push_back(x);
    }
    graph[0].push_back({1, 1});
    for (int i = 1; i < num.size(); i++)
    {

        if (num[0] == num[i])
        {
            graph[0].push_back({i, 1});
        }
    }
    for (int i = 1; i < num.size(); i++)
    {

        graph[i].push_back({i - 1, 1});
        if (i != num.size() - 1)
            graph[i].push_back({i + 1, 1});
        for (int j = i; j < num.size(); j++)
        {
            if (i == j)
                continue;
            if (num[i] == num[j])
            {
                graph[i].push_back({j, 1});
            }
        }
    }
    int ans = dijkstra(0, num.size() - 1);
    cout << ans << endl;
    path(num.size() - 1);
}