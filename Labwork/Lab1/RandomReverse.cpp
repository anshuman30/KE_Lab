#include<bits/stdc++.h>
using namespace std;
int main()
{
    srand((unsigned) time(0));
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int ref1=rand()%6+1;
    int ref2=rand()%6+1;
    int l=min(ref1,ref2);
    int r=max(ref1,ref2);
    ostringstream stream;
    string left="T",right="T";
    stream<<l;
    left+=stream.str();
    ostringstream stream2;
    stream2<<r;
    right+=(stream2.str());
    string data;
    map<string,vector<string>> rev;
    while(cin>>data){
        if(data==left){
            srand((unsigned) time(0));
            string d;
            int count=0;
            int stop=rand()%4+1;
            string transac=left;
            while(cin>>d){
                if(d==right){
                    break;
                }
                if(count<stop && d.front()>='a' && d.front()<='z'){
                    rev[d].push_back(transac);
                    count++;
                }
                else if(d.front()=='T'){
                    transac=d;
                    count=0;
                }
                
            }
            break;
        }
    }

    for(auto it=rev.begin();it!=rev.end();it++){
        cout<<it->first<<" ";
        for(int i=0;i<it->second.size();i++){
            cout<<it->second[i]<<" ";
        }
        cout<<"\n";
    }
    cout<<left<<" "<<right;
    return 0; 
}