#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node{
    public:
    int full;
    int close;
    int open;
    Node()
    {
        this->full=0;
        this->close=0;
        this->open=0;
    }
};

void buildSegment(int ind,int low,int high,string& s,vector<Node>& seg)
{
    //base case
    if(low==high)
    {
        Node temp;
        if(s[low]=='(')
        temp.open++;
        else
        temp.close++;
        
        seg[ind]=temp;
        return ;
    }
    
    //recursive calls
    //and small calculation
    int mid=(low+high)/2;
    buildSegment(ind*2+1,low,mid,s,seg);
    buildSegment(ind*2+2,mid+1,high,s,seg);
    
    Node ans;
    ans.full=seg[ind*2+1].full+seg[ind*2+2].full+min(seg[ind*2+1].open,seg[ind*2+2].close);
    ans.open=seg[ind*2+1].open+seg[ind*2+2].open-min(seg[ind*2+1].open,seg[ind*2+2].close);
    ans.close=seg[ind*2+1].close+seg[ind*2+2].close-min(seg[ind*2+1].open,seg[ind*2+2].close);
    seg[ind]=ans;
}

Node rangeSearching(int ind,int low,int high,int l,int r,vector<Node>& seg)
{
    //no overlapping
    if(r<low or l>high)
    {
        Node temp;
        return temp;
    }
    
    //complete overlapping
    if(low>=l and high<=r)
    return seg[ind];
    
    //partial overlapping
    int mid=(low+high)/2;
    Node left=rangeSearching(ind*2+1,low,mid,l,r,seg);
    Node right=rangeSearching(ind*2+2,mid+1,high,l,r,seg);
    
    Node ans;
    ans.full=left.full+right.full+min(left.open,right.close);
    ans.open=left.open+right.open-min(left.open,right.close);
    ans.close=left.close+right.close-min(left.open,right.close);
    return ans;
}

int main() {
	string s;
	cin>>s;
	
	int n=s.length();
	int q;
	cin>>q;
	
	vector<Node> seg(4*n);
	buildSegment(0,0,n-1,s,seg);

	while(q--)
	{
	    int l,r;
	    cin>>l>>r;
	    l--,r--;
	    
	    cout<<(rangeSearching(0,0,n-1,l,r,seg).full)*2<<endl;
	}
	return 0;
}
