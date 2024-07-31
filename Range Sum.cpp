// Mos algorithm

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
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
        q.push_back({{l,r},i});
    }
    
    // soring the queries
    sqrt_size=sqrt(n);
    sort(q.begin(),q.end(),cmp);
    
    vector<int> ans(qn);
    
    
    // Actual mos algorithm
    int cur_l = 0;
    int cur_r = 0;
    int sum=v[0];
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (auto& it:q) 
    {
        int l=it.first.first;
        int r=it.first.second;
        int queryNumber=it.second;
        
        while (cur_l < l) {
            sum-=v[cur_l];
            cur_l++;
        }
        
        while (cur_l > l) {
            cur_l--;
            sum+=v[cur_l];
        }
        
        while (cur_r <= r) {
            cur_r++;
            sum+=v[cur_r];
        }
        
        while (cur_r > r) {
            sum-=v[cur_r];
            cur_r--;
        }
        ans[queryNumber]=sum;
    }
    
    // Printing all answers for queries
    for(auto& it:ans)
    cout<<it<<" ";
    
	return 0;
}


/*
    5           - Size of an array
    1 2 3 4 5   - Elements of an array
    3           - Number of queries
    0 4         - Range l,r
    1 3
    3 4
*/


