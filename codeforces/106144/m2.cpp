#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

// #define forn(i,s,e) for (ll i=(s);)

void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    ll resp = 0;
    for(ll i = 0; i < n; i++) if(s[i] == '1') resp++;
    ll best = 0;
    for(ll i = 1; i < n-1; i++){
        if(s[i] == '1') best = max(best, (ll)(s[i-1] == '1') + (ll)(s[i] == '1') + (ll)(s[i+1] == '1'));
    }   
    // cout << best << "\n";
    if(best == 0) cout << resp << "\n";
    else cout << resp - best + 1 << "\n";
    // cout << "\n";
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
}