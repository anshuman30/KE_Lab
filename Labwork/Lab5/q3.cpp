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
    string cur="I";
    int lm=1;
    while(lm<c.length()){
                
        if(c[lm]=='I'){
            t.push_back(cur);
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
    int sz=3;
    while(sz>=0 && getline(cin,dat)){
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
        sz--;
    }
    min_sup=(tran*5)/10;
    float min_conf=0.5;
    vector<vector<string> > L;
    vector<vector<string> > C;
    C.push_back(items);
    vector<string> t;
    for(int i=0;i<items.size();i++){
        if(itm[items[i]]>=min_sup){
            t.push_back(items[i]);
            freq[items[i]]=itm[items[i]];
        }
    }
    L.push_back(t);
    sort(L[0].begin(),L[0].end());
    for(int k=1;L[k-1].size()!=0;k++){
        C.push_back(gen(L[k-1],k));
        vector<string> vec;
        for(int i=0;i<C[k].size();i++){
            vector<string> temp;
            int cnt=0;
            string cur="I";
            int lm=1;
            while(lm<C[k][i].length()){
                
                if(C[k][i][lm]=='I'){
                    temp.push_back(cur);
                    cur="I";
                }
                else{
                    cur=cur+C[k][i][lm];
                }
                lm++;
            }
            temp.push_back(cur);
            auto part=tr.begin();
            part++;part++;
            for(auto it=tr.begin();it!=tr.end();it++){
                if(it==part){
                    if(check(it->second,temp)){
                        cnt++;
                    }
                    part++;part++;
                    continue;
                }
                if(check(it->second,temp)){
                    cnt++;
                }
            }
            freq[C[k][i]]=cnt;
            if(cnt>=min_sup){
                vec.push_back(C[k][i]);
            }
        }
        L.push_back(vec);
    }

    map<string,vector<string> > tr2;
    map<string,int> itm2;
    vector<string> items2;
    int cnt1=0;
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
            tr2[key].push_back(item);
            if(itm2.find(item)==itm2.end()){
                
                items2.push_back(item);
            }
            itm2[item]+=1;
            j++;
        }
        cnt1++;
    }
    int min_sup2=(cnt1*5)/10;
    int tot_min_sup = min_sup+min_sup2;
    
    vector<vector<string> > L2;
    vector<vector<string> > C2;
    map<string,int> freq2;
    C2.push_back(items2);
    vector<string> t2;
    for(int i=0;i<items2.size();i++){
        if(itm2[items2[i]]>=min_sup2){
            t2.push_back(items2[i]);
            freq2[items2[i]]=itm2[items2[i]];
        }
    }
    L2.push_back(t2);
    sort(L2[0].begin(),L2[0].end());
    for(int k=1;L2[k-1].size()!=0;k++){
        C2.push_back(gen(L2[k-1],k));
        vector<string> vec;
        for(int i=0;i<C2[k].size();i++){
            vector<string> temp;
            int cnt=0;
            string cur="I";
            int lm=1;
            while(lm<C2[k][i].length()){
                
                if(C2[k][i][lm]=='I'){
                    temp.push_back(cur);
                    cur="I";
                }
                else{
                    cur=cur+C2[k][i][lm];
                }
                lm++;
            }
            temp.push_back(cur);
            for(auto it=tr2.begin();it!=tr2.end();it++){
                if(check(it->second,temp)){
                    cnt++;
                }
            }
            freq2[C2[k][i]]=cnt;
            if(cnt>=min_sup2){
                
                vec.push_back(C2[k][i]);
            }
        }
        //print(vec,0);
        L2.push_back(vec);
    }
    map<string,int> frequent;
    cout<<"Transactions = "<<cnt1+tran<<"\n";
    cout<<"Mininum Support = 50%\nTherefore min_sup = "<<tot_min_sup<<"\n\n";
    for(int i=0;i<L.size();i++){
        for(int j=0;j<L[i].size();j++){
            //cout<<i<<j<<" ";
            if(freq[L[i][j]]+freq2[L[i][j]]>=tot_min_sup){
                cout<<"FREQUENT "<<i+1<<"-ITEMSET:- "<<L[i][j]<<"\n";
                frequent[L[i][j]]=1;
            }
            
        }//cout<<"\n";
    }for(int i=0;i<L2.size();i++){
        for(int j=0;j<L2[i].size();j++){
            if(freq[L2[i][j]]+freq2[L2[i][j]]>=tot_min_sup){
                if(frequent.find(L2[i][j])==frequent.end())
                    cout<<"FREQUENT "<<i+1<<"-ITEMSET:- "<<L2[i][j]<<"\n";
            }
        }
    }


    return 0;
}