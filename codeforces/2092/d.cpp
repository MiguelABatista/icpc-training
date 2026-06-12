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
    ll norig = n;
    string s; cin >> s;
    debug(s);
    map<char, ll> m1, conv;
    vector<pair<ll,char>> auxx;
    vll vec(n), freq(3);

    m1['T'] = 0;
    m1['L'] = 0;
    m1['I'] = 0;

    forn(i,0,n) m1[s[i]]++;
    
    for(auto [k,v] : m1) auxx.push_back({v,k});
    sort(auxx.begin(), auxx.end());

    ll semnome = 0;
    for(auto [amt, c] : auxx){
        freq[semnome] = amt;
        conv[c] = semnome++;
    }
    forn(i,0,n) vec[i] = conv[s[i]];

    // freq 0 <= freq1 <= freq2
    // vec tem 0 1 e 2

    auto tenta = [&](ll val){
        forn(i,0,n-1){
            if(vec[i] == val) continue;
            if(vec[i+1] == val) continue;
            if(vec[i+1] == vec[i]) continue;
            vec.insert(vec.begin()+i+1, val);
            return i+1;
        }
        return (ll)(-1);
    };

    // debugv(vec);
    // debugv(freq);
    vll resp;
    while(freq[0] < freq[1] || freq[1] < freq[2]){
        ll x = -1;
        if(freq[0] < freq[1]) x = tenta(0);
        if(x == -1 && freq[1] < freq[2]) x = tenta(1);
        if(x == -1) x = tenta(2);
        if(x == -1){
            cout << -1 << ln;
            return;
        }
        n++;
        freq[vec[x]]++;
        resp.push_back(x);
        debugv(vec);
    }
    cout << sz(resp) << ln;
    for(ll x : resp) cout << x << ln;
    // cout << n << ln;
    // cout << s << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}

