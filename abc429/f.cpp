#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Segment Tree (Range Query + Point Update)
//
// Balanced binary tree for range queries with a customizable combine; supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    vector<v64> mat = {{-1, INF, INF}, {INF,-1 , INF}, {INF, INF, -1}};
    
    node(){}
    node(const vector<v64> mat_){mat = mat_;}
    node(const vector<char> c){
        forn(i,0,3){
            mat[i][i] = (c[i] == '#' ? INF : 0);
        }
        mat[0][1] = mat[1][0] = ((c[0] != '#' && c[1] != '#') ? 1 : INF);
        mat[0][2] = mat[2][0] = ((c[0] != '#' && c[1] != '#' && c[2] != '#') ? 2 : INF);
        mat[1][2] = mat[2][1] = ((c[1] != '#' && c[2] != '#') ? 1 : INF);
    }
    
    static node comb(const node& a, const node& b) {
        vector<v64> newmat(3, v64(3,INF));

        forn(i,0,3){
            forn(j,0,3){
                forn(k,0,3){
                    newmat[i][j] = min(newmat[i][j], a.mat[i][k]+ b.mat[k][j]+1);
                }
            }
        }
        return node(newmat);
    }
    void print(){
        forn(i,0,3){
            forn(j,0,3){
                if(mat[i][j] == INF) cout << "## ";
                else cout << setw(2) << mat[i][j] << " ";    
            }
            cout << ln;
        }
        cout << ln;
    }
};

const node neutral = node((vector<v64>){{-1ll, INF, INF}, {INF,-1ll , INF}, {INF, INF, -1ll}});

struct tree {
    ll lm, rm;
    unique_ptr<tree> lc, rc;
    
    node val;

    tree(ll l_, ll r_, const vector<node>& v) : lm(l_), rm(r_) {
        if (lm == rm) {
            val = v[lm];
        } else {
            ll m = (lm + rm) / 2;
            lc = make_unique<tree>(lm, m, v);
            rc = make_unique<tree>(m + 1, rm, v);
            pull();
        }
    }

    void pull() {
        val = node::comb(lc->val, rc->val);
    }

    void point_set(ll idx, node x) {
        if (lm == rm) {
            val = x;
            return;
        }
        if (idx <= lc->rm) lc->point_set(idx, x);
        else rc->point_set(idx, x);
        pull();
    }

    node query(ll lq, ll rq) {
        if (rq < lm || lq > rm) return neutral;
        if (lq <= lm && rm <= rq) return val;
        return node::comb(lc->query(lq, rq), rc->query(lq, rq));
    }

    void print(){

        if(lc) lc->print();
        if(rc) rc->print();
        cout << lm << " " << rm << ln; 
        val.print();
    }
};


int main(){
    _;
    ll n; cin >> n;
    vector<string> row(3);
    forn(i,0,3) cin >> row[i];
    ll q; cin >> q;
    vector<node> aux;
    forn(i,0,n){
        vector<char> c = {row[0][i], row[1][i], row[2][i]};
        aux.push_back(node(c));
    }

    tree seg(0,n-1, aux);
    while(q--){
        ll r, c;
        cin >> r >> c;
        r--, c--;
        if(row[r][c] == '#') row[r][c] = '.';
        else row[r][c] = '#';
        vector<char> v = {row[0][c], row[1][c], row[2][c]};
        seg.point_set(c, node(v));
        auto m = seg.query(0,n-1);
        cout << (m.mat[0][2] == INF ? -1 : m.mat[0][2]) << ln;
    }
    return 0;
}