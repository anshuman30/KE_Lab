#include<bits/stdc++.h>
using namespace std;
int main()
{
    srand((unsigned) time(0));
    freopen("input.txt","w",stdout);
    int lim=rand()&10+1;
    for(int i=1;i<=lim;i++){
        //srand((unsigned) time(0));
        cout<<"T"<<i<<" ";
        int numOfItems=rand()%10+1;
        for(int j=1;j<=numOfItems;j++){
            //srand((unsigned) time(0));
            int dat=rand()%25;
            char item = 'a' + dat;
            cout<<item<<" ";
        }
        cout<<"\n";
    }
    return 0;
}