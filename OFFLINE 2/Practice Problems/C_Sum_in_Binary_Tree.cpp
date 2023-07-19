#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define all(x) x.begin(),x.end()
const int N=10e5+10;
typedef long long int ll;
vector<int>leaf(N,0);
void dfs(int vertex,int parent,vector<vector<int>>&graph)
{
    for(int child:graph[vertex])
    {
        if(child==parent) continue;
        dfs(child,vertex,graph);
    }
    if(leaf[vertex]==0) leaf[parent]+=1;
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
    ll sum=0;
    while(n>0)
    {
        sum+=n;
        n=n/2;
    }
    cout<<sum<<endl;
   





    }
    

}