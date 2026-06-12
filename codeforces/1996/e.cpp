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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;


void solve(){
    string s; cin >> s;
    ll n = sz(s);
    vll vec(n);
    forn(i,0,n) vec[i] = (s[i] == '1' ? 1 : -1);
    
    ll resp = 0;
    map<ll,ll> pref;
    pref[0]++;
    ll sum = 0;
    forn(i,0,n){
        ll x = vec[i];
        sum += x;
        resp = (resp+pref[sum]*(n-i))%MOD;
        pref[sum] += i+2;
    }

    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
