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

vll pi(string s){
    vll p(sz(s));
    for (ll i = 1, j = 0; i < sz(s); i++) {
        while (j && s[j] != s[i]) j = p[j-1];
        if (s[j] == s[i]) j++;
        p[i] = j;
    }
    return p;
}

vll get_z(string s) {
    ll n = sz(s);
    vll z(n, 0);

    ll l = 0, r = 0;
    forn(i,1,n){
        if( i <= r) z[i] = min(r-i+1, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;  
    }
    return z;
}

ll comp(string a, string b){
    ll n = sz(a);
    ll m = sz(b);

    string bb = b;
    string aa = a;
    reverse(b.begin(), b.end());
    reverse(a.begin(), a.end());
    string invb = b;
    string inva = a;
    b = bb;
    a = aa;
    
    string trash = "#";
    string c = a +trash+ invb;
    string d = a + trash + inva;
    vll z = get_z(c);
    vll kmp = pi(d);

}

void solve(){
    string a; cin >> a;
    string b; cin >> b;
    ll resp = comp(a,b) + comp(b,a);
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();

    return 0;
}
