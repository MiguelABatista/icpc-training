#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    ll resp = 0, full = 0;
    forn(i,0,n){
        string s; cin >> s;
        ll m = 0;
        if(s[0] == '=') m = 3;
        if(s[m] == 'x' && s[m+1] == 'x' && s[m+2] == 'x') full++;
        else if(s[m+1] == 'x' && (s[m] == 'x' || s[m+2] == 'x')) resp++;
    }
    if((resp%2 + full%2) >  0) cout << "Monocarp" << ln;
    else cout << "Polycarp" << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}