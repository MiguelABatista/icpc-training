#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

    
    if(n%2 == 1){
        if(s[0] == 'b'){
            cout << "NO" << ln;
            return;
        }
        n--;
        s.erase(s.begin());
    }
    

    
    for(ll i = 0; i < n; i += 2){
        if(s[i] == 'a' && s[i+1] == 'a'){
            cout << "NO" << ln;
            return;
        }
        if(s[i] == 'b' && s[i+1] == 'b'){
            cout << "NO" << ln;
            return;
        }
    }
    cout << "YES" << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
