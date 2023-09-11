#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define all(x) x.begin(),x.end()
const int N=10e5+10;
typedef long long int ll;

int main() {
    ifstream in;
    ofstream out;
    string currentFilePath = __FILE__;

    size_t found = currentFilePath.find_last_of("/\\");
    string currentDirectory = currentFilePath.substr(0, found);

    string inputFilePath = currentDirectory + "/input.txt";
    string outputFilePath = currentDirectory + "/output.txt";

    in.open(inputFilePath);
    out.open(outputFilePath);

    int x;
    in >> x;
    out << x << endl;
    cout << x << endl;

    in.close();
    out.close();
    return 0;
}
