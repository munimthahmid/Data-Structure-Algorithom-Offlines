#include <iostream>
#include<vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
vector<int>parent(N);
vector<int>Size(N);
multiset<int>sizes;
vector<int>weights;
typedef long long int ll;
void make(int v)
{
    parent[v]=v;
    Size[v]=1;
}
int find(ll v)
{
    if(v==parent[v]) return v;
    return parent[v]=find(parent[v]);

}
void Union(ll a,ll b)
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
vector<pair<ll,ll>> KruskalAlgorithm(vector<pair<ll,pair<ll,ll>>>&graph,ll &weight)
{
    sort(graph.begin(),graph.end());
    vector<pair<ll,ll>>edges;
    for(int i=0; i<graph.size(); i++)
    {
        ll w=graph[i].first;
        ll u=graph[i].second.first;
        ll v=graph[i].second.second;
        if(find(u)==find(v)) continue;
        Union(u,v);
        weight+=w;
        weights.push_back(w);
        edges.push_back({u,v});

    }
    return edges;
}
int main()
{
   
    ll n,m,k;
    cin>>n>>m>>k;
    vector<pair<ll,pair<ll,ll>>>graph;

    for(ll i=1; i<=n; i++)
    {
        make(i);
    }
    for(int i=0; i<m; i++)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        graph.push_back({w,{u,v}});
    }
    ll finalWeight=0;
    vector<pair<ll,ll>>edges=KruskalAlgorithm(graph,finalWeight);
    if(k<weights.size()) cout<<-1<<endl;
    else
    {
        sort(weights.begin(),weights.end(),greater<ll>());
    ll curtotal=accumulate(weights.begin(),weights.end(),0LL);
    ll counter=0;
    for(ll i=0;i<weights.size();i++)
    {
        if(curtotal>k)
        {
            counter++;
            curtotal-=weights[i];
            curtotal+=1;
    cout<<"curtotal: "<<curtotal<<endl;

        }
        else break;
    }
    if(curtotal>k) cout<<-1<<endl;
    else cout<<counter<<endl;
    }
    
    




}



