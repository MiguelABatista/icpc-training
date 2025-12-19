#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


void solve(){
    ll n, m, k; cin >> n >> m >> k;
    ll cnt = 0;
    ll q = (m*n)/k;

    vector<v64> mat(n, v64(m, 0));

    auto decomp = [&](ll x){
        return (p64){x/m, x%m};
    };
    ll base_idx = 0;

    while(base_idx < m*n){
        auto [ba,bb] = decomp(base_idx);
        if(mat[ba][bb] != 0){
            base_idx++;
            continue;
        }
        ll idx = base_idx;
        while(idx < m*n){
            auto [a,b] = decomp(idx);
            trace(cout << idx << " " << a << ":" << b << " " << cnt/q + 1 << ln;);
            mat[a][b] = cnt/q + 1;
            cnt++;
            if((m%2 == 0) && (idx/m != (idx+2)/m)){
                if((idx+1)/m != idx/m) idx += 1;
                else idx += 3;
            } else idx += 2;
        }
    }
        
    forn(i,0,n) debugv(mat[i]);
    trace(cout << ln;);
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}