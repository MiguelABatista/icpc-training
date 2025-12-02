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

// Disjoint Set Union (Union-Find)
//
// Supports find with path compression and union by size to maintain dynamic connectivity of disjoint sets.
//
// complexity: O(alpha(N)) amortized per op, O(N)

struct dsu {
	v64 id, len;

	dsu(ll n) : id(n), len(n, 1) { iota(id.begin(), id.end(), 0); }

	ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

	void uni(ll a, ll b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (len[a] < len[b]) swap(a, b);
		len[a] += len[b], id[b] = a;
	}
};


const ll INF = 0x3f3f3f3f3f3f3f3fll;
vector<v64> g;
v64 vl, vr;

ll ini = -1;
ll fim = -1;

p64 fp(ll a, ll b){
    if(a < b) return {a,b};
    return {b,a};
}

ll testa(v64& vec){
    set<p64> s;
    ll n = sz(vec);
    forn(i,0,n-1){
        if(vec[i] == vec[i+1]) continue;
        s.insert(fp(vec[i], vec[i+1]));
    }
    return sz(s);
}

v64 euler_path() {
    vector<ll> st, path;
    ll start = ini;
    st.push_back(start);

    while (!st.empty()) {
        ll v = st.back();
        if (!g[v].empty()) {
            ll u = g[v].back();
            g[v].pop_back();
            auto it = find(g[u].begin(), g[u].end(), v);
            if (it != g[u].end()) g[u].erase(it);
            st.push_back(u);
        } else {
            path.push_back(v);
            st.pop_back();
        }
    }

    reverse(path.begin(), path.end());
    return path;
}

bool solve2(){
    ll p; cin >> p;
    vl.resize(p);
    forn(i,0,p) cin >> vl[i];

    ll q; cin >> q;
    vr.resize(q);
    forn(i,0,q) cin >> vr[i];

    if(p+q <= 1) return true;
    if(p+q > 2) return false;
    
    forn(i,0,q) vl.push_back(vr[i]);
    v64 cnt(3);
    
    forn(i,0,p+q) cnt[vl[i]]++;

    if(cnt[1] > 1 || cnt[2] > 1) return false;
    return true;
}

bool solve(ll n){
    g.resize(n);
    ll p; cin >> p;
    vl.resize(p);
    forn(i,0,p){
        cin >> vl[i];
        vl[i]--;
    }

    ll q; cin >> q;
    vr.resize(q);
    forn(i,0,q){
        cin >> vr[i];
        vr[i]--;
    }

    set<p64> aux;
    forn(i,0,n){
        forn(j,i+1,n){
            aux.insert({i,j});
        }
    }

    dsu sdu(n);
    v64 degs(n);
    
    forn(i,0,p-1){
        auto it = aux.find(fp(vl[i], vl[i+1]));
        if(it == aux.end()) return false;
        aux.erase(it);   
    }
    forn(i,0,q-1){
        auto it = aux.find(fp(vr[i], vr[i+1]));
        if(it == aux.end()) return false;
        aux.erase(it);   
    }

    for(p64 pa: aux){
        sdu.uni(pa.first, pa.second);
        degs[pa.first]++;
        degs[pa.second]++;
        g[pa.first].push_back(pa.second);
        g[pa.second].push_back(pa.first);
    }

    set<ll> componentes;

    ll odds = 0;

    forn(i,0,n){
        if(degs[i] != 0) componentes.insert(sdu.find(i));
        if(degs[i]%2 == 1) odds++;
    }

    if(sz(componentes) == 0) return (p == 0 || q == 0);
    if(sz(componentes) > 1) return false;   
    if(p + q == 0) return true;
    
    if(p == 0){
        swap(p, q);
        swap(vl, vr);
    }
    
    if(p != 0) ini = vl.back();
    if(q != 0) fim = vr.front();

    if(odds > 3) return false;
    if(odds == 2){
        if(q == 0){
            if(degs[ini]%2 == 1 && degs[vl.front()]%2 == 1) return true;
            return false;
        }
        if(ini == fim) return false;
        if(degs[ini]%2 == 1 && degs[fim]%2 == 1) return true;
        return false;
    }
    if(odds == 1) return false;

    return q == 0 ? true : ini == fim;
}

int main(){
    _;
    ll n; cin >> n;
    
    if(n == 2){
        cout << "NY"[solve2()] << ln;
        return 0;
    }

    if(n%2 == 0){
        cout << "N" << ln;
        return 0;
    }   

    if(solve(n)){
        cout << "Y" << ln;
    }else{
        cout << "N" << ln;
    }
    return 0;
}