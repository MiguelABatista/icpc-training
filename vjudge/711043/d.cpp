#include <iostream>
#include <vector>
using namespace std ;
typedef long long ll;
#define ln '\n'
#define forn( init ,  index ,  end) for(int index = init ; index < end ; index++)

struct Node {
	int start;
	int end;
	int mino;
	vector<int> v;
	Node* L;
	Node* R;
public: Node(int s, int e, vector<int>& vct) : v(vct) { this->start = s; this->end = e;L = nullptr;R = nullptr;  };
};

struct SegmentTree {
	Node* Root;

	Node* build(vector<int>& v , int s  , int e) {
    	Node* n = new Node(s, e, v);
    	if (s == e) { n->mino = v[s]; }
    	else {
        	int mid = (s + e) / 2;
        	n->L = build(v, s, mid);
        	n->R = build(v, mid+1, e);
        	n->mino = min(n->L->mino,n->R->mino);
    	}
    	return n;
	}
	void update(Node* n , int element , int value ) {
    	if (n->start == n->end && n->start == element) { n->mino = value; }
    	else {
        	int mid = (n->start + n->end) / 2;
        	if (element <= mid) {
            	update(n->L, element, value);
        	}
        	else { update(n->R, element, value); }
        	n->mino = min(n->R->mino,n->L->mino);
    	}
	}
	int query(Node* n,int l , int r ) {
    	if (l > n->end || r < n->start) { return 1e9 + 7; }
        else if (l<=n->start && r>=n->end){ return n->mino;}
        else{
            return min(query(n->L,l,r),query(n->R,l,r));
        }
    }
    public: SegmentTree(vector<int>& arr){
        this->Root = build(arr,0,arr.size()-1);
    }
    void act_update(int idx,int val){
        update(this->Root,idx,val);
    }
    int act_query(int s , int e){
        return query(this->Root,s,e);
    }

};
int main()
{
	int n, q;
	cin >> n >> q;
	vector<int> v(n, 0);
	vector<int> answers;
	forn(0, i, n) { cin >> v[i]; }
    SegmentTree seg(v);
	forn(0, i, q) { int op, a, b; cin >> op >> a >> b; 
    if (op==1){seg.act_update(a-1,b);}
    else{answers.push_back(seg.act_query(a-1,b-1));}
    }
    for(int i : answers){cout << i <<ln; }


}



