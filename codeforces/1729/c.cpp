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
    string s; cin >> s;
    ll n = sz(s);
    char baixo = min(s[0], s[n-1]);
    char cima = max(s[0], s[n-1]);
    bool reverse = false;
    if(baixo == s[n-1]) reverse = true;
    vector<pair<char, ll>> resp;
    forn(i,1,n-1){
        if(s[i] >= baixo && s[i] <= cima) resp.push_back({s[i],i});
    }
    if(reverse) sort(resp.rbegin(), resp.rend());
    else sort(resp.begin(), resp.end());
    cout << cima-baixo << " " << sz(resp) + 2 << ln;
    cout << 1 << " ";
    forn(i,0,sz(resp)) cout << resp[i].second+1 << " ";
    cout << n << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
