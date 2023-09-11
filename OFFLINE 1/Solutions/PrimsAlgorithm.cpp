#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<limits.h>
#include<fstream>
using namespace std;
const int N=1e5;
vector<int>visited(N,false);
class edge
{
public:
    int v1;
    int v2;
    double w;
    edge(int v1,int v2,double w)
    {
        this->v1=v1;
        this->v2=v2;
        this->w=w;
    }

};
vector<pair<int,int>> PrimsAlgo(vector<vector<pair<int,double>>> &graph,double &finalWeight)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    int v=graph.size();
    vector<double> weight(v, INT_MAX);
    vector<int> parent(v, -1);
    vector<bool>inMST(v,false);
    pq.push({0,0});
    weight[0]=0;
    vector<pair<int,int>>edges;
    while(!pq.empty())
    {
        int u=pq.top().second;
        if(!inMST[u]) finalWeight+=weight[u];
        pq.pop();
        inMST[u]=true;
        for(auto child: graph[u])
        {
            int child_v=child.first;
            double child_w=child.second;

            if(!inMST[child_v] && child_w<weight[child_v])
            {
                weight[child_v]=child_w;
                parent[child_v]=u;
                pq.push({child_w,child_v});

            }

        }



    }
    for(int i=1; i<parent.size(); i++)
    {
        edges.push_back({parent[i],i});
    }



    return edges;


}



int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int, double>>> graph(n, vector<pair<int, double>>());

    vector<edge>v;
    for(int i=0; i<m; i++)
    {
        int v1,v2;
        double w;
        cin>>v1>>v2>>w;
        if(v1!=v2)
        {
            edge x(v1,v2,w);
            v.push_back(x);
        }
    }

    for(int i=0; i<v.size(); i++)
    {
        int v1=v[i].v1;
        int v2=v[i].v2;
        double w=v[i].w;

        graph[v1].push_back({v2,w});
        graph[v2].push_back({v1,w});

    }
    double finalweight=0;
    vector<pair<int,int>>edges=PrimsAlgo(graph,finalweight);
    cout<<"Prim-Jarnik Algorithm: "<<endl;
    cout<<"Total weight: "<<finalweight<<endl;
    cout<<"Root Node " <<0<<endl;
    for(int i=0; i<edges.size(); i++)
    {
        cout<<edges[i].first<<" "<<edges[i].second<<endl;
    }
      







}
