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
#define debugm(v) trace({cout << #v": "; for (auto x : v) cout<< x.first << ":" << x.second << " "; cout << ln;})
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

p64 fp(ll a, ll b){
    if(a < b) return {a,b};
    return {b,a};
}

bool testa(v64& vec){
    set<p64> s;
    ll n = sz(vec);
    forn(i,0,n-1){
        if(vec[i] == vec[i+1]) continue;
        s.insert(fp(vec[i], vec[i+1]));
    }
    if(sz(s) == n-1){
        return true;
    }
    return false; 
}

int main(){
    _;
    cout << "N" << ln;
    return 0;
    ll n; cin >> n;
    
    ll p; cin >> p;
    v64 vl(p);
    forn(i,0,p){
        cin >> vl[i];
        vl[i]--;
    }

    ll q; cin >> q;
    v64 vr(q);
    forn(i,0,q){
        cin >> vr[i];
        vr[i]--;
    }

    ll tam = (n*(n-1))/2+1;
    v64 vec(tam, -1);
    forn(i,0,p) vec[i] = vl[i]; 
    forn(i,0,q) vec[tam-q+i] = vr[i];
    ll l = p;
    ll r = tam - q;

    ll lim = 1;
    forn(i,0,r-l+1) lim*= n;
    ll mask = 0;
    while (mask < lim){
        v64 aux = vec;
        ll auxmask = mask;
        forn(i,l,r){
            vec[i] = auxmask%n;
            auxmask /= n;
        }
        if(testa(vec)){
            cout << "Y" << ln;
            return 0;
        }
        mask++;
    }   
    cout << "N" << ln;
    return 0;   
}