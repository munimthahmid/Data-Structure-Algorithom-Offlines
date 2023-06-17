#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> parent(N);
vector<int> Size(N);
multiset<int> sizes;

void make(int v)
{
    parent[v] = v;
    Size[v] = 1;
    sizes.insert(1);
}

int find(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}

void Union(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a != b)
    {
        auto it = sizes.find(Size[a]);
        if (it != sizes.end())
            sizes.erase(it);
        
        auto it2 = sizes.find(Size[b]);
        if (it2 != sizes.end())
            sizes.erase(it2);
        
        if (Size[a] < Size[b])
            swap(a, b);
        
        parent[b] = a;
        Size[a] += Size[b];
        sizes.insert(Size[a]);
    }
}

vector<pair<int, int>> KruskalAlgorithm(vector<pair<int, pair<int, int>>>& graph, int& weight)
{
    sort(graph.begin(), graph.end());
    vector<pair<int, int>> edges;
    
    for (int i = 0; i < graph.size(); i++)
    {
        int w = graph[i].first;
        int u = graph[i].second.first;
        int v = graph[i].second.second;
        
        if (find(u) == find(v))
            continue;
        
        Union(u, v);
        weight += w;
        edges.push_back({ u, v });
    }
    
    return edges;
}

int findSecondBestMST(vector<pair<int, pair<int, int>>>& graph)
{
    int xweight=0;
        vector<pair<int,int>>y;

     for (int i = 0; i <=N; i++)
            make(i);
    vector<pair<int, int>> bestMST = KruskalAlgorithm(graph,xweight);
    vector<pair<int, int>> secondBestMST;
    cout<<xweight<<endl;
    int weight=INT_MAX;
    for (auto removedEdge : bestMST)
    {
        int removedEdgeWeight = -1;
        vector<pair<int, pair<int, int>>> modifiedGraph;
        
        for (auto edge : graph)
        {
            if (edge.second == removedEdge || edge.second == make_pair(removedEdge.second, removedEdge.first))
            {
                removedEdgeWeight = edge.first;
                continue;
            }
            modifiedGraph.push_back(edge);
        }
        
        sizes.clear();
        
        for (int i = 0; i < N; i++)
            make(i);
        int cur=0;
        vector<pair<int,int>> x=KruskalAlgorithm(modifiedGraph, cur);
        
        if(cur<weight)
        {
            y=x;
            weight=min(cur,weight);
        }
        
    }
    for(int i=0;i<y.size();i++)
    {
        cout<<y[i].first<<" "<<y[i].second<<endl;
    }
    
    return weight;
}

int main()
{
    int V, E;
    cin >> V;
    cin >> E;

    vector<pair<int, pair<int, int>>> graph;
    for (int i = 0; i < E; i++)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.push_back({ weight, {src, dest} });
    }

  int ans = findSecondBestMST(graph);

    // cout << "Edges in the second-best MST:" << endl;
    // for (auto edge : secondBestMST)
    // {
    //     cout << edge.first << " " << edge.second << endl;
    // }c
    cout<<ans<<endl;

    return 0;
}
