// Problem link - https://www.spoj.com/problems/DQUERY/

// Mos algorithm

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;


int sqrt_size;
bool cmp(pair<pair<int,int>,int>& a,pair<pair<int,int>,int>& b)
{
    int block1=a.second/sqrt_size;
    int block2=b.second/sqrt_size;
    
    if(block1<block2)
    return true;
    
    if(block1==block2)
    {
        if(a.first.second<=b.first.second)
        return true;
    }
    
    return false;
}


int main() {
    
    // n -> length of an array
    int n;
    cin>>n;
    
    // Elements of an array
    vector<int> v(n);
    for(auto& it:v)
    cin>>it;
    
    // Taking query input and storing it with query number
    vector<pair<pair<int,int>,int>> q;
    int qn;
    cin>>qn;
    
    for(int i=0;i<qn;i++)
    {
        int l,r;
        cin>>l>>r;
        l--,r--;
        q.push_back({{l,r},i});
    }
    
    // soring the queries
    sqrt_size=sqrt(n);
    sort(q.begin(),q.end(),cmp);
    
    vector<int> ans(qn);
    
    
    // Actual mos algorithm
    unordered_map<int,int> mp;
    int cur_l = 0;
    int cur_r = 0;
    int distinct=1;
    mp[v[0]]++;
    
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (auto& it:q) 
    {
        int l=it.first.first;
        int r=it.first.second;
        int queryNumber=it.second;
        
        while (cur_l < l) {
            mp[v[cur_l]]--;
    
            if(mp[v[cur_l]]==0)
            distinct--;
            
            cur_l++;
        }
        
        while (cur_l > l) {
            cur_l--;
            
            mp[v[cur_l]]++;
            if(mp[v[cur_l]]==1)
            distinct++;
        }
        
        while (cur_r <= r) {
            cur_r++;
            
            mp[v[cur_r]]++;
            if(mp[v[cur_r]]==1)
            distinct++;
            
        }
        
        while (cur_r > r) {
            mp[v[cur_r]]--;
            if(mp[v[cur_r]]==0)
            distinct--;
            
            cur_r--;
        }
        ans[queryNumber]=distinct;
    }
    
    // Printing all answers for queries
    for(auto& it:ans)
    cout<<it<<endl;
    
	return 0;
}


