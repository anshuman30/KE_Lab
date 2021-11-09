#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string data;
    map<string,int> freq;
    //string str="";
    while(cin>>data){
        if(data.front()>='a' && data.front()<='z'){
            freq[data]+=1;
        }
        
    }
    for(auto it=freq.begin();it!=freq.end();it++){
        cout<<it->first<<" "<<it->second<<"\n";
    }
    return 0;
}