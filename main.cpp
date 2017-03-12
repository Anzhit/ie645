#include <bits/stdc++.h>

using namespace std;
void mprint(vector<vector<int>> vec);
class Node{
public:
	unsigned int serial; //serial no.
	int lb;  // lower bound
	vector<vector<int>> C; // reduced cost square matrix
	vector<pair<int,int>> in; // indexed list of in arcs
	vector<pair<int,int>> out; // indexed list of out arcs
    vector<vector<pair<int,int>>> chains; // indexed list of directed chains

    void print(){

    	cout<<"Serial Number: "<<serial<<endl;
    	cout<<"Lower Bound: "<<lb<<endl;
    	cout<<"Residual Matrix:\n";
    	mprint(C);
    	cout<<"In Arcs: ";
    	for(int i=0;i<in.size();i++)
    		cout<<'('<<in[i].first<<','<<in[i].second<<") ";
    	cout<<endl;
    	cout<<"Out Arcs: ";
    	for(int i=0;i<out.size();i++)
    		cout<<'('<<out[i].first<<','<<out[i].second<<") ";
    	cout<<endl;
    	cout<<"Directed Chains: \n";
    	for(int i=0;i<chains.size();i++){
    		cout<<"Chain "<<i<<" :";
    		for(int j=0;chains[i].size();j++)
    			cout<<'('<<chains[i][j].first<<','<<chains[i][j].second<<") ";
    		cout<<endl;
    	}
    	cout<<endl;
    }
};

int reduce(vector<vector<int>> &C){
	//reduce the cost matrix and return the obtained lower bound
	int ret=0;
	for(int i=0;i<C.size();i++){
		int t=*min_element(C[i].begin(),C[i].end());
		ret+=t;
		if(t>0)
			for(int j=0;j<C[i].size();j++)
				C[i][j]-=t;
	}
	for(int i=0;i<C.size();i++){
		int t=INT_MAX;
		for(int j=0;j<C.size();j++)
			if(t>C[j][i])
				t=C[j][i];
		ret+=t;
		if(t>0)
			for(int j=0;j<C.size();j++)
				C[j][i]-=t;
	}			

	return ret;
}
void mprint(vector<vector<int>> vec){ //print the matrix
	for (int i = 0; i < vec.size(); i++){
    	for (int j = 0; j < vec[i].size(); j++)
    	{
        	cout << vec[i][j] << " ";
    	}
    	cout<<endl;
    }
}

int main(){
list<Node> nodes; // list of sorted nodes (acc LB) to be explored

	vector<vector<int>> C={{1,2,3},{4,5,6},{7,8,9}};
	cout<<reduce(C)<<endl;
	mprint(C);
	return 0;
}