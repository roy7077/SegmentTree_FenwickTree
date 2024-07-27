#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// building segment
bool buildSegment(int ind,int low,int high,vector<int>& seg,vector<int>& v)
{
    //base case
    if(low==high)
    {
        seg[ind]=v[low];
        return 1;
    }
    
    //recursive calls
    //and small calculation
    int mid=(low+high)/2;
    bool left=buildSegment(ind*2,low,mid,seg,v);
    bool right=buildSegment(ind*2+1,mid+1,high,seg,v);
    
    if(left and right)
    {
        seg[ind]=seg[ind*2] | seg[ind*2+1];
        return 0;
    }
    else
    {
        seg[ind]=seg[ind*2] ^ seg[ind*2+1];
        return 1;
    }
}

// Point update
bool pointUpdate(int ind,int low,int high,int& index,int& value,vector<int>& seg,vector<int>& v)
{
    //base case
    if(low==high and low==index)
    {
        seg[ind]=value;
        //v[low]=value;
        return 1;
    }
    
    //recursive calls
    //and small calculation
    int mid=(low+high)/2;
    if(index<=mid)
    {
        bool a=pointUpdate(ind*2,low,mid,index,value,seg,v);
        if(a)
        {
            seg[ind]=seg[ind*2] | seg[ind*2+1];
            return 0;
        }
        else
        {
            seg[ind]=seg[ind*2] ^ seg[ind*2+1];
            return 1;
        }
    }
    else
    {
        bool a=pointUpdate(ind*2+1,mid+1,high,index,value,seg,v);
        if(a)
        {
            seg[ind]=seg[ind*2] | seg[ind*2+1];
            return 0;
        }
        else
        {
            seg[ind]=seg[ind*2] ^ seg[ind*2+1];
            return 1;
        }
    }
}


int main(){
    int n,m;
    cin>>n>>m;
    
    vector<int> v(pow(2,n)+1);
    for(int i=1;i<=pow(2,n);i++)
    cin>>v[i];
    
    // for(int i=1;i<=7;i++)
    // cout<<v[i]<<endl;
    
    vector<int> seg(pow(2,n)*4+1);
    buildSegment(1,1,pow(2,n),seg,v);
    
    // for(int i=1;i<=7;i++)
    // cout<<"ind -> "<<i<<" seg -> "<<seg[i]<<endl;
    
    while(m--)
    {
        int index,value;
        cin>>index>>value;
        
        pointUpdate(1,1,pow(2,n),index,value,seg,v);
        cout<<seg[1]<<endl;
    }
    return 0;
}

