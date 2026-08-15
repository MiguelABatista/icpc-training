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
    for(ll i = 0; i < n; i++) if(s[i] == '1'){
        ll curr = 0;
        if(i > 0 && s[i-1] == '1') curr++; 
        if(s[i] == '1') curr++; 
        if(i < n-1 && s[i+1] == '1') curr++;
        best = max(curr, best); 
    }   

    // cout << best << " " << resp << "\n";
    if(best == 0) cout << resp << "\n";
    else cout << resp - best + 1 << "\n";
    // cout << "\n";
}

int main(){
    ll t; cin >> t;
    while(t--) solve();
}