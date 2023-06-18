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
    string a,b;
    cin>>a>>b;
    int thikdis=0;
    int ultdis=0;
    if(a==b)
    {
        cout<<0<<endl;
        continue;
    }
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i]) thikdis++;
    }
   reverse(all(b));
   for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i]) ultdis++;
    }
    if(thikdis!=0 && ultdis==0)
    {
        cout<<2<<endl;
        continue;
    }
    if(thikdis==ultdis)
    {
        int dis=thikdis-1;
        int ans=2*dis+1;
        cout<<ans<<endl;
        continue;
    }

    int dis=min(thikdis,ultdis);
    dis--;
    int ans=0;
    if(dis+1==thikdis)
    {
        ans+=2*dis;
        if(dis%2==0)
        {

        }
        else
        {
            ans+=1;
        }
        ans+=1;
        cout<<ans<<endl;
    }
    else
    {
        ans+=2*dis;
        if(dis%2==0)
        {
            ans+=1;
        }
        ans+=1;
        cout<<ans<<endl;
    }
   





    }
    

}