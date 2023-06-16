#include <iostream>
#include<vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
vector<int>parent(N);
vector<int>Size(N);
multiset<int>sizes;

void make(int v)
{
    parent[v]=v;
    Size[v]=1;
    sizes.insert(1);
}
int find(int v)
{
    if(v==parent[v]) return v;
    return parent[v]=find(parent[v]);

}
void Union(int a,int b)
{
    a=find(a);
    b=find(b);

    if(a!=b)
    {
        auto it=sizes.find(Size[a]);
        if(it!=sizes.end()) sizes.erase(it);
        //
        auto it2=sizes.find(Size[b]);
        if(it2!=sizes.end()) sizes.erase(it2);
        if(Size[a]<Size[b]) swap(a,b);
        parent[b]=a;
        Size[a]+=Size[b];
        sizes.insert(Size[a]);
    }
}
vector<pair<int,int>> KruskalAlgorithm(vector<pair<int,pair<int,int>>>&graph,int &weight)
{
    sort(graph.begin(),graph.end());
    vector<pair<int,int>>edges;
    for(int i=0; i<graph.size(); i++)
    {
        int w=graph[i].first;
        int u=graph[i].second.first;
        int v=graph[i].second.second;
        if(find(u)==find(v)) continue;
        Union(u,v);
        weight+=w;
        edges.push_back({u,v});

    }
    return edges;
}
int main()
{
   
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>graph;

    for(int i=1; i<=n; i++)
    {
        make(i);
    }
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph.push_back({w,{u,v}});
    }
    int finalWeight=0;
    vector<pair<int,int>>edges=KruskalAlgorithm(graph,finalWeight);
    cout<<finalWeight<<endl;
    for(int i=0; i<edges.size(); i++)
    {
        cout<<edges[i].first<<" "<<edges[i].second<<endl;
    }
    




}



