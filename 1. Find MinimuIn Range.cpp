#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// build segment tree
void buildSegment(int ind,int low,int high,vector<int>& v,vector<int>& seg)
{
    //base case
    if(low==high)
    {
        seg[ind]=v[low];
        return ;
    }
    
    //recursive calls
    //and small calculation
    int mid=(low+high)/2;
    buildSegment(ind*2+1,low,mid,v,seg);
    buildSegment(ind*2+2,mid+1,high,v,seg);
    seg[ind]=min(seg[ind*2+1],seg[ind*2+2]);
}



// search in range
int searchInRange(int ind,int low,int high,int s,int e,vector<int>& seg)
{
    //No overlap
    if(e<low or s>high)
    return 1e9;
    
    //Complete overlap
    if(low>=s and high<=e)
    return seg[ind];
    
    //partiall overlap
    int mid=(low+high)/2;
    int left=searchInRange(ind*2+1,low,mid,s,e,seg);
    int right=searchInRange(ind*2+2,mid+1,high,s,e,seg);
    return min(left,right);
    
}


// point update
void pointUpdate(int ind,int low,int high,int index,int value,vector<int>& seg)
{
    //base case
    if(low==high and low==index)
    {
        seg[ind]=value;
        return ;
    }
    
    //recursive call
    //small calculation
    int mid=(low+high)/2;
    if(index<=mid)
    pointUpdate(ind*2+1,low,mid,index,value,seg);
    else
    pointUpdate(ind*2+2,mid+1,high,index,value,seg);
    
    seg[ind]=min(seg[ind*2+1],seg[ind*2+2]);
}


int main(){
    int n;
    cin>>n;
    
    vector<int> v(n);
    for(auto& it:v)
    cin>>it;
    
    vector<int> seg(n*4);
    buildSegment(0,0,n-1,v,seg);
    
    int q;
    cin>>q;
    while(q--)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            int s,e;
            cin>>s>>e;
            
            cout<<searchInRange(0,0,n-1,s,e,seg)<<endl;
        }
        else
        {
            int index,value;
            cin>>index>>value;
            
            pointUpdate(0,0,n-1,index,value,seg);
        }
    }
    return 0;
}

/*
    Sample test case
    ________________
    
    5            - Number of element in an array
    1 2 3 4 5    - Elements of an array
    3            - Number of queries
    1            - Type = 1 Means search in range
    0 4          - Range in which searching to be done
    2            - Type = 2 Means Point Update
    2 -1         - Index and value
    1
    0 4
    2
    3 -2
    1
    0 4
*/

