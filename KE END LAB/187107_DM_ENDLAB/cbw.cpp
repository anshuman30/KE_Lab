#include<bits/stdc++.h>
using namespace std;
int min_sup;

void get_subset(vector<string> tr,int l,int r,vector<string> &res,string cur,int i){
    if(i==tr.size()){
        res.push_back(cur);
    }
    else{
        get_subset(tr,l,r,res,cur,i+1);
        cur+=tr[i];
        get_subset(tr,l,r,res,cur,i+1);
    }
}

void print_vec(vector<string> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}

bool notFound(vector<string> v,string s){
    for(int i=0;i<v.size();i++){
        if(v[i].compare(s)==0){
            return false;
        }
    }
    return true;
}

void Trans(map<int,vector<string> > db,map<string,vector<int> > &T,vector<string> F1,vector<string> &F2,int &a){
    vector<string> C2;
    map<string,int> freq;
    for(int i=0;i<F1.size();i++){
        for(int j=0;j<F1.size();j++){
            string cand=F1[i]+F1[j];
            C2.push_back(cand);
        }
    }
    int numf=0;
    int dbSz=0;
    for(auto it=db.begin();it!=db.end();it++){
        dbSz++;
        int sz=it->second.size();
        for(auto it1=it->second.begin();it1!=it->second.end();it1++){
            if(notFound(F1,*it1)){
                it->second.erase(it1);
                sz--;
            }
        }
        numf+=it->second.size();
        if(sz>=3){
            for(int i=0;i<it->second.size();it++){
                T[it->second[i]].push_back(it->first);
            }
        }
        for(int i=0;i<it->second.size();i++){
            for(int j=i+1;j<it->second.size();j++){
                if(!notFound(C2,(it->second[i]+it->second[j]))){
                    freq[(it->second[i]+it->second[j])]++;
                }
            }
        }
    }
    for(auto it=freq.begin();it!=freq.end();it++){
        if(it->second>=min_sup){
            F2.push_back(it->first);
        }
    }
    a=numf/dbSz;
}

void Dwnsearch(map<int,vector<string> > db,vector<string> &DF,vector<string> Fa,int a){
    map<string,int> freq;
    for(auto it=db.begin();it!=db.end();it++){
        vector<string> allsub;
        string cur="";
        get_subset(it->second,3,a,allsub,cur,0);
        for(int j=0;j<allsub.size();j++){
            freq[allsub[j]]++;
        }
    }
    for(auto it=freq.begin();it!=freq.end();it++){
        if(it->second>=min_sup){
            DF.push_back(it->first);
        }
    }
}

void Upsearch(map<string,vector<int> > T,vector<string> &UF,vector<string> Fa,int a){
    if(Fa.size()==0){
        return;
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string dat;
    map<int,vector<string> > db;
    map<string,int> item_freq;
    int f=0;
    while(getline(cin,dat)){
        if(f==0){
            stringstream str(dat);
            str>>min_sup;
            f=1;
            continue;
        }
        string key="";
        int j=0;
        while(dat[j]!=' '){
            key+=dat[j];
            j++;
        }
        j++;
        stringstream stream(key);
        int k=0;
        stream>>k;
        string item="";
        while(j<dat.length()){
            if(dat[j]==' '){
                db[k].push_back(item);
                item_freq[item]++;
                item="";
            }
            else{
                item+=dat[j];
            }
            j++;
        }
        db[k].push_back(item);
    }
    /*for(auto it=db.begin();it!=db.end();it++){
        cout<<it->first<<" ";
        for(int i=0;i<it->second.size();i++){
            cout<<it->second[i]<<" ";
        }
        cout<<"\n";
    }*/
    //freq 1 itemsets
    vector<string> F1;
    for(auto it=item_freq.begin();it!=item_freq.end();it++){
        if(it->second>=min_sup){
            F1.push_back(it->first);
        }
    }
    //print_vec(F1);
    map<string,vector<int> > T;
    vector<string> F2;
    int a;
    //Trans(db,T,F1,F2,a);
    vector<string> DF,UF;
    Dwnsearch(db,DF,F2,a);
    Upsearch(T,UF,F2,a);
    cout<<"Minimum support = "<<min_sup<<"\n";
    cout<<"FREQUENT ITEMSETS ARE:-\n";
    for(int i=0;i<DF.size();i++){
        cout<<DF[i]<<"\n";
    }
    for(int i=0;i<UF.size();i++){
        cout<<UF[i]<<"\n";
    }
    
}