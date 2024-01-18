#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        vector<pair<int,int>> vec;
        vec.push_back({1,1});
        vec.push_back({a,1});vec.push_back({1,b});vec.push_back({a,b});
        
        for(int i=0;i<vec.size();i++){
            if(x==vec[i].first && y==vec[i].second){
                vec.erase(vec.begin()+i);
            }
        }
        int p=x;int q=y;
        
       


        
    }
    return 0;
}