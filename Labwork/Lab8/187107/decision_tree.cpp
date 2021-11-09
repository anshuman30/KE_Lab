#include<bits/stdc++.h>
using namespace std;

struct dtnode{
    int attrib;
    int attrib_vals;
    bool is_leaf;
    int class_name;
    vector<struct dtnode *> children;
};

typedef struct dtnode * DTPTR;

ofstream fout;

void print_vec(vector<int> v){
    for(int i=0;i<v.size();i++){
        fout<<v[i]<<" ";
    }
    fout<<"\n";
}

bool check_all_same_class(vector<int> classes){
    //cout<<"Man"<<"\n";
    for(int i=0;i<classes.size();i++){
        if(classes[i]!=classes[0]){
            return false;
        }
    }
    return true;
}

int most_common(vector<int> classes){
    map<int,int> freq;
    int max=INT_MIN,max_class;
    for(int i=0;i<classes.size();i++){
        freq[classes[i]]++;
        if(max<freq[classes[i]]){
            max=freq[classes[i]];
            max_class=classes[i];
        }
    }
    return max_class;
}

set<int>::iterator get_iterator(set<int> attrib_set,int attrib){
    set<int>::iterator t;
    for(auto it=attrib_set.begin();it!=attrib_set.end();it++){
        if(*it==attrib){
            return it;
        }
    }
    return t;
}

vector<int> get_dist_vals(vector<int> attrib_val){
    map<int,int> pres;
    vector<int> ans;
    for(int i=0;i<attrib_val.size();i++){
        if(pres.find(attrib_val[i])==pres.end()){
            ans.push_back(attrib_val[i]);
            pres[attrib_val[i]]=1;
        }
    }
    return ans;
}

vector<vector<int> > pivot(vector<vector<int> > D){
    vector<vector<int> > ans;
    for(int i=0;i<D[0].size();i++){
        vector<int> tuple;
        for(int j=0;j<D.size();j++){
            tuple.push_back(D[j][i]);
        }
        ans.push_back(tuple);
    }
    return ans;
}

vector<vector<int> > get_part(vector<vector<int> > D,int best_attrib,int attrib_val){
    vector<vector<int> > ans;
    for(int i=0;i<D[0].size();i++){
        vector<int> tuple;
        for(int j=0;j<D.size();j++){
            tuple.push_back(D[j][i]);
        }
        if(tuple[best_attrib]==attrib_val){
            ans.push_back(tuple);
        }
    }
    ans = pivot(ans);
    return ans;
}

int get_counts(vector<int> v,int x){
    int c=0;
    for(int i=0;i<v.size();i++){
        if(v[i]==x){
            c++;
        }
    }
    return c;
}

int get_counts2(vector<int> v,int x,vector<int> v2,int x2){
    int c=0;
    for(int i=0;i<v.size();i++){
        if(v[i]==x && v2[i]==x2){
            c++;
        }
    }
    return c;
}

double info(vector<vector<int> > D,int attr){
    double sum=0;
    vector<int> dist_vals = get_dist_vals(D[attr]);
    for(int i=0;i<dist_vals.size();i++){
        int c = get_counts(D[attr],dist_vals[i]);
        int nos = get_counts2(D[attr],dist_vals[i],D[D.size()-1],1);
        int yes = get_counts2(D[attr],dist_vals[i],D[D.size()-1],2);
        if(c==0 || nos==0 ||yes==0){
            continue;
        }
        sum-=(nos*(log(nos)-log(c)));
        sum-=(yes*(log(yes)-log(c)));
    }
    return sum;
}

int get_best(vector<vector<int> > D,set<int> attrib_set){
    set<int>::iterator it=attrib_set.begin();
    double min=99999999.0;
    int min_atr;
    //cout<<info(D,*it)<<"\n";
    for(it;it!=attrib_set.end();it++){
        if(info(D,*it)<min){
            min = info(D,*it);
            min_atr=*it;
        }
        //cout<<info(D,*it)<<"\n";
    }
    return min_atr;
}

DTPTR make_tree(vector<vector<int> > D,set<int> attrib_set){
    //cout<<"Hi\n";
    DTPTR N=NULL;
    N=new struct dtnode;
    N->is_leaf=false;
    //print_vec(D[D.size()-1]);
    //check_all_same_class(D[D.size()-1]);
    if(check_all_same_class(D[D.size()-1])){
        //cout<<"Yo\n";
        N->is_leaf=true;
        N->class_name=D[D.size()-1][0];
        return N;
    }
    if(attrib_set.empty()){
        N->is_leaf=true;
        N->class_name=most_common(D[D.size()-1]);
        return N;
    }
    int best_attrib = get_best(D,attrib_set);
    fout<<best_attrib<<"\n";
    //cout<<*get_iterator(attrib_set,best_attrib)<<"\n";
    attrib_set.erase(get_iterator(attrib_set,best_attrib));
    //cout<<"HI\n";
    //int it1 = attrib_set.size();
    //cout<<it1<<"\n";
    vector<int> distinct_values = get_dist_vals(D[best_attrib]);
    for(int i=0;i<distinct_values.size();i++){
        vector<vector<int> > Di = get_part(D,best_attrib,distinct_values[i]);
        //print_vec(Di[Di.size()-1]);
        if(Di[0].size()==0){
            N->is_leaf=true;
            N->class_name=most_common(D[D.size()-1]);
            return N;
        }
        N->attrib = best_attrib;
        //N->attrib_vals = distinct_values[i];
        N->children.push_back(make_tree(Di,attrib_set));
    }
    for(int i=0;i<N->children.size();i++){
        N->children[i]->attrib_vals=distinct_values[i];
    }
    return N;
}

int test_classes(vector<int> test,DTPTR root){
    if(root->is_leaf==true){
        return root->class_name;
    }
    else{
        for(int i=0;i<root->children.size();i++){
            if(test[root->attrib]==root->children[i]->attrib_vals){
                return test_classes(test,root->children[i]);
            }
        }
        return -1;
    }
}

int main()
{
    fout.open("output.txt");
    fstream fin;
    fin.open("input.txt");
    string dat;
    vector<vector<int> > D;
    set<int> attrib_set;
    while(getline(fin,dat)){
        //cout<<dat<<"\n";
        vector<int> tuple;
        string n="";
        int j=0;
        int col=0;
        while(j<dat.length()){
            if(dat[j]==' '){
                stringstream stream(n);
                //cout<<n<<" ";
                int num =10;
                stream>>num;
                tuple.push_back(num);
                n="";
                attrib_set.insert(col);
                col++;
                j+=3;
                continue;
            }
            n+=dat[j];
            j++;
        }
        stringstream stream(n);
        int num =0;
        stream>>num;
        tuple.push_back(num);
        //attrib_set.insert(col);
        col++;
        D.push_back(tuple);
    }
    //print_vec(D[0]);
    fout<<"All tuples of the database along with class labels as the last column value:-\n";
    for(int i=0;i<D.size();i++){
        print_vec(D[i]);
    }
    fout<<"__________________________________________________\n\n";
    vector<vector<int> > temp=D; 
    D = pivot(D);
    DTPTR root=make_tree(D,attrib_set);
    fstream fin2;
    fin2.open("test.txt");
    vector<vector<int> > test;
    vector<int> verify;
    while(getline(fin2,dat)){
        //cout<<dat<<"\n";
        vector<int> tuple;
        string n="";
        int j=0;
        int col=0;
        while(j<dat.length()){
            if(dat[j]==' '){
                stringstream stream(n);
                //cout<<n<<" ";
                int num =10;
                stream>>num;
                tuple.push_back(num);
                n="";
                //attrib_set.insert(col);
                //col++;
                j+=3;
                continue;
            }
            n+=dat[j];
            j++;
        }
        stringstream stream(n);
        int num =0;
        stream>>num;
        tuple.push_back(num);
        verify.push_back(num);
        //attrib_set.insert(col);
        col++;
        test.push_back(tuple);
    }
    fout<<"Test data results\n";
    int test_tot=0,correct=0;
    for(int i=0;i<test.size();i++){
        fout<<"Predicted class: "<<test_classes(test[i],root)<<"\tActual class: "<<verify[i]<<"\n";
        test_tot++;
        if(test_classes(test[i],root)==verify[i]){
            correct++;
        }
    }
    fout<<"Test accuracy=\t"<<(float)correct/test_tot<<"\n\n";
    fout<<"Training data results\n";
    int train_tot=0,cor=0;
    for(int i=0;i<temp.size();i++){
        fout<<"Predicted class: "<<test_classes(temp[i],root)<<"\tActual class: "<<temp[i][temp[i].size()-1]<<"\n";
        train_tot++;
        if(test_classes(temp[i],root)==temp[i][temp[i].size()-1]){
            cor++;
        }
    }fout<<"Training accuracy=\t"<<(float)cor/train_tot<<"\n\n";
    fstream fin3;
    fin3.open("pred.txt");
    vector<vector<int> > pred;
    while(getline(fin3,dat)){
        //cout<<dat<<"\n";
        vector<int> tuple;
        string n="";
        int j=0;
        int col=0;
        while(j<dat.length()){
            if(dat[j]==' '){
                stringstream stream(n);
                //cout<<n<<" ";
                int num =10;
                stream>>num;
                tuple.push_back(num);
                n="";
                //attrib_set.insert(col);
                //col++;
                j+=3;
                continue;
            }
            n+=dat[j];
            j++;
        }
        stringstream stream(n);
        int num =0;
        stream>>num;
        tuple.push_back(num);
        //attrib_set.insert(col);
        col++;
        pred.push_back(tuple);
    }
    fout<<"Prediction results\n";
    for(int i=0;i<pred.size();i++){
        fout<<test_classes(pred[i],root)<<"\n";
    }
    //test = pivot(test);
    return 0;
}