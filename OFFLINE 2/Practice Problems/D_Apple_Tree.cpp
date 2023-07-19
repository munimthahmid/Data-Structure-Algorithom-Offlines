#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define all(x) x.begin(),x.end()
const int N=10e5+10;
typedef long long int ll;

void dfs(int vertex,int parent,vector<vector<int>>&graph,vector<int>&leaf)
{
    for(int child:graph[vertex])
    {
        if(child==parent) continue;
        dfs(child,vertex,graph,leaf);
    }
    if(leaf[vertex]==0) 
    {
        leaf[parent]+=1;
        leaf[vertex]=1;
    }
    else leaf[parent]+=leaf[vertex];

}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    ll n;
    cin>>n;
    vector<int>leaf(n+1,0);
   vector<vector<int>>graph(n+1);
   for(int i=0;i<n-1;i++)
   {
    int u, v;
    cin>>u>>v;
    graph[u].push_back(v);
    graph[v].push_back(u);
   }
   dfs(1,0,graph,leaf);
   int q;
   cin>>q;
   for(int i=0;i<q;i++)
   {
    int u,v;
    cin>>u>>v;
    ll a=leaf[u];
    ll b=leaf[v];
    ll ans=a*b;
    cout<<ans<<endl;
   }
   





    }
    

}