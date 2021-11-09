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
    //print(L,0);
    for(int i=0;i<L.size();i++){
        for(int j=i+1;j<L.size();j++){
            //cout<<L[i]<<L[j]<<" ";
            if(comPref(L[i],L[j])){
                string temp=L[i];
                string t="";
                //cout<<L[j]<<" ";
                int s=L[j].length()-1;
                //cout<<L[j][L[j].length()-1];
                while(L[j][s]!='I'){
                    t+=L[j][s];
                    s--;
                    //cout<<L[j][s]<<" ";
                    //cout<<t<<"\n";
                }
                t=t+'I';
                reverse(t.begin(),t.end());
                temp+=t;
                //cout<<temp<<" ";
                if(hasInfreq(L,temp))
                    ans.push_back(temp);
            }
        }
    }
    //print(ans,0);
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
    }
    //cout<<itm["I1"];
    //items vector has list of all candidate 1 itemsets
    cout<<"MINIMUM SUPPORT = 20%\n\n";
    cout<<"ITEMS SIZE="<<itm.size();
    min_sup=(itm.size()*2)/10;
    cout<<" MIN_SUP="<<min_sup<<"\n";
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
            //cout<<items[i]<<" :- "<<itm[items[i]]<<"\n";
        }
    }
    //print(t,0);
    L.push_back(t);
    sort(L[0].begin(),L[0].end());
    //print(L[0],1);
    for(int k=1;L[k-1].size()!=0;k++){
        C.push_back(gen(L[k-1],k));
        //print(C[1],5);
        vector<string> vec;
        for(int i=0;i<C[k].size();i++){
            //cout<<"hi";
            vector<string> temp;
            int cnt=0;
            string cur="I";
            int lm=1;
            while(lm<C[k][i].length()){
                
                if(C[k][i][lm]=='I'){
                    temp.push_back(cur);
                    //cout<<cur;
                    cur="I";
                }
                else{
                    cur=cur+C[k][i][lm];
                }
                lm++;
            }
            temp.push_back(cur);
            //print(temp,0);
            //cout<<temp[temp.size()-1]<<" ";
            for(auto it=tr.begin();it!=tr.end();it++){
                //print(it->second,1);
                //print(temp,2);
                if(check(it->second,temp)){
                    cnt++;
                }
            }
            //cout<<cnt<<" ";
            freq[C[k][i]]=cnt;
            if(cnt>=min_sup){
                //print(temp,cnt);
                cout<<"FREQUENT ITEMSET: ";
                cout<<C[k][i]<<" :- "<<cnt<<"\nASSOCIATION RULES:-\n";
                vector<set<string> > allsub;
                set<string> sub;
                getItemset(temp,0,allsub,sub);
                for(int g=1;g<allsub.size();g++){
                    string conv=get_conv(temp,allsub[g]);
                    string subset=get_str(allsub[g]);
                    if(conv.length()>0){
                        float confidence=float(cnt)/freq[subset];
                        if(confidence>=min_conf)
                            cout<<subset<<" => "<<conv<<"\t\t\t\tconfidence = "<<confidence<<"\n";
                    }
                    //cout<<conv<<" "<<subset<<"\n";
                }
                vec.push_back(C[k][i]);
            }
        }
        L.push_back(vec);
    }

    cout<<"\n\n---------------------------------------------\n\n";
    cout<<"\nMINIMUM SUPPORT = 30%\n\n";
    cout<<"ITEMS SIZE="<<itm.size();
    min_sup=(itm.size()*3)/10;
    cout<<" MIN_SUP="<<min_sup<<"\n";
    //float min_conf=0.5;
    cout<<"MIN_CONFIDENCE = "<<min_conf<<"\n\n";
    vector<vector<string> > L2;
    vector<vector<string> > C2;
    C2.push_back(items);
    vector<string> t2;
    for(int i=0;i<items.size();i++){
        //cout<<itm[items[i]];
        if(itm[items[i]]>=min_sup){
            t2.push_back(items[i]);
            //freq[items[i]]=itm[items[i]];
            //cout<<items[i]<<" :- "<<itm[items[i]]<<"\n";
        }
    }
    //print(t,0);
    L2.push_back(t);
    sort(L2[0].begin(),L2[0].end());
    //print(L[0],1);
    for(int k=1;L2[k-1].size()!=0;k++){
        C2.push_back(gen(L2[k-1],k));
        //print(C[1],5);
        vector<string> vec;
        for(int i=0;i<C2[k].size();i++){
            //cout<<"hi";
            vector<string> temp;
            int cnt=0;
            string cur="I";
            int lm=1;
            while(lm<C2[k][i].length()){
                
                if(C2[k][i][lm]=='I'){
                    temp.push_back(cur);
                    //cout<<cur;
                    cur="I";
                }
                else{
                    cur=cur+C2[k][i][lm];
                }
                lm++;
            }
            temp.push_back(cur);
            //print(temp,0);
            //cout<<temp[temp.size()-1]<<" ";
            for(auto it=tr.begin();it!=tr.end();it++){
                //print(it->second,1);
                //print(temp,2);
                if(check(it->second,temp)){
                    cnt++;
                }
            }
            //cout<<cnt<<" ";
            freq[C2[k][i]]=cnt;
            if(cnt>=min_sup){
                //print(temp,cnt);
                cout<<"FREQUENT ITEMSET: ";
                cout<<C2[k][i]<<" :- "<<cnt<<"\nASSOCIATION RULES:-\n";
                vector<set<string> > allsub;
                set<string> sub;
                getItemset(temp,0,allsub,sub);
                for(int g=1;g<allsub.size();g++){
                    string conv=get_conv(temp,allsub[g]);
                    string subset=get_str(allsub[g]);
                    if(conv.length()>0){
                        float confidence=float(cnt)/freq[subset];
                        if(confidence>=min_conf)
                            cout<<subset<<" => "<<conv<<"\t\t\t\tconfidence = "<<confidence<<"\n";
                    }
                    //cout<<conv<<" "<<subset<<"\n";
                }
                vec.push_back(C2[k][i]);
            }
        }
        L2.push_back(vec);
    }

    cout<<"\n\n---------------------------------------------\n\n";
    cout<<"\nMINIMUM SUPPORT = 50%\n\n";
    cout<<"ITEMS SIZE="<<itm.size();
    min_sup=(itm.size()*5)/10;
    cout<<" MIN_SUP="<<min_sup<<"\n";
    //float min_conf=0.5;
    cout<<"MIN_CONFIDENCE = "<<min_conf<<"\n\n";
    vector<vector<string> > L3;
    vector<vector<string> > C3;
    C3.push_back(items);
    vector<string> t3;
    for(int i=0;i<items.size();i++){
        //cout<<itm[items[i]];
        if(itm[items[i]]>=min_sup){
            t3.push_back(items[i]);
            //freq[items[i]]=itm[items[i]];
            //cout<<items[i]<<" :- "<<itm[items[i]]<<"\n";
        }
    }
    //print(t,0);
    L3.push_back(t);
    sort(L3[0].begin(),L3[0].end());
    //print(L[0],1);
    for(int k=1;L3[k-1].size()!=0;k++){
        C3.push_back(gen(L3[k-1],k));
        //print(C[1],5);
        vector<string> vec;
        for(int i=0;i<C3[k].size();i++){
            //cout<<"hi";
            vector<string> temp;
            int cnt=0;
            string cur="I";
            int lm=1;
            while(lm<C3[k][i].length()){
                
                if(C3[k][i][lm]=='I'){
                    temp.push_back(cur);
                    //cout<<cur;
                    cur="I";
                }
                else{
                    cur=cur+C3[k][i][lm];
                }
                lm++;
            }
            temp.push_back(cur);
            //print(temp,0);
            //cout<<temp[temp.size()-1]<<" ";
            for(auto it=tr.begin();it!=tr.end();it++){
                //print(it->second,1);
                //print(temp,2);
                if(check(it->second,temp)){
                    cnt++;
                }
            }
            //cout<<cnt<<" ";
            freq[C3[k][i]]=cnt;
            if(cnt>=min_sup){
                //print(temp,cnt);
                cout<<"FREQUENT ITEMSET: ";
                cout<<C3[k][i]<<" :- "<<cnt<<"\nASSOCIATION RULES:-\n";
                vector<set<string> > allsub;
                set<string> sub;
                getItemset(temp,0,allsub,sub);
                for(int g=1;g<allsub.size();g++){
                    string conv=get_conv(temp,allsub[g]);
                    string subset=get_str(allsub[g]);
                    if(conv.length()>0){
                        float confidence=float(cnt)/freq[subset];
                        if(confidence>=min_conf)
                            cout<<subset<<" => "<<conv<<"\t\t\t\tconfidence = "<<confidence<<"\n";
                    }
                    //cout<<conv<<" "<<subset<<"\n";
                }
                vec.push_back(C3[k][i]);
            }
        }
        L3.push_back(vec);
    }


    return 0;
}