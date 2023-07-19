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
        if(Size[a]<Size[b]) swap(a,b);
        parent[b]=a;
        Size[a]+=Size[b];
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
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("kruskal.txt");
    int n,m;
    in>>n>>m;
    vector<pair<int,pair<int,int>>>graph;

    for(int i=1; i<=n; i++)
    {
        make(i);
    }
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        in>>u>>v>>w;
        graph.push_back({w,{u,v}});
    }
    int finalWeight=0;
    vector<pair<int,int>>edges=KruskalAlgorithm(graph,finalWeight);
    out<<finalWeight<<endl;
    for(int i=0; i<edges.size(); i++)
    {
        out<<edges[i].first<<" "<<edges[i].second<<endl;
    }
    in.close();
    out.close();





}



