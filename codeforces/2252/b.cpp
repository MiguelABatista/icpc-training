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
    char cc = s[0];
    ll csz = 1;
    vll comp0;
    vll comp1;
    forn(i,1,n){
        if(s[i] == cc) csz++;
        else{
            if(cc == '0') comp0.push_back(csz);
            if(cc == '1') comp1.push_back(csz);
            cc = s[i];
            csz = 1;
        }
    }

    if(cc == '0') comp0.push_back(csz);
    if(cc == '1') comp1.push_back(csz);

    ll gor1 = 0;
    ll gor0 = 0;
    for(ll x: comp0) gor0 += x-1;
    for(ll x: comp1) gor1 += x-1;
    ll sz1 = sz(comp1);
    ll sz0 = sz(comp0);
    if(gor0 > gor1){
        swap(sz0,sz1);
        swap(gor0, gor1);
        forn(i,0,n){
            if(s[i] == '0') s[i] = '1';
            else s[i] = '0';
        }
    }
    ll resp = 2*gor0;
    gor1 -= gor0;

    ll aux = 1;
    if(s[0] == '0') aux++;
    if(s[n-1] == '0') aux++;
    debug(gor1);
    if(gor1 > aux){
        cout << -1 << ln;
        trace(cout << "-------------------\n\n";)
        return;
    }
    cout << resp + 2*gor1 - (gor1 != 0) << ln;
    trace(cout << "-------------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
