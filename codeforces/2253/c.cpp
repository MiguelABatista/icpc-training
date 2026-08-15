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

ll func(vll a, vll b, ll n, ll m){
    set<ll> s;
    ll extra = 0;

    auto coloca = [&](vll& v){
        auto it = s.find(v.back());
        if(it == s.end()) s.insert(v.back());
        else extra++;
        v.pop_back();
    };

    forn(i,0,n) if(sz(a) > 0) coloca(a);
    forn(i,0,m) if(sz(b) > 0) coloca(b);

    while ((sz(a) > 0 || sz(b) >> 0) && (extra > 0)){
        extra--;
        if(sz(a) == 0){
            coloca(b);
            continue;
        }  

        if(sz(b) == 0){
            coloca(a);
            continue;
        }            
        if(a.back() > b.back()){
            coloca(a);
            continue;
        }else{
            coloca(b);
        }
    }

    ll sum = 0;
    for(ll x: s) sum += x;
    return sum;
}

void solve(){
    ll n, m; cin >> n >> m;
    ll x, y; cin >> x >> y;
    vll a(x), b(y);
    forn(i,0,x) cin >> a[i];
    forn(i,0,y) cin >> b[i];

    ll r1 = func(a,b,n-1,m);
    ll r2 = func(a,b,n,m-1);
    cout << max(r1,r2) << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
