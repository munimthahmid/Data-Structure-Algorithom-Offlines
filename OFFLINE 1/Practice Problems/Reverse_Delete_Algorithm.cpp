/*
https://www.geeksforgeeks.org/reverse-delete-algorithm-minimum-spanning-tree/?ref=lbp
*/
#include<bits/stdc++.h>
using namespace std;
void dfs(int vertex,vector<bool>&visited,vector<vector<int>> &graph)
{
           

    visited[vertex]=true;
    for(int child:graph[vertex])
    {
        if(!visited[child])
        dfs(child,visited,graph);
    }
}
bool isConnected(vector<vector<int>>&graph)
{
    int n=graph.size();

    vector<bool>visited(n+1,false);
    dfs(graph[0].front(),visited,graph);

    bool check=true;
    for(int i=0;i<n;i++)
    {
        if(visited[i]==true) continue;
        else
        {
            check=false;
            break;
        }
    }
    return check;
}
int reverseDeletaionAlgorithm(vector<pair<int,pair<int,int>>>&graph,vector<vector<int>>&edges)
{
    int n=graph.size();
    int weight=0;
    sort(graph.begin(),graph.end());
    for(int i=graph.size()-1;i>=0;i--)
    {
        int u=graph[i].second.first;
        int v=graph[i].second.second;
        auto it=find(edges[u].begin(),edges[u].end(),v);
        auto it2=find(edges[v].begin(),edges[v].end(),u);

        edges[u].erase(it);
        edges[v].erase(it2);

        bool check=isConnected(edges);

        if(!check)
        {
            edges[u].push_back(v);
            edges[v].push_back(u);
             weight+=graph[i].first;
        }

    }
    return weight;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>graph;
    vector<vector<int>>edges(n);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph.push_back({w,{u,v}});
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int ans=reverseDeletaionAlgorithm(graph,edges);
    cout<<ans<<endl;
}
