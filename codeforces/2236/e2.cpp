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
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
    }

    ll resp = 0; 
    forn(k,1,n/2+1){
        debug(k); 
        vector<vll> pos(n);

        forn(i,0,n-k+1){
            set<ll> s;
            forn(j,i,i+k) s.insert(vec[j]);
            ll ini = *s.begin();
            ll fim = *prev(s.end());
            debugv(s);
            if(fim-ini + 1 == k && sz(s) == k){
                pos[ini].push_back(i);
            }
        }

        forn(i,0,n){debugv(pos[i]);};
        forn(i,0,n){
            if(i+k >= n) break; 
            if(pos[i].empty()) continue;
            if(pos[i+k].empty()) continue;
            for(ll x : pos[i]){
                for(ll y : pos[i+k]){
                    if(abs(x-y) >= k) resp = max(resp, k);
                }
            }
        }
    }
    cout << resp << ln;
    trace(cout << "-----------------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
