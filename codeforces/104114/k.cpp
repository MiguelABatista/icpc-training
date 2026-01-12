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

#define debugv(v) trace({cout << #v": "; for (auto u : v) cout<< u << " "; cout << ln;})
#define debugm(v) trace({cout << #v": "; for (auto u : v) cout<< u.first << ":" << u.second << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll n;

vector<map<ll, ll>> g;

// Segment Tree (Range Query + Point Update)
//
//supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)
const ll d = 11;

struct node {
    
    vector<v64> mat;
    ll l, r;
    node() : mat(d,v64(d, 0)), l(-10), r(-10){}
    node(ll x) : mat(d,v64(d, 0)), l(x), r(x){}
    
    void print(){
        cout << l << " " << r << ln;
        forn(i,0,d){
            forn(j,0,d){
                cout << setw(3) << (mat[i][j] >= INF ? 999 : mat[i][j]) << " ";
            }
            cout << ln;
        }
        cout << ln;
    }
    
    static node comb(node& a, node& b, bool printa = false) {
        node no(0);
        if(a.l == -1) return b;
        if(b.l == -1) return a;

        no.l = a.l;
        no.r = b.r;

        if(no.l == -1 || no.r == -1) assert(false);
        if(printa){
            a.print();
            b.print();
        }

        vector<v64> intermed(d, v64(d));

        forn(i,0,d){
            forn(j,0,d){
                if(a.r*d+i >= n || b.l*d + j >= n){
                    intermed[i][j] = INF;
                    continue;
                } 
                ll val = g[a.r*d + i][b.l*d + j];
                if(val == 0){
                    intermed[i][j] = INF;
                }else{
                    intermed[i][j] = val;
                }
            }
        }

        forn(i,0,d){
            forn(j,0,d){
                ll& ans = no.mat[i][j];
                ans = INF;
                forn(k,0,d){
                    ans = min(ans, (a.mat[i][k] + intermed[k][j] >= INF ? INF : a.mat[i][k] + intermed[k][j]));
                }
            }
        }

        intermed = no.mat;
        
        forn(i,0,d){
            forn(j,0,d){
                ll& ans = no.mat[i][j];
                ans = INF;
                forn(k,0,d){
                    ans = min(ans, (intermed[i][k] + b.mat[k][j] >= INF ? INF : intermed[i][k] + b.mat[k][j]));
                }
            }
        }
        return no;
    }
};

template<typename T> struct segtree {
    ll nseg;
    T neutral;
    vector<T> tree;
    
    segtree<T>(ll _n, T _neutral) {
        nseg = _n, neutral = _neutral;
        tree.resize(2*nseg+1, neutral);
    }
    
    void set_leaves(vector<T> &leaves) {
        copy(leaves.begin(), leaves.end(), tree.begin() + nseg);
        
        for (ll i = nseg - 1; i > 0; i--) tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
    }
    
    void update(ll i, T v) {
        i += nseg;
        tree[i] = v;
        while (i > 1) {
            i /= 2;
            tree[i] = T::comb(tree[2 * i], tree[2 * i + 1]);
        }
    }
    
    T query(ll i, ll j) {
        T rl = neutral, rr = neutral;
        for(i += nseg, j += nseg; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) rl = T::comb(rl, tree[i++]);
            if((j&1) == 0) rr = T::comb(tree[j--], rr);
        }
        return T::comb(rl, rr);
    }

    void print(){
        for(auto nu: tree) nu.print();
    }
};

int main(){
    _;
    ll m, q; cin >> n >> m >> q;
    g.resize(n);
    
    forn(i,0,m){
        ll a, b, w;
        cin >> a >> b >> w;
        a--,b--;
        g[a][b] = w;
        g[b][a] = w;
    }

    forn(i,0,n){
        for(auto [v, wv] : g[i]){
            if(v < i) continue;
            for(auto [u, wu] : g[i]){
                if(u == v) continue;
                if(u < i) continue;
                
                if(g[v][u] == 0){
                    g[u][v] = g[v][u] = wv + wu; 
                }else if (wv + wu < g[v][u]){
                    g[u][v] = g[v][u] = wv + wu; 
                }
            }
        }
    }


    for(ll i = n-1; i >= 0; i--){
        for(auto [v, wv] : g[i]){
            if(v > i) continue;
            for(auto [u, wu] : g[i]){
                if(u == v) continue;
                if(u > i) continue;
                
                if(g[v][u] == 0){
                    g[u][v] = g[v][u] = wv + wu; 
                }else if (wv + wu < g[v][u]){
                    g[u][v] = g[v][u] = wv + wu; 
                }
            }
        }
    }

    ll segn = (n+d-1)/d;
    
    vector<node> aux;

    forn(t,0,segn){
        node nn(t);
        auto& dist = nn.mat;

        forn(i,0,d){
            forn(j,0,d){
                if(i == j) continue;
                if(t*d+i >= n || t*d + j >= n){
                    dist[i][j] = INF;
                    continue;
                };
                dist[i][j] = (g[t*d + i][t*d + j] == 0 ? INF : g[t*d + i][t*d + j]);
            }
        }
        
        forn(k,0,d)
        forn(i,0,d)
        forn(j,0,d){
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }

        debug(t);
        aux.push_back(nn);
    }   

    // aux[0].print();

    // auto asd = node::comb(aux[0],aux[1]);
    // trace(
    //     aux[0].print();
    //     aux[1].print();
    //     asd.print();
    // );

    node neu(-1); 

    forn(i,0,d){
        forn(j,0,d) if(i!=j){
            neu.mat[i][j] = INF;
        }
    } 

    segtree<node> seg(segn,neu);
    seg.set_leaves(aux);
    trace(
        seg.print();
    );
    // node::comb(aux[0], neu, true).print();

    forn(iiiiiii,0,q){ 
        ll a, b; cin >> a >> b;
        a--, b--;
        if(a > b) swap(a,b);

        ll i = a%d;
        ll l = a/d;

        ll j = b%d;
        ll r = b/d;

        auto nan = seg.query(l,r);
        ll ans = nan.mat[i][j]; 
        // trace(
        //     cout << l << " " << r << " " << i << " " << j << ln;
        //     nan.print();
        // );
        if(ans >= INF) ans = -1;
        cout << ans << ln;
    }

    return 0;
} 