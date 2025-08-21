#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    string s;
    cin >> s;

    map<char, ll> mp;
    forn(i,0,s.size()) mp[s[i]]++;
    string out;
    ll t = mp['T'];
    while(t--) out.push_back('T');
    mp['T'] = 0;
    for(auto& [k,v] : mp){
        if(k == 'T') continue;
        forn(i,0,v) out.push_back(k);
    }
    cout << out << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
