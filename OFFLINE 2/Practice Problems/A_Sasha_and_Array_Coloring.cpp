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
    ll n;
    cin>>n;
    vector<ll>num;
    for(int i=0;i<n;i++)
    {
        ll x;
        cin>>x;
        num.push_back(x);
    }
    sort(all(num));
    int sum=0;
    for(int i=0;i<(n/2);i++)
    {
        sum+=abs(num[i]-num[n-1-i]);
    }
    cout<<sum<<endl;
    





    }
    

}