#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string data;
    map<string,vector<string>> mp;
    string transac;
    string temp;
    while(getline(cin,data)){
        stringstream stream(data);
        int count=0;
        while(getline(stream,temp,' ')){
            
            if(count==0){
                transac=temp;
            }
            else{
                mp[temp].push_back(transac);
            }
            count++;
        }
    }
    //map<string,vector<string>>::iterator it;
    for(auto it=mp.begin();it!=mp.end();it++){
        cout<<it->first<<" ";
        for(int i=0;i<it->second.size();i++){
            cout<<it->second[i]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}