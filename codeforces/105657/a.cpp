// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// typedef pair<ll, ll> p64; 
// typedef vector<ll> v64;

// #define forn(i, s, e) for(ll i = (s); i < (e); i++)
// #define ln "\n"

// #if defined(DEBUG)
//     #define _ (void)0
//     #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
// #else
//     #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
//     #define debug(x) (void)0
// #endif

// const ll INF = 0x3f3f3f3f3f3f3f3fll;

// int main(){
//     _;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct dsu {
    vector<ll> id, sz;
     dsu(ll n) : id(n), sz(n,1) { iota(id.begin(), id.end(), 0);}

    ll find(ll a) { return a == id[a] ? a : id[a] = find(id[a]); }

    void uni(ll a, ll b) {
        a = find(a), b = find(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b], id[b] = a;
    }
};

void solve(){
    string s1, s2, s3; cin >> s1 >> s2 >> s3;
    ll n = s1.size();

    if(s1.size() != s2.size()){
        cout << "NO" << ln;
        return;
    }
    if(s1.size()!= s3.size()){
        cout << "YES" << ln;
        return;
    }

    dsu sdu(26);
    forn(i, 0, n){
        sdu.uni(s1[i]-'a', s2[i]-'a');
    }

    bool possible = false;
    forn(i, 0, n) if(sdu.find(s1[i]-'a') != sdu.find(s3[i]-'a')) possible = true;

    if(possible) cout << "YES" << ln;
    else cout << "NO" << ln;
}

int main() {
    _; ll t; cin >> t;
    while(t--) solve();
    return 0;
}