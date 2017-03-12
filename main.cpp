#include <bits/stdc++.h>

using namespace std;

class Node{
public:
	unsigned int serial; //serial no.
	int lb;  // lower bound
	vector<vector<int>> C; // reduced cost square matrux
	list<pair<int,int>> in; // list of in arcs
	list<pair<int,int>> out; // list of out arcs
    list<list<pair<int,int>>> chains; // list of directed chains
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
void print(vector<vector<int>> vec){ //print the matrix
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
	print(C);
	return 0;
}