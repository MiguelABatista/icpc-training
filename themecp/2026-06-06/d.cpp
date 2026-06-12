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

#define debug(u) trace(cout << __LINE__ << ": " << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll solvefim(string s){
    ll n = sz(s);
    debug(s);
    string r(n, '0');
    ll resp = 0;
    ll curr = 0;
    ll prox = 0;

    forn(i,0,n){
        if(prox == 1){
            r[i] = '1';
            resp += n-i;
            prox = 0;
            curr = 1;
            continue;
        }
        if(s[i] == '1'){
            if(curr == 1){
                curr = 0;
                continue;
            }
            resp++; 
            prox = 1;
            continue;
        }
        curr = 0;
    }
    if(prox == 1) r[n-1] = '1';
    debug(r);
    return resp;
}

void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    ll resp = 0;

    forn(i,0,n){
        debug(i);
        resp += solvefim(s.substr(i,n-i));
    }

    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}