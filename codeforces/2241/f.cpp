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
    string s; cin >> s;
    while(s.back() == '1') s.pop_back();
    ll p = 0;
    while(p < sz(s) && s[p] == '0') p++;
    s = s.substr(p, sz(s));
    n = sz(s);
    if(n == 0){
        cout << "Bob" << ln;
        return;
    }

    char c = '1';
    vll vec = {0};
    forn(i,0,n){
        if(c == s[i]) vec[sz(vec)-1]++;
        else{
            c = s[i];
            vec.push_back(1);
        }
    }
    for(ll x : vec){
        if(x%2 == 1){
            cout << "Alice" << ln;
            return;
        }
    }
    cout << "Bob" << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
