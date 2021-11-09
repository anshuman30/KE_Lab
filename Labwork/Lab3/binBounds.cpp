#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string dat;
    vector<int> val;
    int num_bins=3;

    while(cin>>dat){
        int t;
        stringstream stream(dat);
        stream>>t;
        val.push_back(t);
    }
    sort(val.begin(),val.end());
    int width = val.size()/num_bins;
    for(int i=0;i<val.size();i++){
        for(int j=i;j<i+width;j++){
            if(abs(val[j]-val[i])<abs(val[j]-val[i+width-1])){
                val[j]=val[i];
            }
            else{
                val[j]=val[i+width-1];
            }
        }
        i=i+width-1;
    }
    for(int i=0;i<val.size();i++){
        cout<<val[i]<<" ";
    }
    return 0;
}