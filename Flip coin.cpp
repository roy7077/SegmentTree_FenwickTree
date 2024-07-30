#include <iostream>
#include <vector>
using namespace std;

// Build segment tree
void buildSegment(int ind,int low,int high,vector<int>& v,vector<int>& seg)
{
    // base case
    if(low==high)
    {
        seg[ind]=v[low];
        return ;
    }
    
    // recursive calls
    // and small calculation
    int mid=(low+high)/2;
    buildSegment(ind*2+1,low,mid,v,seg);
    buildSegment(ind*2+2,mid+1,high,v,seg);
    
    seg[ind]=seg[ind*2+1]+seg[ind*2+2];
}


// Search in range
int searchInRange(int ind,int low,int high,int l,int r,vector<int>& seg,vector<int>& lazy)
{
    // if pending in lazy
    if(lazy[ind])
    {
        int totalCoins=(high-low+1);
        int newHead=totalCoins-seg[ind];
        seg[ind]=newHead;
        
        if(low!=high)
        {
            lazy[ind*2+1]=(!lazy[ind*2+1]);
            lazy[ind*2+2]=(!lazy[ind*2+2]);
        }
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

// Update in range
void updateInRange(int ind,int low,int high,int l,int r,vector<int>& seg,vector<int>& lazy)
{
    // if pending in lazy
    if(lazy[ind])
    {
        int totalCoins=(high-low+1);
        int newHead=totalCoins-seg[ind];
        seg[ind]=newHead;
        
        if(low!=high)
        {
            lazy[ind*2+1]=(!lazy[ind*2+1]);
            lazy[ind*2+2]=(!lazy[ind*2+2]);
        }
    }
    
    // No overlapping
    if(high<l or low>r)
    return ;
    
    // Complete overlapping
    if(low>=l and high<=r)
    {
        int totalCoins=(high-low+1);
        int newHead=totalCoins-seg[ind];
        seg[ind]=newHead;
        
        if(low!=high)
        {
            lazy[ind*2+1]=(!lazy[ind*2+1]);
            lazy[ind*2+2]=(!lazy[ind*2+2]);
        }
        return ;
    }
    
    // Partial overlapping
    int mid=(low+high)/2;
    updateInRange(ind*2+1,low,mid,l,r,seg,lazy);
    updateInRange(ind*2+2,mid+1,high,l,r,seg,lazy);
    
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
	
	int q;
	cin>>q;
	while(q--)
	{
	    int type;
	    cin>>type;
	    if(type)
	    {
	        int l,r;
	        cin>>l>>r;
	        cout<<searchInRange(0,0,n-1,l,r,seg,lazy)<<endl;
	    }
	    else
	    {
	        int l,r;
	        cin>>l>>r;
	        updateInRange(0,0,n-1,l,r,seg,lazy);
	    }
	}
	return 0;
}

/*

    5.            - Number of elements in an array
    1 1 0 1 1     - Elements of an array
    3             - Number of quries
    1             - Type of query (type = 1 Search In Range)
    0 4           - Range , l , r
    0             - Type of query (type = 0 update In Range)
    0 3           - Range , l , r
    1
    0 4

*/












