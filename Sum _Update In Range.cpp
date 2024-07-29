/*------------  Lazy Propagation Segment Tree ----------*/
#include <vector>
#include <iostream>
using namespace std;

// bulding segment tree
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
    
    seg[ind]=seg[ind*2+1]+seg[ind*2+2];
}

int searchInRange(int ind,int low,int high,int l,int r,vector<int>& seg,vector<int>& lazy)
{
    // if update is pending
    if(lazy[ind])
    {
        seg[ind]=lazy[ind]*(high-low+1);
        if(low!=high)
        {
            lazy[ind*2+1]+=lazy[ind];
            lazy[ind*2+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    
    // No overlapping
    if(high<l or low>r)
    return 0;
    
    // Complete overlapping
    if(low>=l and high<=r)
    return seg[ind];
    
    // Partial overlapping
    int mid=(low+high)/2;
    int left=searchInRange(ind*2+1,low,mid,l,r,seg,lazy);
    int right=searchInRange(ind*2+2,mid+1,high,l,r,seg,lazy);
    
    return (left+right);
}


// update in range
void updateInRange(int ind,int low,int high,int l,int r,int& value,vector<int>& seg,vector<int>& lazy)
{
    // if update is pending
    if(lazy[ind])
    {
        seg[ind]=lazy[ind]*(high-low+1);
        if(low!=high)
        {
            lazy[ind*2+1]+=lazy[ind];
            lazy[ind*2+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    
    // No overlapping
    if(high<l or low>r)
    return ;
    
    // Complete overlapping
    if(low>=l and high<=r)
    {
        seg[ind]=value*(high-low+1);
        if(low!=high)
        {
            lazy[ind*2+1]+=value;
            lazy[ind*2+2]+=value;
        }
        return ;
    }
    
    // Partial overlapping
    int mid=(low+high)/2;
    updateInRange(ind*2+1,low,mid,l,r,value,seg,lazy);
    updateInRange(ind*2+2,mid+1,high,l,r,value,seg,lazy);
    
    seg[ind]=seg[ind*2+1]+seg[ind*2+2];
}



int main() {
	int n;
	cin>>n;
	vector<int> v(n);
	for(auto& it:v)
	cin>>it;
	
	vector<int> seg(n*4,0);
	vector<int> lazy(n*4,0);
	buildSegment(0,0,n-1,v,seg);
	
	// Number of queries
	int q;
	cin>>q;
	while(q--)
	{
	    int type;
	    cin>>type;
	    
	    // search in range
	    if(type==1)
	    {
	        int l,r;
	        cin>>l>>r;
	        cout<<searchInRange(0,0,n-1,l,r,seg,lazy)<<endl;
	    }
	    else // update in range
	    {
	        int l,r,value;
	        cin>>l>>r>>value;
	        updateInRange(0,0,n-1,l,r,value,seg,lazy);
	    }
	}
	return 0;
}


/*

    5.          - Number of elements in an array
    1 2 3 4 5   - Elements of an array
    3           - Number of queries
    1           - type of querie (type - 1, means search in range)
    0 4         - Range (l,r)
    2           - type of querie (type - 2, means update in range)
    1 3 1       - l,r,value
    1
    0 4

*/


