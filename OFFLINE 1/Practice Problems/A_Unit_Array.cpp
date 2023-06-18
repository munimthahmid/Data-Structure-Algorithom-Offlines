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
    int one=0;
    int minusone=0;
    for(int i=0;i<n;i++)
    {
        ll x;
        cin>>x;
        num.push_back(x);
        if(x==1) one++;
        if(x==-1) minusone++;
    }
    int op=0;
    if(minusone%2==0 && (one>=minusone))
    {
        cout<<0<<endl;
        continue;
    }
 
        if(one>=minusone)
        {
            op++;
            minusone--;
            one++;
            cout<<op<<endl;
            continue;
        }
        if(minusone>one)
        {
            int diff=abs(one-minusone);
            int k;
            if(diff%2!=0)
            {
                k=(diff+1)/2;
            }
            else k=diff/2;
            one+=k;
            minusone-=k;
            op+=k;
            if(minusone%2!=0) op++;
            cout<<op<<endl;
        }
    }
 



    }
