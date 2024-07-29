// Problem Link - https://codeforces.com/contest/52/problem/C
#include <iostream>
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

#define ll long long
vector<ll> process(string str){
	string curr = "";
	vector<ll> vec;
	for(int i=0;i<str.size();i++){
		if(str[i]==' '){
			vec.push_back(stoi(curr));
			curr = "";
		}
		else curr+=str[i];
	}
	vec.push_back(stoi(curr));
	return vec;
}

void buildSeg(vector<ll>& v,ll* seg,ll ind,ll low,ll high)
{
    //base case
    if(low==high)
    {
        seg[ind]=v[low];
        return ;
    }
    
    //recursive calls
    //and small calculation
    ll mid=(low+high)/2;
    buildSeg(v,seg,ind*2+1,low,mid);
    buildSeg(v,seg,ind*2+2,mid+1,high);
    
    seg[ind]=min(seg[ind*2+1],seg[ind*2+2]);
}

void updateSeg(ll* seg,ll* lazy,ll ind,ll low,ll high,ll l,ll r,ll val)
{
    //remaining part
    if(lazy[ind]!=0)
    {
        seg[ind]+=lazy[ind];
        if(low!=high)
        {
            lazy[ind*2+1]+=lazy[ind];
            lazy[ind*2+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    
    //complete overlap
    if(low>=l and high<=r)
    {
        // cout<<"ind -> "<<ind<<endl;
        // cout<<seg[ind]<<endl;
        seg[ind]+=val;
        if(low!=high)
        {
            lazy[ind*2+1]+=val;
            lazy[ind*2+2]+=val;
        }
        // cout<<"ind2 -> "<<ind<<endl;
        // cout<<seg[ind]<<endl;
        return ;
    }
    
    //no overlap
    if(high<l or low>r)
    return ;
    
    //partial overlapping
    ll mid=(low+high)/2;
    updateSeg(seg,lazy,ind*2+1,low,mid,l,r,val);
    updateSeg(seg,lazy,ind*2+2,mid+1,high,l,r,val);
    
    seg[ind]=min(seg[ind*2+1],seg[ind*2+2]);
}

ll searchInRange(ll* seg,ll* lazy,ll ind,ll low,ll high,ll l,ll r)
{
    //remaining part
    if(lazy[ind]!=0)
    {
        seg[ind]+=lazy[ind];
        if(low!=high)
        {
            lazy[ind*2+1]+=lazy[ind];
            lazy[ind*2+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    
    //complete overlap
    if(low>=l and high<=r)
    return seg[ind];
    
    //no overlap
    if(high<l or low>r)
    return 1e16;
    
    //partial overlapping
    ll mid=(low+high)/2;
    ll left=searchInRange(seg,lazy,ind*2+1,low,mid,l,r);
    ll right=searchInRange(seg,lazy,ind*2+2,mid+1,high,l,r);
    
    return min(left,right);
}
int main() {
	int n;
	cin>>n;
	
	vector<ll> v(n);
	for(auto& it:v)
	cin>>it;
	
	ll seg[4*n];
	ll lazy[4*n]={0};
	
	buildSeg(v,seg,0,0,n-1);
	
	ll q; 
	cin>>q; 
	string str; 
	getline(cin, str);
	
	for(int i=0;i<q;i++)
	{
		string str; 
		getline(cin, str);		
		vector<ll> nums = process(str);

		if((nums.size())==3){ //q1, increment
			if(nums[0]<=nums[1]){
				updateSeg(seg,lazy,0,0,n-1,nums[0],nums[1],nums[2]);
			}
			else{
				updateSeg(seg,lazy,0,0,n-1,0,nums[1],nums[2]);
				updateSeg(seg,lazy,0,0,n-1,nums[0],n-1,nums[2]);
			}
		}
		else{ //q2, rmq
			if(nums[0]<=nums[1]){
				cout<<searchInRange(seg,lazy,0,0,n-1,nums[0],nums[1])<<endl;
			}
			else{
				cout<<min(searchInRange(seg,lazy,0,0,n-1,0,nums[1]),searchInRange(seg,lazy,0,0,n-1,nums[0],n-1))<<endl;
			}
		}
	}
// 	updateSeg(seg,lazy,0,0,n-1,3,4,5);
// 	cout<<searchInRange(seg,lazy,0,0,n-1,3,4)<<endl;
	
// 	updateSeg(seg,lazy,0,0,n-1,0,2,2);
// 	cout<<searchInRange(seg,lazy,0,0,n-1,0,4)<<endl;
	
	return 0;
}

// update -1 -> 1 2 0 9 10 
 
