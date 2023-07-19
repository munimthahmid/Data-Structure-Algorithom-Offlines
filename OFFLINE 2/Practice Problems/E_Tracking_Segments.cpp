#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define all(x) x.begin(),x.end()
const int N=10e5+10;
typedef long long int ll;
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>graph(n+1);
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u].push_back({v,0});
        graph[v].push_back({u,0});
    }
    int q;
    cin>>q;
    int count=0;
    vector<int>queries;
    for(int i=0;i<q;i++)
    {
        int x;
        cin>>x;
        queries.push_back(x);
    }
    bool done=false;
    for(int i=0;i<queries.size();i++)
    {
        int x=queries[i];
                    count++;

        for(auto &child:graph[x])
        {
            child.second++;
            int a=child.first;
            graph[x][a].second=child.second;
            graph[a][x].second=child.second;

            int b=x;
            int weight=abs(a-b)+1-child.second;
            if(weight<child.second)
            {
                done=true;
                break;
            }


        
        }
        if(done==true) break;
    }
    cout<<count<<endl;
   





    }
    

}