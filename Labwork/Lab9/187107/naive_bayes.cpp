#include<bits/stdc++.h>
using namespace std;

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

float prob(int class_name,vector<vector<int> > D){
    int tot=D[0].size();
    int fav=0;
    for(int i=0;i<D[0].size();i++){
        if(D[D.size()-1][i]==class_name){
            fav++;
        }
    }
    return (float)fav/tot;
}

float prob_given(int x,int attrib,int c,vector<vector<int> > D){
    int fav_widx=0;
    int fav=0;
    for(int i=0;i<D[0].size();i++){
        if(D[D.size()-1][i]==c){
            fav++;
        }
    }
    for(int i=0;i<D[0].size();i++){
        if(D[D.size()-1][i]==c && D[attrib][i]==x){
            fav_widx++;
        }
    }
    return (float)fav_widx/fav;
}

float prob_giv(vector<int> tup,int class_name,vector<vector<int> > D){
    float prod=1.000000;
    for(int i=0;i<tup.size();i++){
        prod*=prob_given(tup[i],i,class_name,D);
    }
    return prod;
}

int get_class(vector<vector<int> > D,vector<int> tup){
    vector<int> dist_classes;
    dist_classes=get_dist_vals(D[D.size()-1]);
    float max=-1.0;
    int ans;
    for(int i=0;i<dist_classes.size();i++){
        float temp = prob_giv(tup,dist_classes[i],D)*prob(dist_classes[i],D);
        if(temp>max){
            max=temp;
            ans = dist_classes[i];
        }
    }
    //cout<<max<<" : ";
    return ans;
}

int main()
{
    freopen("output.txt","w",stdout);
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
    vector<vector<int> > temp=D; 
    D = pivot(D);
    cout<<"Training data predictions:-\n";
    int total=temp.size();
    int correct2=0;
    for(int i=0;i<temp.size();i++){
        temp[i].pop_back();
        int cl = get_class(D,temp[i]);
        cout<<"Predicted value = "<<cl<<"\tActual Value = "<<D[D.size()-1][i]<<"\n";
        if(cl==D[D.size()-1][i]){
            correct2++;
        }
    }cout<<"\nTraining accuracy= "<<(float)correct2/total<<"\n";
    cout<<"\n___________________\n\n";

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
    cout<<"Test data predictions:-\n";
    int test_tot=0,correct=0;
    for(int i=0;i<test.size();i++){
        test[i].pop_back();
        int cl = get_class(D,test[i]);
        cout<<"Predicted value = "<<cl<<"\tActual value = "<<verify[i]<<"\n";
        test_tot++;
        if(cl==verify[i]){
            correct++;
        }
    }
    cout<<"\nTest accuracy= "<<(float)correct/test_tot<<"\n";
    cout<<"\n___________________\n\n";

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
    cout<<"Predictions data:\n";
    for(int i=0;i<pred.size();i++){
        //test[i].pop_back();
        cout<<"Predicted Value = "<<get_class(D,pred[i])<<"\n";
    }

    return 0;
}