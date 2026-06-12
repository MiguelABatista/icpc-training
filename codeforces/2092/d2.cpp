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

char func(char a, char b){
    assert(a != b);
    set<char> s = {'T', 'I', 'L'};
    s.erase(a);
    s.erase(b);
    return *s.begin();
}

void solve(){
    ll k; cin >> k;
    if(k == -1){
        cout << 1 << ln;
        return;
    }
    vll vec(k);
    forn(i,0,k) cin >> vec[i];

    ll n; cin >> n;
    vector<char> s(n); 
    forn(i,0,n) cin >> s[i];
    
    forn(i,0,k){
        ll t= vec[i];
        debug(t);
        debugv(s);
        char c = func(s[t-1],s[t]);
        s.insert(s.begin()+t, c);
        debugv(s);
        n++;
    }
    map<char, ll> freq; 
    forn(i,0,n) freq[s[i]]++;
    for(auto[kk ,v]: freq){
        if(3*v != n){
            cout << -1 << ln;
            return;
        }
    }
    cout << 1 << ln;

    // forn(i,0,n) cout << s[i];
    // cout << ln;
}

int main() {
    _;
    ll t = 1; 
    while(t--) solve();
    return 0;
}
