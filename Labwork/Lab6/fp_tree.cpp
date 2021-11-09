#include<bits/stdc++.h>
using namespace std;

int min_sup=2;

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
    if(freq[items[i]]<min_sup){
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

int main()
{
    fstream fin;
    ofstream fout;
    string dat;
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
    fout<<"\n___________________________________________________\n\n";

    fout<<"Populated tree traversals for each item:\n";
    for(auto it=items.begin();it!=items.end();it++){
        fout<<it->first<<" ==> ";
        for(int j=0;j<it->second.size();j++){
            fout<<it->second[j]->item<<":"<<it->second[j]->cnt<<", ";
        }
        fout<<"\n";
    }

    return 0;
}