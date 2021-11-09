#include<bits/stdc++.h>
using namespace std;
void print(vector<string> ,int );

int min_sup;

vector<int> decToBinary(int n) 
{ 
    vector<int> binaryNum; 
  
    //int i = 0; 
    while (n > 0) { 
  
        binaryNum.push_back(n % 2); 
        n = n / 2;  
    } 
  
    return binaryNum;
} 

int binToDec(vector<int> bin){
    int res=0;
    int power=1;
    for(int i=bin.size();i>=0;i--){
        res=res+bin[i]*power;
        power*=2;
    }
    return res;
}

vector<int> quick_cand_gener(vector<int> bl){
    vector<int> bc;
    for(int i=0;i<bl.size();i++){
        int temp=bl[i];
        vector<int> binary = decToBinary(temp);
        for(int j=binary.size();j>=0;j--){
            if(binary[j]==1){
                binary[j]=0;
                break;
            }
        }
        int mid = binToDec(binary);
        for(int j=i+1;j<bl.size();j++){
            if(mid&bl[j]==mid){
                bc.push_back(bl[i]|bl[j]);
            }
        }
    }
    return bc;
}

vector<int> quick_supp_count(vector<int> bc,vector<int> db){
    vector<int> bl;
    for(int i=0;i<bc.size();i++){
        vector<int> bin = decToBinary(bc[i]);
        int res=db[0];
        for(int j=1;j<bin.size();j++){
            if(bin[j]==1){
                res=res&db[j];
            }
        }
        vector<int> bin2=decToBinary(res);
        int c=0;
        for(int j=0;j<bin2.size();j++){
            c+=bin2[j];
        }
        if(c>=min_sup){
            bl.push_back(bc[i]);
        }
    }
    return bl;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string dat;
    map<string,int> itm;
    vector<string> items;
    map<string,int> freq;
    vector<vector<int> > DB;
    while(getline(cin,dat)){
        vector<int> tup;
        string key="";
        int j=0;
        while(j<dat.length()){
            if(dat[j]!=' '){
                if(dat[j]=='1'){
                    tup.push_back(1);
                }
                else{
                    tup.push_back(0);
                }
            }
        }
        DB.push_back(tup);

    }

    min_sup=2;
    cout<<" MIN_SUP="<<min_sup<<"\n";
    float min_conf=0.5;
    vector<int> bl;
    vector<int> bc;
    vector<int> db;
    for(int i=0;i<DB[0].size();i++){
        vector<int> bin;
        for(int j=0;j<DB.size();j++){
            bin.push_back(DB[j][i]);
        }
        db.push_back(binToDec(bin));
    }

    return 0;
}