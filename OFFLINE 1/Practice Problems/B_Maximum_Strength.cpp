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
    string a,b;
    cin>>a>>b;
    int maxi=max(a.size(),b.size());
    string first(maxi,'0');
    string second(maxi,'0');
    int j=a.size()-1;
    for(int i=first.size()-1;i>=0;i--)
    {
        first[i]=a[j];
        j--;
        if(j==-1) break;
    }
     j=b.size()-1;
    for(int i=first.size()-1;i>=0;i--)
    {
        second[i]=b[j];
        j--;
    }
    int index=-1;
    for(int i=0;i<first.size();i++)
    {
        if(first[i]!=second[i])
        {
            index=i;
            break;
        }
    }
    if(index==-1)
    {
        cout<<0<<endl;
        continue;
    }
    int x=first[index];
    int y=second[index];
    int ans=0;
    ans+=abs(x-y);
    if(index!=first.size()-1)
    {
        index++;
    int m=first[index]-'0';
    int n=second[index]-'0';
     ans+=9;
    }

   
    int remain=first.size()-(index+1);
    remain=remain*9;
    ans+=remain;
    cout<<ans<<endl;
   

   





    }
    

}