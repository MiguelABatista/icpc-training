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

pair<vll, vll> sieve(ll n){
    vll lp(n+1);
    vll pr;
    forn(i,2,n+1){
        if(lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
        }
        for(ll j = 0; i * pr[j] <= n; ++j){
            lp[i * pr[j]] = pr[j];
            if(pr[j] == lp[i]) {
                break;
            }
        }
    }
    return {pr, lp};
}

int main() {
    _;
    ll n, q; cin >> n >> q;
    auto [pr, lp] = sieve(n);
    vector<pair<vll, ll>> vec(n+1);

    forn(i,1,n+1){
        ll x = i;
        while(x > 1){
            ll p = lp[x];
            vec[i].first.push_back(p);
            x /= lp[x];
        }
        vec[i].second = i;
    }

    sort(vec.begin(), vec.end());
    while (q--){
        ll idx; cin >> idx;
        cout <<  vec[idx].second << ln;
    }
    
    return 0;
}
