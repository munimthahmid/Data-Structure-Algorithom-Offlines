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
    for(ll i=1;i<=t;i++)
    {
    ll n;
    cin>>n;
    vector<ll>num;
    for(ll i=0;i<n;i++)
    {
        ll x;
        cin>>x;
        num.push_back(x);
    }
    ll sum=0;
    for(ll i=0;i<num.size();i++)
    {
        sum+=abs(num[i]);
    }
    ll op=0;
    vector<ll>newnum;
    for(ll i=0;i<num.size();i++)
    {
        if(num[i]==0) continue;
        if(num[i]>0) newnum.push_back(1);
        else newnum.push_back(-1);
    }
    auto it=unique(all(newnum));
    newnum.resize(distance(newnum.begin(),it));
    ll ans=count(all(newnum),-1);
//     for(int i=0;i<newnum.size();i++)
//     {
//         cout<<newnum[i]<<" ";
//     }
//     cout<<endl;
//    bool lag=false;
    cout<<sum<<" "<<ans<<endl;





    }
    

}