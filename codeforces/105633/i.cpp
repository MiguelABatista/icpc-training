#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

typedef ll T;

#define LC nd * 2 + 1
#define RC nd * 2 + 2


const T NEUTRAL = -1;

struct SegTree {
  vector < T > tree;
  ll n;

  T op(const T & a, const T & b) {
    return max(a, b);
  }

  SegTree(const vector < T > & v): n(v.size()) {
    tree.resize(4 * n);
    _build(v, 0, 0, n - 1);
  }

  void update(ll idx, const T & val) {
    _update(idx, val, 0, 0, n - 1);
  }

  T query(ll l, ll r) {
    return _query(l, r, 0, 0, n - 1);
  }
  
  void _build(const vector < T > & v, ll nd, ll st, ll ed) {
    if (st == ed) {
      tree[nd] = v[st];
    } else {
      ll mid = (st + ed) / 2;
      _build(v, LC, st, mid);
      _build(v, RC, mid + 1, ed);
      tree[nd] = op(tree[LC], tree[RC]);
    }
  }
  
  void _update(ll idx, const T & val, ll nd, ll st, ll ed) {
    if (st == ed) tree[nd] = val;
    else {
      ll mid = (st + ed) / 2;
      if (idx <= mid) _update(idx, val, LC, st, mid);
      else _update(idx, val, RC, mid + 1, ed);
      tree[nd] = op(tree[LC], tree[RC]);
    }
  }

  T _query(ll l, ll r, ll nd, ll st, ll ed) {
    if (r < st || ed < l) return NEUTRAL;
    if (l <= st && ed <= r) return tree[nd];
    ll mid = (st + ed) / 2;
    T left = _query(l, r, LC, st, mid);
    T right = _query(l, r, RC, mid + 1, ed);
    return op(left, right);
  }

};

v64 fir(100'005, -1);
v64 sec(100'005, -1);
SegTree seg(sec);

void atualiza(ll t, ll idx){
    sec[t] = fir[t];
    fir[t] = idx;
    seg.update(t, sec[t]);
}

void get_div(ll k, ll idx){
    for (long long i = 1; i*i <= k; ++i) {
        if (k % i == 0) {
            atualiza(i, idx);
            if (i * i != k) { 
               atualiza(k / i, idx);
            }
        }
    }
}

ll bs(ll bound){
	ll l, r;
	l = 0;
	r = 100'005;

	// cout << bound << ln;

	// forn(i,0,36) cout << i << ':' << sec[i] << "  ";
	// cout << ln;

	while(l+1 < r){
		ll mid = (r+l)/2;
		ll aux = seg.query(mid,r); 
		// cout << l << ' ' << mid << ' ' << r << ' ' << aux << ln;
		if(aux >= bound){
			l = mid;
		}else{
			r = mid;
		}
	}

	if(sec[r] >= bound) return r;
	return l;
}

int main(){
    _;
    ll n; cin >> n;
    v64 vec(n);

    forn(i,0,n) cin >> vec[i];

    ll q; cin >> q;
    
    vector<pair<p64, ll>> querries(q);

    forn(i,0,q){
        ll l, r;
        cin >> l >> r;
		l--; r--;
        querries[i] = {{r,l}, i};
    }

    sort(querries.begin(), querries.end());

    ll curr_r = 0;
	v64 resp(q);

    forn(i,0,q){
        ll r = querries[i].first.first; 
        ll l = querries[i].first.second;
		while (curr_r <= r){
			get_div(vec[curr_r], curr_r);
			curr_r++;
		}
		
		// cout << l << " # " << r << " # " << querries[i].second << ln;
		ll aux = bs(l);
		resp[querries[i].second] = aux;
    }	

	forn(i,0,q) cout << resp[i] << ln;

	
    return 0;
}