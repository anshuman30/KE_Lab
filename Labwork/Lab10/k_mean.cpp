#include<bits/stdc++.h>
using namespace std;

int k = 3;

double dist(pair<int,int> p1,pair<int,int> p2){
    double sum = ((p1.first-p2.first)*(p1.first-p2.first))+((p1.second-p2.second)*(p1.second-p2.second));
    sum = sqrt(sum);
    return sum;
}

int min_dist(pair<int,int> pt,vector<pair<int,int> > centres){
    double min=999999999.000;
    int min_ind=0;
    for(int i=0;i<centres.size();i++){
        if(dist(pt,centres[i])<min){
            min=dist(pt,centres[i]);
            min_ind=i;
        }
    }
    return min_ind;
}
int lim=0;

bool change(vector<pair<int,int> > &centres,map<string,int> tags,map<string,pair<int,int> > pts){
    vector<pair<int,int> > temp(k);
    lim++;
    vector<int> xsum(k,0);
    vector<int> cnt(k,0);
    vector<int> ysum(k,0);
    for(auto it=tags.begin();it!=tags.end();it++){
        xsum[it->second]+=pts[it->first].first;
        ysum[it->second]+=pts[it->first].second;
        cnt[it->second]++;
    }
    for(int i=0;i<k;i++){
        temp[i]=make_pair(xsum[i]/cnt[i],ysum[i]/cnt[i]);
    }
    for(int i=0;i<k;i++){
        if(temp[i].first==centres[i].first && temp[i].second==centres[i].second){
            continue;
        }
        else{
            centres=temp;
            return true;
        }
    }
    return false;
    /*lim--;
    if(lim==0){
        return false;
    }
    
    return true;*/
}

void make_cluster(map<string,pair<int,int> > data_pts,map<string,int> &tags){
    srand((unsigned) time(0));
    vector<pair<int,int> > centres;
    for(int i=0;i<k;i++){
        int x1=rand()%10+1;
        int y1=rand()%10+1;
        centres.push_back(make_pair(x1,y1));
    }
    do{
        for(auto it=data_pts.begin();it!=data_pts.end();it++){
            int c = min_dist(it->second,centres);
            tags[it->first]=c;
        }
    }while(change(centres,tags,data_pts));

    for(int i=0;i<centres.size();i++){
        cout<<"Center for cluster "<<i<<" : ("<<(int)centres[i].first<<","<<(int)centres[i].second<<")\n";
    }

    cout<<"\nnumber of iterations: ";
    cout<<(int)lim<<"\n\n";
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output_for_kmeans.txt","w",stdout);
    string dat;
    map<string,pair<int,int> > data_pts;
    map<string,int> tags;
    while(getline(cin,dat)){
        string key="";
        int j=0;
        while(dat[j]!=' '){
            key+=dat[j];
            j++;
        }
        j++;
        string num="";
        int x,y;
        while(j<dat.length()){
            if(dat[j]==' '){
                stringstream s(num);
                s>>x;
                num="";
                j++;
                continue;
            }
            num+=dat[j];
            j++;
        }
        stringstream s2(num);
        s2>>y;
        pair<int,int> coord(x,y);
        data_pts[key]=coord;
    }
    //cout<<data_pts["A1"].first<<data_pts["A1"].second;
    cout<<"Number of clusters = "<<k<<"\n\n";
    make_cluster(data_pts,tags);
    for(auto it=tags.begin();it!=tags.end();it++){
        cout<<it->first<<" belongs to Cluster: "<<(int)it->second<<" point is: ("<<(int)data_pts[it->first].first<<","<<(int)data_pts[it->first].second<<")\n";
    }
    return 0;
}