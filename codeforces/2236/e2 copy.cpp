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

ll test(multiset<ll> s){
    ll ini = *s.begin();
    ll fim = *prev(s.end());
    if(fim - ini + 1 == sz(s)) return ini;
    return -1;
}

void solve(){
    ll n; cin >> n;
    vll vec(n);
    forn(i,0,n){
        cin >> vec[i];
        vec[i]--;
    }

    ll resp = 0;
    forn(k,1,n/2+1){
        vector<vll> pos(n);

        multiset<ll> s;
        forn(i,0,k) s.insert(vec[i]);
        ll xxx = test(s);
        debug(xxx);
        if(xxx != -1) pos[xxx].push_back(0);
        
        forn(i,k,n){
            s.insert(vec[i]);
            s.erase(s.find(vec[i-k]));
            ll x = test(s);
            if(x != -1) pos[x].push_back(i-k+1);
        }

        forn(i,0,n){debugv(pos[i]);};
        forn(i,0,n){
            if(i+k >= n) break;
            if(pos[i].empty()) continue;
            if(pos[i+k].empty()) continue;
            ll mini = INF;
            ll mink = INF;
            ll maxi = -INF;
            ll maxk = -INF;
            for(ll x : pos[i]){
                mini = min(mini, x);
                maxi = max(maxi, x);
            }
            for(ll x : pos[i+k]){
                mink = min(mink, x);
                maxk = max(maxk, x);
            }
            if(mini + k -1 < maxk){
                resp = max(resp, k);
                break;
            }
            if(mink + k -1 < maxi){
                resp = max(resp, k);
                break;
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
