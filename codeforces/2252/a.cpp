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
    map<ll, ll> freq;
    forn(i,0,n){
        ll x; cin >> x;
        freq[x]++;
    }
    ll last = -1;
    ll resp = 0;

    forn(i,0,n){
        ll best = 0;
        ll kb = -1;
        for(auto [k,v] : freq){
            if(k == last) continue;
            if(v > best){
                best = v;
                kb = k;
            }
        }
        if(kb == -1){
            resp += last;
            break;
        }
        resp += kb;
        freq[kb]--;
        last = kb;
        if(freq[kb] == 0) freq.erase(kb);
    }
    cout << resp << ln;
    trace( cout << "------------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
