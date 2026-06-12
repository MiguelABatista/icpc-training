#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l,r);
    return uid(rng);
}

int main() {
    _;
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){
        string s; cin >> s;
        vec[i] = stoi(s, 0, 16);
    }
    
    ll best = 0;
    ll bm = 0; 
    forn(mask,0,(1<<n)){
        ll cnt = 0;
        ll resp = 0;
        forn(i,0,n){
            if(((1<<i)&mask) == 0) continue;
            resp += vec[i]^cnt;
            cnt++;
        }
        if(resp > best){
            bm = mask;
            best = resp;
        }
    }
  
    cout << best << ln;
    trace(
        debugv(vec);
        cout << bitset<10>(bm) << ln;
    )
    return 0;
}
 