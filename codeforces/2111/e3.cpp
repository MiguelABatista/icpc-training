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

string s;
ll n, q;

void anda(ll &p, char c){
    while(p < n && s[p] != c) p++;
}

void solve(){
    
    cin >> n >> q;
    cin >> s;

    ll pa = 0;
    ll pb = 0;
    ll pc = 0;

    map<char, set<ll>> cidx;
    
    ll btoc = 0;
    forn(i,0,n) cidx[s[i]].insert(i);

    forn(i,0,q){
        char x,y;
        cin >> x >> y;
        if(x == 'a') continue;
        if(x == y) continue;

        if(x == 'b' && y == 'c'){
            btoc++;
            continue;
        }
        
        if(x == 'c' && y == 'a' && btoc == 0) // nada

        if(x == 'c' && y == 'a' && btoc != 0){
            // muda o primeiro b -> c valido
            // valido é :
            //   ele n apareceu de uma querrie c -> b que veio depois da b -> c que eu guardei

        }

        auto it = cidx[x].begin();
        ll val = *it;
        cidx[x].erase(it);
        cidx[y].insert(val);
        s[val] = y;
    }
    cout << s << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}