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

const ll INF = 0x3f3f3f3f3f3f3f3fll;


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
    
    ll tam(ll a){
        return len[find(a)];
    }
};


int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);
    priority_queue<p64> pq;
    forn(i,0,n){
        cin >> vec[i];
        pq.push({vec[i], i});
    }

    dsu sdu(n);
    ll last = pq.top().first;
    ll kresp = 0;
    vector<bool> active(n);

    map<ll, ll> kop;
    while(!pq.empty()){
        auto [val, idx] = pq.top();
        pq.pop();

        if(val != last){
            kop[last] = kresp;
        }
        last = val;

        debug(val);
        debug(idx);
        debug(kresp);
        if(idx > 0 && active[idx-1]){
            kresp -= (sdu.tam(idx-1)+1)/2;
            debug(kresp);
            sdu.uni(idx-1, idx);
        }
        if(idx < n-1 && active[idx+1]){
            kresp -= (sdu.tam(idx+1)+1)/2;
            debug(kresp);
            sdu.uni(idx+1, idx);
        }
        
        kresp += (sdu.tam(idx)+1)/2;
        debug(kresp);

        if(pq.empty()){
            kop[val] = kresp;
        }
        active[idx] = true;
        trace(cout << "-------------------\n\n");
    }
 
    debugm(kop);
    last = 0;
    ll resp = 0;
    for(auto [k, amt] : kop){
        resp += amt*(k-last);
        debug(resp);
        last = k;
    }
    cout << resp << ln; 
    return 0;
}