#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt","w",stdout);
    srand((unsigned) time(0));
    int num_trans=rand()%10+1;
    for(int i=1;i<=num_trans;i++){
        cout<<"T"<<i<<" ";
        int num_items=rand()%6+1;
        for(int j=1;j<=num_items;j++){
            int item=rand()%10+1;
            cout<<item<<" ";
        }
        cout<<"\n";
    }
}