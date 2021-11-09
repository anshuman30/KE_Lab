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
    map<string,int> freq;
    while(cin>>data){
        if(data==left){
            //stringstream sin(data);
            //srand((unsigned) time(0));
            string d;
            int count=0;
            int stop=rand()%4+1;
            while(cin>>d){
                if(d==right){
                    break;
                }
                if(count<stop && d.front()>='a' && d.front()<='z'){
                    freq[d]+=1;
                    count++;
                }
                else if(d.front()=='T'){
                    count=0;
                }
                
            }
            break;
        }
    }
    for(auto it=freq.begin();it!=freq.end();it++){
        cout<<it->first<<" "<<it->second<<"\n";
    }
    cout<<left<<" "<<right;
    return 0;
}