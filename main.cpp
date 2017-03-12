#include <bits/stdc++.h>

using namespace std;
void mprint(vector<vector<double>> vec);
double reduce(vector<vector<double>> &C);
int num=0;
class Node{
public:
	unsigned int serial=0; //serial no.
	double lb=0;  // lower bound
	vector<vector<double>> C; // reduced cost square matrix
	vector<pair<int,int>> in; // indexed list of in arcs
	vector<pair<int,int>> out; // indexed list of out arcs
    vector<list<int>> chains; // indexed list of directed chains
    double theta(int I,int J){
    	double ret=0;
    	double min =DBL_MAX;
    	for(int i=1;i<C.size();i++)
    		if(min>C[I][i]&&i!=J)
    			min=C[I][i];
    	ret=min;
    	min =DBL_MAX;
    	for(int i=1;i<C.size();i++)
    		if(min>C[i][J]&&i!=I)
    			min=C[i][J];
    	return ret+min;
    }
    pair<int,int> branchOn(){
    	double max=DBL_MIN;
    	pair<int,int> ret;
    	for(int i=1;i<C.size();i++)
    		for(int j=1;j<C.size();j++)
    			if(C[i][j]==0&&theta(i,j)>max){
    				max=theta(i,j);
    				ret=make_pair(C[i][0],C[0][j]);
    			}
    	return ret;
    }
    Node branch1(int I,int  J){ // branch with arc (I,J)
        Node r = *this;
        int l=C.size(),m=C.size();
    	for(int i=0;i<C.size();i++)
    		if(C[i][0]==I)
    			l=i;
    	for(int i=0;i<C.size();i++)
    		if(C[0][i]==J)
    			m=i;
    	for(int i=0;i<r.C.size();i++) {
    		r.C[i].erase(r.C[i].begin()+m); // remove column 
    	}
    	r.C.erase(r.C.begin()+l); // remove row
    	r.in.push_back(make_pair(I,J));
    	//add to chain/s
    	int front=C.size(),back=C.size();
    	for(int i=0;i<r.chains.size();i++){
    		if(r.chains[i].back()==I){
    			r.chains[i].push_back(J);
    			back=i;
    		}
    		if(r.chains[i].front()==J){
    			r.chains[i].push_front(I);
    			front=i;
    		}
    		
    	}
    	//try and connect chains
    	if(front==C.size()&&back==C.size()){
    		list<int> t; t.push_back(I);t.push_back(J);
    		r.chains.push_back(t);
    		r.invalidate(J,I);
    	}
    	else if(front<C.size()&&back<C.size()){
    		//connect front, back
    		r.chains[front].pop_front();
    		r.chains[back].pop_back();
    		r.chains[back].splice(r.chains[back].end(),r.chains[front]);
    		//invalidate edges
    		r.invalidChain(r.chains[back]);
    		r.chains.erase(r.chains.begin()+front);

    	}
    	else if(front<C.size()){
    		r.invalidChain(r.chains[front]);

    	}
    	else if(back<C.size()){
    		r.invalidChain(r.chains[back]);

    	}
    	r.serial=++num;
    	r.lb+=reduce(r.C);
    	return r;
    }
    Node branch2(int I,int  J){ //branch w/o arc (I,J)
    	Node r = *this;
    	r.invalidate(J,I);
    	r.lb+=reduce(r.C);
    	r.out.push_back(make_pair(I,J));
    	r.serial=++num;
    	return r;
    }
    void invalidate(int I,int J){//invalidate arc I, J i.e find element corersponding to it in matrice and set to INF
    	int l=C.size(),m=C.size();
    	for(int i=0;i<C.size();i++)
    		if(C[i][0]==I)
    			l=i;
    	for(int i=0;i<C.size();i++)
    		if(C[0][i]==J)
    			m=i;
    	if(l<C.size()&&m<C.size())
    		C[l][m]=DBL_MAX;
    }
    void invalidChain(list<int> c){
    	for ( list<int>::const_iterator i = c.end() ; i != c.begin() ; ){
    		--i;
    	for ( list<int>::const_iterator j = c.begin() ; j != i ; ++j )
    		invalidate(*i,*j);    		
		}	
    }
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
    		cout<<"Chain "<<i+1<<" : ";
    		for ( list<int>::const_iterator j = chains[i].begin() ; j != chains[i].end() ; ++j )
    			cout<<*j<<"->";
    		cout<<endl;
    	}
    	cout<<endl;
    }
    bool operator<(const Node& y) { return lb < y.lb; }
};
double reduce(vector<vector<double>> &C){
	//reduce the cost matrix and return the obtained lower bound
	double ret=0;
	for(int i=1;i<C.size();i++){
		double t=*min_element(C[i].begin()+1,C[i].end());
		ret+=t;
		if(t>0)
			for(int j=1;j<C[i].size();j++)
				C[i][j]-=t;
	}
	for(int i=1;i<C.size();i++){
		double t=DBL_MAX;
		for(int j=1;j<C.size();j++)
			if(t>C[j][i])
				t=C[j][i];
		ret+=t;
		if(t>0)
			for(int j=1;j<C.size();j++)
				C[j][i]-=t;
	}			

	return ret;
}
void mprint(vector<vector<double>> vec){ //print the matrix
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
	int n;
	//Take Input and create init node
	cin>>n;
	Node init;
	init.C.resize(n+1);
	for(int i=0;i<=n;i++){
		init.C[i].resize(n+1);
		init.C[i][0]=i;
		init.C[0][i]=i;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cin>>init.C[i+1][j+1];
	}
	init.lb=reduce(init.C);
	nodes.push_back(init);
	init.print();
	while(true){
		Node cur=nodes.front();
				nodes.pop_front();
		cout<<"Expanding Node: "<<cur.serial<<endl;
		pair<int,int> arc=cur.branchOn();
		cout<<"Branching on Arc: ("<<arc.first<<","<<arc.second<<")\n";
		Node X=cur.branch1(arc.first,arc.second);
		X.print();
		Node Xbar=cur.branch2(arc.first,arc.second);
		Xbar.print();
		if(isfinite(X.lb))
			nodes.push_back(X);
		if(isfinite(Xbar.lb))
			nodes.push_back(Xbar);
		nodes.sort();
	}

	return 0;
}