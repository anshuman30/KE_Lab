#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("dataset.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string dat,foravg;
    int avg=70,sum=0,count=0;

    while(getline(cin,dat)){
        int i=0;
        while(dat[i]>='0'&&dat[i]<='9'){
            i++;
        }
        if(i+1==dat.length()){
            cout<<dat<<avg;
        }
        else{
            cout<<dat;
        }
        cout<<"\n";
    }
    return 0;
}