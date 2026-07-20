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
    string s; cin >> s;
    ll n = sz(s);
    ll w, q; cin >> w >> q;

    vll vec(n);
    vll pref(n);
    forn(i,0,n) vec[i] = s[i]-'0';
    forn(i,0,n) pref[i] = vec[i] + (i == 0 ? 0 : pref[i-1]);
    auto sum = [&](ll l, ll r){
        return pref[r] - (l == 0 ? 0 : pref[l-1]);
    };

    vector<vll> aux(9);
    forn(i,0,n-w+1) aux[sum(i,i+w-1)%9].push_back(i);
    
    while(q--){
        ll l, r, k; 
        cin >> l >> r >> k;
        l--; r--;
        ll fix = sum(l,r)%9;
        pll best = {INF, INF};
        forn(i,0,9){
            forn(j,0,9){
                pll curr = {INF,INF};
                if((i*fix+j)%9 != k) continue;
                if(sz(aux[i]) >= 1) curr.first = aux[i][0];
                if(sz(aux[j]) >= (1 + (i==j))) curr.second = aux[j][i==j]; 
                
                if(curr.first != INF && curr.second != INF) best = min(best, curr);
            }
        }
        if(best.first == INF || best.second == INF) best = {-2,-2};
        cout << best.first+1 << " " << best.second+1 << ln;
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
