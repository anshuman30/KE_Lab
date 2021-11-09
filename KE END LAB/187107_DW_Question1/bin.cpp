#include<bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int t;
        cin>>t;
        arr.push_back(t);
    }
    int num_bins=4;
    int mini=INT_MAX,maxi=INT_MIN;
    for(int i=0;i<arr.size();i++){
        if(mini>arr[i]){
            mini=arr[i];
        }
        if(maxi<arr[i]){
            maxi=arr[i];
        }
    }
    int bin_width = (maxi-mini)/num_bins;
    vector<vector<int> > bins(num_bins,vector<int>());
    for(int i=0;i<arr.size();i++){
        if(arr[i]>mini && arr[i]<mini+(bin_width)){
            bins[0].push_back(arr[i]);
        }
        if(arr[i]>mini+(bin_width) && arr[i]<mini+2*(bin_width)){
            bins[1].push_back(arr[i]);
        }
        if(arr[i]>mini+2*(bin_width) && arr[i]<mini+3*(bin_width)){
            bins[2].push_back(arr[i]);
        }
        if(arr[i]>mini+3*(bin_width) && arr[i]<maxi){
            bins[3].push_back(arr[i]);
        }
    }
    for(int i=0;i<num_bins;i++){
        sort(bins[i].begin(),bins[i].end());
        for(int j=0;j<bins[i].size();j++){
            if(bins[i][j]-bins[i][0]>bins[i][j]-bins[i][bins.size()-1]){
                bins[i][j]=bins[i][bins.size()-1];
            }
            else{
                bins[i][j]=bins[i][0];
            }
        }
    }
    for(int i=0;i<bins[1].size();i++){
        cout<<bins[1][i]<<" ";
    }
    cout<<endl;
    return 0;
}