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

void solve(){
    ll a, b, x; 
    cin >> a >> b >> x;
    vector<pll> as;
    vector<pll> bs;
    ll aux = a;
    ll cost = 0;  
    while(aux > 0){
        as.push_back({aux, cost});
        aux /= x;
        cost++;
    }
    as.push_back({aux, cost});
    aux = b;
    cost = 0;  
    while(aux > 0){
        bs.push_back({aux, cost});
        aux /= x;
        cost++;
    }
    bs.push_back({aux, cost});

    ll resp = INF;
    for(auto [aa, ca] : as){
        for(auto [bb, cb] : bs){
            resp = min(resp, ca+cb + abs(aa-bb));
        }
    }
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
