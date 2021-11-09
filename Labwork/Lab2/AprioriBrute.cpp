#include<bits/stdc++.h>
using namespace std;

void getItemset(vector<string> items,int i,vector<set<int> > &cur,set<int> pres){
    if(i==items.size()){
        cur.push_back(pres);
    }
    else{
        getItemset(items,i+1,cur,pres);
        pres.insert(i);
        getItemset(items,i+1,cur,pres);
    }
}

bool find(vector<string> v,string d){
    for(int i=0;i<v.size();i++){
        if(v[i].compare(d)==0){
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string data;
    map<string,int> freq;
    vector<string> items;
    string pres;
    map<string,vector<string> > transac;
    //string str="";
    while(cin>>data){
        if(data.front()>='a' && data.front()<='z'){
            freq[data]+=1;
            transac[pres].push_back(data);
        }
        if(data.front()=='T'){
            pres=data;
        }
    }
    for(auto it=freq.begin();it!=freq.end();it++){
        items.push_back(it->first);
    }
    vector<set<int> > itemsets;
    set<int> s;
    getItemset(items,0,itemsets,s);
    int min_sup=2;
    for(int i=0;i<itemsets.size();i++){
        map<string,int> mp;
        int cp=0;
        if(itemsets[i].size()==0){
            continue;
        }
        for(auto it=itemsets[i].begin();it!=itemsets[i].end();it++){
            mp[items[*it]]=1;
        }
        for(auto tit=transac.begin();tit!=transac.end();tit++){
            int f=0;
            for(auto mpit=mp.begin();mpit!=mp.end();mpit++){
                if(!find(tit->second,mpit->first)){
                    f=1;
                    break;
                }
            }
            if(f==0){
                cp++;
            }
        }
        if(cp>=min_sup){
            for(auto mpit=mp.begin();mpit!=mp.end();mpit++){
                cout<<mpit->first<<" ";
            }
            cout<<" :- "<<cp<<"\n";
        }
    }
    return 0;
}