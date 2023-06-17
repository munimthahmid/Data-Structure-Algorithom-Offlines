
#include<bits/stdc++.h>
using namespace std;


vector<pair<int,int>> PrimsAlgorithm(vector<vector<pair<int,int>>>&graph,int &finalweight)
{
    priority_queue<pair<int,int>>pq;
    int v=graph.size();
    vector<int>weight(v,0);
    vector<int>parent(v,-1);
    vector<bool>inMST(v,false);
    pq.push({0,1});
    weight[1]=0;
    vector<pair<int,int>>edges;
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();
        inMST[u]=true;
        for(auto child:graph[u])
        {

            int child_v=child.first;
            int child_w=child.second;
            if(!inMST[child_v] && child_w>=weight[child_v])
            {
                weight[child_v]=child_w;
                parent[child_v]=u;
                pq.push({child_w,child_v});

            }
        }
    }
    for(int i=2;i<parent.size();i++)
    {
        finalweight+=weight[i];
        edges.push_back({i,parent[i]});
        cout<<i<<" "<<parent[i]<<endl;
    }
    return edges;
    
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>mengraph(n+1);
    vector<vector<pair<int,int>>>womengraph(n+1);

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        if(w!=2)
        {
             mengraph[u].push_back({v,w});
             mengraph[v].push_back({u,w});
        }
        
        if(w!=1)
        {
             womengraph[u].push_back({v,w});
             womengraph[v].push_back({u,w});
    }
        }
    int finalWeight=0;
    vector<pair<int,int>>edges=PrimsAlgorithm(mengraph,finalWeight);
    vector<pair<int,int>>edges2=PrimsAlgorithm(womengraph,finalWeight);
    set<pair<int,int>>edgesfinal;
    for(int i=0;i<edges.size();i++)
    {
        cout<<edges[i].first<<" "<<edges[i].second<<endl;
        edgesfinal.insert(edges[i]);
    }
    for(int i=0;i<edges2.size();i++)
    {
        edgesfinal.insert(edges2[i]);
    }
    int k=edgesfinal.size();
    cout<<m-k<<endl;


}
