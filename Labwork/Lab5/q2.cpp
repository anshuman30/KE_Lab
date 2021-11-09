#include<bits/stdc++.h>
using namespace std;
void print(vector<string> ,int );

bool comPref(string a,string b){
    int ea=a.length()-1;
    int eb=b.length()-1;
    while(a[ea]!='I'){
        ea--;
    }
    while(b[eb]!='I'){
        eb--;
    }
    if(a.substr(0,ea).compare(b.substr(0,eb))==0){
        return true;
    }
    return false;
}

bool isInfreq(vector<string> L,vector<string> t,int i){
    string item="";
    for(int j=0;j<t.size();j++){
        if(j!=i){
            item+=t[j];
        }
    }
    for(int j=0;j<L.size();j++){
        if(L[j].compare(item)==0){
            return false;
        }
    }
    return true;
}

bool hasInfreq(vector<string> L,string c){
    vector<string> t;
    //int cnt=0;
    string cur="I";
    int lm=1;
    while(lm<c.length()){
                
        if(c[lm]=='I'){
            t.push_back(cur);
            //cout<<cur;
            cur="I";
        }
        else{
            cur=cur+c[lm];
        }
        lm++;
    }
    t.push_back(cur);
    for(int i=0;i<t.size();i++){
        if(isInfreq(L,t,i)){
            return false;
        }
    }
    return true;
}

vector<string> gen(vector<string> L,int k){
    vector<string> ans;
    for(int i=0;i<L.size();i++){
        for(int j=i+1;j<L.size();j++){
            if(comPref(L[i],L[j])){
                string temp=L[i];
                string t="";
                int s=L[j].length()-1;
                while(L[j][s]!='I'){
                    t+=L[j][s];
                    s--;
                }
                t=t+'I';
                reverse(t.begin(),t.end());
                temp+=t;
                if(hasInfreq(L,temp))
                    ans.push_back(temp);
            }
        }
    }
    return ans;
}

void getItemset(vector<string> items,int i,vector<set<string> > &cur,set<string> pres){
    if(i==items.size()){
        cur.push_back(pres);
    }
    else{
        getItemset(items,i+1,cur,pres);
        pres.insert(items[i]);
        getItemset(items,i+1,cur,pres);
    }
}

void print(vector<string> s,int c){
    for(int i=0;i<s.size();i++){
        cout<<s[i]<<" ";
    }
    cout<<c<<"\n";
}

void getItemset_k(vector<string> items,int i,vector<set<string> > &cur,set<string> pres,int k){
    if(i==items.size()){
        if(pres.size()==k)
            cur.push_back(pres);
    }
    else{
        getItemset_k(items,i+1,cur,pres,k);
        pres.insert(items[i]);
        getItemset_k(items,i+1,cur,pres,k);
    }
}

bool check(vector<string> a,vector<string> b){
    for(int i=0;i<b.size();i++){
        int f=0;
        for(int j=0;j<a.size();j++){
            if(a[j].compare(b[i])==0){
                f=1;
                break;
            }
        }
        if(f==0){
            return false;
        }
    }
    return true;
}

bool comp(string a,string b){
    return a.compare(b)<0;
}

string get_conv(vector<string> all,set<string> subset){
    string ans="";
    for(int i=0;i<all.size();i++){
        if(subset.find(all[i])==subset.end()){
            ans+=all[i];
        }
    }
    return ans;
}

string get_str(set<string> subset){
    string ans="";
    for(auto it=subset.begin();it!=subset.end();it++){
        ans=ans+*it;
    }
    return ans;
}

string get_str_except_k(set<string> subset,int k){
    string ans="";
    int i=0;
    for(auto it=subset.begin();it!=subset.end();it++,i++){
        if(i!=k)
            ans=ans+*it;
    }
    return ans;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    map<string,vector<string> > tr;
    string dat;
    map<string,int> itm;
    vector<string> items;
    int min_sup;
    map<string,int> freq;
    int tran=0;
    while(getline(cin,dat)){
        string key="";
        int j=0;
        while(dat[j]!=' '){
            key+=dat[j];
            j++;
        }
        j++;
        while(j<dat.length()){
            string item="I";
            while(j<dat.length() && dat[j]!=' '){
                item+=dat[j];
                j++;
            }
            tr[key].push_back(item);
            if(itm.find(item)==itm.end()){
                
                items.push_back(item);
            }
            itm[item]+=1;
            j++;
        }
        tran++;
    }
    cout<<"MINIMUM SUPPORT = 50%\n\n";
    cout<<"ITEMS SIZE="<<itm.size()<<" TRANSACTIONS SIZE = "<<tran<<"\n";
    min_sup=(tran*5)/10;
    cout<<"MIN_SUP="<<min_sup<<"\n";
    float min_conf=0.5;
    cout<<"MIN_CONFIDENCE = "<<min_conf<<"\n\n";
    vector<vector<string> > L;
    vector<vector<string> > C;
    C.push_back(items);
    vector<string> t;
    for(int i=0;i<items.size();i++){
        //cout<<itm[items[i]];
        if(itm[items[i]]>=min_sup){
            t.push_back(items[i]);
            freq[items[i]]=itm[items[i]];
        }
    }
    L.push_back(t);
    sort(L[0].begin(),L[0].end());
    set<string> sq;
    set<string> cir;
    for(int i=0;i<items.size();i++){
        cir.insert(items[i]);
    }
   
    int sz=2;
    //min_sup=1;
    int limit=1000;
    while(limit>0 && !cir.empty()){
        //for(int i=0;i<L[0].size();i++){
        map<string,int> counter;
        for(auto it=tr.begin();it!=tr.end();it++){
            for(auto it2=cir.begin();it2!=cir.end();it2++){
                vector<string> temp;
                //int cnt=0;
                string cur="I";
                int lm=1;
                while(lm<(*it2).length()){
                    
                    if((*it2)[lm]=='I'){
                        temp.push_back(cur);
                        //cout<<cur;
                        cur="I";
                    }
                    else{
                        cur=cur+(*it2)[lm];
                    }
                    lm++;
                }
                temp.push_back(cur);
                if(check(it->second,temp)){
                    counter[(*it2)]++;
                }
            }
                
        }
        for(auto it=counter.begin();it!=counter.end();it++){
            if(it->second>=min_sup){
                sq.insert(it->first);
                auto it2=cir.find(it->first);
                cir.erase(it2);
            }
        }
        vector<set<string> > cur;
        set<string> pres;
        getItemset_k(items,0,cur,pres,sz);
        for(int i=0;i<cur.size();i++){
            int flg=0;
            for(int k=0;k<cur[i].size();k++){
                string str = get_str_except_k(cur[i],k);
                if(sq.find(str)==sq.end()){
                    flg=1;
                    break;
                }
            }
            if(flg==0){
                cir.insert(get_str(cur[i]));
            }
        }
        sz++;
        limit--;
        //cout<<cir.size()<<"\n";
        //}
    }
    cout<<"FREQUENT ITEMSETS ARE:- \n\n";
    for(auto it=sq.begin();it!=sq.end();it++){
        cout<<"  "<<*it<<"\n";
    }
    cout<<"\n--------------------------------------------------";

    return 0;
}