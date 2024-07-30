#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    
    // Number of Elements
	int n;
	cin>>n;
	
	// Elements of an array
	vector<int> v(n);
	for(auto& it:v)
	cin>>it;
	
	int sqrt_size=sqrt(n);
	vector<int> block(sqrt_size+1,0);
	
	for(int i=0;i<n;i++)
	block[i/sqrt_size]+=v[i];
	
	// Number of queries
	int q;
	cin>>q;
	
	while(q--)
	{
	    // Type of a query 1 or 2
	    int type;
	    cin>>type;
	    
	    // Point update
	    if(type==1)
	    {
	        int index,value;
	        cin>>index>>value;
	        
	        block[index/sqrt_size]+=value;
	        v[index]+=value;
	    }
	    else if(type==2)
	    {
	        int l,r;
	        cin>>l>>r;
	        
	        int sum=0;
	        int i=l;
	        while(i<=r)
	        {
	            if((i%sqrt_size)==0 and (i+sqrt_size-1)<=r)
	            {
	                sum+=block[i/sqrt_size];
	                i+=sqrt_size;
	            }
	            else
	            {
	                sum+=v[i];
	                i++;
	            }
	        }
	        cout<<"sum -> "<<sum<<endl;
	    }
	}
	
	return 0;
}


/*
    5           - Size of an array
    1 2 3 4 5   - Elements of an array
    3           - Number of queries
    2           - type of a query ( type = 2 Range sum)
    0 4         - Range l , r
    1           - Type of a query ( type = 1 Point update)
    1 4         - Index and value
    2
    0 3
*/

