#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define all(x) x.begin(),x.end()
const int N=10e5+10;
const int INF = 1e9 + 10;
typedef long long int ll;
ll sum(vector<vector<ll>>&num)
{
    ll sum=0;
    for(ll i=0;i<num.size();i++)
    {
        for(ll j=0;j<num[i].size();j++)
        {
         if(num[i][j]!=INF)   sum+=num[i][j];
        }
    }
    return sum;
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    ll n;
    cin>>n;
    vector<ll>num;
    vector<vector<ll>> distance(n , vector<ll>(n , INF));
    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<n;j++)
        {
            ll x;
            cin>>x;
            distance[i][j]=x;
            distance[i][i]=0;
            distance[j][j]=0;
        }
    }
    vector<ll>deletions;
    for(ll i=0;i<n;i++)
    {
        ll x;
        cin>>x;
        deletions.push_back(x);
    }
   

    reverse(all(deletions));
    int j=0;
    vector<ll>ans;
     for (ll j=0; j < n; j++)
    {
       ll  k = deletions[j];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <n; j++)
            {

                ll cur_dist = distance[i][k] + distance[k][j];
                if(distance[i][k]!=INF && distance[k][j]!=INF)
                distance[i][j] = min(cur_dist, distance[i][j]);
            }
        }
       ll sumi=0;
       for(int i=0;i<k;i++)
       {
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<k;j++)
            {
                sumi+=distance[deletions[i]][deletions[j]];
            }
          
        }
          ans.push_back(sumi);
       }


    }
    reverse(all(ans));
    for(auto c:ans)

    {
        cout<<c<<" ";
    }
    cout<<endl;

   





    }
    

}
