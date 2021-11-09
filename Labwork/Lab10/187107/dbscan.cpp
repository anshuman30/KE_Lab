#include<bits/stdc++.h>
using namespace std;

int min_pts=2;
int e=3;

void print_pts(vector<pair<string,pair<int,int> > > points,int c){
    for(int i=0;i<points.size();i++){
        cout<<"Object name: "<<points[i].first<<" : "<<c<<" ("<<points[i].second.first<<","<<points[i].second.second<<")\n";
    }
}

double dist(pair<int,int> p1,pair<int,int> p2){
    double sum = ((p1.first-p2.first)*(p1.first-p2.first))+((p1.second-p2.second)*(p1.second-p2.second));
    sum = sqrt(sum);
    return sum;
}

bool unvis(map<string,int> vis){
    for(auto it=vis.begin();it!=vis.end();it++){
        if(it->second==0){
            return true;
        }
    }
    return false;
}

bool not_there(vector<pair<string,pair<int,int> > > points,string pt){
    for(int i=0;i<points.size();i++){
        if(points[i].first.compare(pt)==0){
            return false;
        }
    }
    return true;
}

bool nbhd(pair<int,int> pt,int e,int min_pts,vector<pair<string,pair<int,int> > > &points,map<string,pair<int,int> > data){
    int cnt=0;
    vector<pair<string,pair<int,int> > > temp; 
    for(auto it=data.begin();it!=data.end();it++){
        if(false){
            continue;
        }
        else{
            if(dist(pt,it->second)<=(double)e){
                cnt++;
                temp.push_back(make_pair(it->first,make_pair(it->second.first,it->second.second)));
            }
        }
    }
    if(cnt>=min_pts){
        //points=temp;
        for(int i=0;i<temp.size();i++){
            if(not_there(points,temp[i].first))
                points.push_back(make_pair(temp[i].first,make_pair(temp[i].second.first,temp[i].second.second)));
        }
        return true;
    }
    return false;
}

void make_clusters(map<string,pair<int,int> > pts,map<string,int> &tags,map<string,int> &vis){
    int c=0;
    int noise=INT_MAX;
    do{
        pair<int,int> p;
        string pt_name;
        for(auto it=pts.begin();it!=pts.end();it++){
            if(vis[it->first]==0){
                vis[it->first]=1;
                p.first=it->second.first;
                p.second=it->second.second;
                pt_name=it->first;
                break;
            }
        }
        //vis[pt_name]=1;
        vector<pair<string,pair<int,int> > > points;
        if(nbhd(p,e,min_pts,points,pts)){
            tags[pt_name]=c;
            //print_pts(points,999);
            for(int i=0;i<points.size();i++){
                //cout<<points[i].first<<"\n";
                if(vis[points[i].first]==0){
                    //cout<<it->first<<" ";
                    vis[points[i].first]=1;
                    nbhd(points[i].second,e,min_pts,points,pts);

                }
                //print_pts(points,990);
                //the_end=points.end();
                //cout<<"Noice mf\n";
                if(tags.find(points[i].first)==tags.end()){
                    tags[points[i].first]=c;
                }
            }
            print_pts(points,c);
            c++;
        }
        else{
            tags[pt_name]=noise;
            cout<<"Object name: "<<pt_name<<" : *noise* "<<" ("<<p.first<<","<<p.second<<")\n";
        }
        //cout<<pt_name<<"\n";
        //cout<<"NICE\n";
    }while(unvis(vis));
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output_for_dbscan.txt","w",stdout);
    string dat;
    map<string,pair<int,int> > data_pts;
    map<string,int> tags;
    map<string,int> vis;
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
        vis[key]=0;
    }
    //cout<<data_pts["A1"].first<<data_pts["A1"].second;
    cout<<"Radius for each point (e): "<<e<<" Minimum no of points (min_pts): "<<min_pts<<"\n\n";
    make_clusters(data_pts,tags,vis);
    /*for(auto it=tags.begin();it!=tags.end();it++){
        cout<<it->first<<" "<<it->second<<" point is: ("<<data_pts[it->first].first<<")\n";
    }*/
    return 0;
}