#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct dsu {
	v64 id, len, c;
    ll allbip = true;
	stack<pair<ll&, ll>> st;

	dsu(ll n) : id(n), len(n, 1), c(n,0) { 
		iota(id.begin(), id.end(), 0); 
	}
		
	void save(ll &x) { 
        st.emplace(x, x);
    }

	ll time() { return sz(st); }

	void rollback(ll t) {
		while(sz(st) > t) {
			auto [end, val] = st.top(); st.pop();
			end = val;
		}
	}

	ll find(ll a) { return a == id[a] ? a : find(id[a]); }
	ll color(ll a) { return a == id[a] ? c[a] : c[a] ^ color(id[a]); }

    void unite(ll a, ll b) {
		bool change = color(a) == color(b);
		a = find(a), b = find(b);
		if (a == b) {
			if (change) {
                save(allbip);
                allbip = false;
            }
			return;
		}
		
		if (len[a] < len[b]) swap(a, b);
		if (change){
            save(c[b]);
            c[b] = 1;
        }
        save(len[a]);
        save(id[b]);
		len[a] += len[b], id[b] = a;
	}
};


int main() {
    _;
    ll n, m;
    cin >> n >> m;
    vector<p64> edges(m);

    forn(i,0,m){
        cin >> edges[i].first;
        cin >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    dsu sdu(n);
    vector<bool> boa(m, false);

    function<void (ll, ll)> dnc = [&](ll l, ll r){ // semi aberto

        trace(cout << l << " " << r << ln;);

        if(l+1 == r){
            debug(l);
            debug(sdu.allbip);
            boa[l] = sdu.allbip;
            return; 
        }
        
        ll mid = (l+r)/2;
        
        // l ... m, m ... r
        
        ll t1 = sdu.time();
        
        forn(i,mid,r){
            sdu.unite(edges[i].first, edges[i].second);
        }

        dnc(l, mid);

        sdu.rollback(t1);
        
        forn(i,l,mid){
            sdu.unite(edges[i].first, edges[i].second);
        }

        dnc(mid, r);

        sdu.rollback(t1);
    };

    dnc(0,m);

    v64 resp;
    forn(i,0,m) if(boa[i]) resp.push_back(i);

    cout << sz(resp) << ln;
    forn(i,0,sz(resp)) cout << resp[i] + 1 << " \n"[i == sz(resp)-1];
    
    return 0;
} 
