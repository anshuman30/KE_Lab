#include<bits/stdc++.h>
using namespace std;

int min_sup=5;
fstream fin;
ofstream fout;
string dat;

map<string,int> freq;

struct fp_tree{
    string item;
    int cnt;
    vector<struct fp_tree *> children;
};
typedef struct fp_tree * FTPTR;

bool comp(string a,string b){
    if(freq[a]==freq[b]){
        return b.compare(a);
    }
    return freq[a]>freq[b];
}

void add_to_tree(FTPTR &T,vector<string> items,int i){
    if(i>=items.size()){
        return;
    }
    int flg=0;
    for(int j=0;j<T->children.size();j++){
        if(items[i].compare(T->children[j]->item)==0){
            flg=1;
            T->children[j]->cnt++;
            //cout<<T->children[j]->item<<" : "<<T->children[j]->cnt<<"\n";
            add_to_tree(T->children[j],items,i+1);
            break;
        }
    }
    if(flg==0){
        FTPTR temp = NULL;
        temp=new struct fp_tree;
        temp->item=items[i];
        temp->cnt=1;
        //temp->next=NULL;
        T->children.push_back(temp);
        add_to_tree(T->children[T->children.size()-1],items,i+1);
    }
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

void populate(FTPTR T,map<string,vector<FTPTR> > &items){
    items[T->item].push_back(T);
    for(int i=0;i<T->children.size();i++){
        populate(T->children[i],items);
    }
}


void print_tree(FTPTR T){
    cout<<T->item<<" : "<<T->cnt<<"\n";
    for(int i=0;i<T->children.size();i++){
        print_tree(T->children[i]);
    }
}


vector<string> refer;

vector<string> dfs_path(FTPTR root,FTPTR dest,vector<string> &cur){
    vector<string> ans;
    if(root==dest){
        return cur;
    }
    else{
        cur.push_back(root->item);
        for(int i=0;i<root->children.size();i++){
            vector<string> temp = dfs_path(root->children[i],dest,cur);
            if(temp!=refer){
                return temp;
            }
        }
        cur.pop_back();
    }
    return refer;
}

void print_vec(vector<string> tem){
    for(int i=0;i<tem.size();i++){
        cout<<tem[i]<<" ";
    }
}

vector<pair<vector<string>,int> > get_pcb(FTPTR T,vector<FTPTR> items){
    vector<pair<vector<string>,int> > ans;
    for(int i=0;i<items.size();i++){
        pair<vector<string>,int> t;
        vector<string> temp,cur;
        temp=dfs_path(T,items[i],cur);
        t=make_pair(temp,items[i]->cnt);
        ans.push_back(t);
    }
    return ans;
}

void print_lev(FTPTR root){
    queue<struct fp_tree * > q;
    FTPTR ref =NULL;
    ref = new struct fp_tree;
    ref->item="ref";
    ref->cnt=0;
    
    q.push(root);
    q.push(ref);
    fout<<"Level order representation of the fp-tree:\n";
    while(q.size()>1){
        //cout<<q.size();
        FTPTR t=q.front();
        q.pop();
        if(t->item==ref->item){
            fout<<"\n";
            q.push(ref);
            continue;
        }
        fout<<t->item<<":"<<t->cnt<<" ";
        for(int j=0;j<t->children.size();j++){
            q.push(t->children[j]);
        }
    }
}

void remove_blank(vector<string> &vec){
    vector<string>::iterator it=vec.begin();
    for(int i=0;i<vec.size();i++,it++){
        if(vec[i].compare("{}")==0){
            vec.erase(it);
        }
    }
}

void set_freq(FTPTR T,map<string,int> &frq,vector<string> &temp){
    for(int i=0;i<T->children.size();i++){
        if(frq.find(T->children[i]->item)==frq.end()){
            temp.push_back(T->children[i]->item);
        }
        frq[T->children[i]->item]+=T->children[i]->cnt;
        set_freq(T->children[i],frq,temp);
    }
}

int get_min(set<string> s,map<string,int> frq){
    int ans=INT_MAX;
    for(auto it=s.begin();it!=s.end();it++){
        ans=min(ans,frq[*it]);
    }
    return ans;
}

int main()
{
    
    fin.open("input.txt");
    fout.open("output.txt");
    map<string,vector<FTPTR> > items;
    fout<<"min_sup = 2\n";
    fout<<"\n____________________________________________________\n\n";

    //scan 1 to find frequent itemsets
    while(getline(fin,dat)){
        int i=0;
        while(dat[i]!=' '){
            i++;
        }
        i++;
        string cur="";
        while(i<dat.length()){
            if(dat[i]==' '){
                freq[cur]++;
                cur="";
                i++;
                continue;
            }
            cur+=dat[i];
            i++;
        }
        freq[cur]++;
    }
    fout<<"count of all items after 1 scan:\n";
    for(auto it=freq.begin();it!=freq.end();it++){
        fout<<it->first<<" :- "<<it->second<<"\n";
        if(freq[it->first]>=min_sup){
            vector<FTPTR> temp;
            items[it->first]=temp;
        }
    }
    fout<<"\n___________________________________________________\n\n";

    FTPTR root = NULL;
    root = new struct fp_tree;
    root->item="{}";
    root->cnt=0;

    fstream fin2;
    fin2.open("input.txt");
    fout<<"sorted itemsets transaction wise:\n";

    //scan 2 to construct the fp-tree
    while(getline(fin2,dat)){
        int i=0;
        while(dat[i]!=' '){
            i++;
        }
        i++;
        vector<string> items;
        string cur="";
        while(i<dat.length()){
            if(dat[i]==' '){
                items.push_back(cur);
                cur="";
                i++;
                continue;
            }
            cur+=dat[i];
            i++;
        }
        items.push_back(cur);
        sort(items.begin(),items.end(),comp);

        add_to_tree(root,items,0);

        for(int j=0;j<items.size();j++){
            fout<<items[j]<<" ";
        }
        fout<<"\n";
    }
    for(int k=0;k<root->children.size();k++){
        populate(root->children[k],items);
    }
    fout<<"\n___________________________________________________\n\n";

    //fp_growth(root,items,"5");

    print_lev(root);
    fout<<"\n___________________________________________________\n\n\n";
    fout<<"\nCONDITIONAL FP-TREES AND THEIR CORRESPONDING FREQUENT ITEMSETS ARE SHOWN BELOW:-\n\n";

    for(auto it=items.begin();it!=items.end();it++){
        vector<pair<vector<string>,int> > pcb;
        pcb = get_pcb(root,it->second);
        //print_vec(pcb[0].first);
        //cout<<pcb[1].second;
        FTPTR T_new =NULL;
        T_new = new struct fp_tree;
        T_new->cnt=0;
        T_new->item="{}";
        for(int i=0;i<pcb.size();i++){
            for(int j=0;j<pcb[i].second;j++){
                remove_blank(pcb[i].first);
                sort(pcb[i].first.begin(),pcb[i].first.end(),comp);
                add_to_tree(T_new,pcb[i].first,0);
            }
        }
        //cout<<"END\n";
        fout<<"Item: "<<it->first<<"\n";
        print_lev(T_new);
        fout<<"\nFREQUENT ITEMSETS FROM THE ABOVE TREE:-\n";
        map<string,int> frequency;
        vector<string> tempo;
        set_freq(T_new,frequency,tempo);
        //cout<<frequency["3"]<<"Bro\n";
        vector<set<string> > cur;
        set<string> pres;

        getItemset(tempo,0,cur,pres);
        for(int j=1;j<cur.size();j++){
            int occ = get_min(cur[j],frequency);
            //cout<<occ<<"\n";
            if(occ<min_sup){
                continue;
            }
            for(auto it2=cur[j].begin();it2!=cur[j].end();it2++){
                fout<<*it2<<" ";
            }
            
            fout<<it->first<<" : "<<occ<<"\n";
        }
        fout<<"\n_________________________________________________________\n";

    }

    return 0;
}