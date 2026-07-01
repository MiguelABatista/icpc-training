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
    string r = s;
    ll saldo = 0;
    ll p1 = 0;
    forn(i,0,n){
        if(s[i] == '0') saldo++;
        else saldo--;
        if(saldo < 0){
            while(p1 < n && r[p1] == '0') p1++;
            r[p1] = '0';
            saldo += 2;
        }
    }
    ll resp = (n*(n+1))/2;
    forn(i,0,n) if(r[i] == '1') resp -= (i+1);
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
