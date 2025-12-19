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
    
    set<ll> s;
    forn(i,0,n*m) s.insert(i);

    while(base_idx < m*n){
        auto [ba,bb] = decomp(base_idx);
        if(mat[ba][bb] != 0){
            base_idx++;
            continue;
        }
        ll idx = base_idx;
        debug(base_idx);
        while(idx < m*n){
            auto [a,b] = decomp(idx);
            trace(cout << idx << " " << a << ":" << b << " " << cnt/q + 1 << ln;);
            ll val = cnt/q+1;
            ll valid = true;
            if(mat[a][b] != 0) valid = false;
            if(a > 0 && mat[a-1][b] == val) valid = false;
            if(b > 0 && mat[a][b-1] == val) valid = false;
            if(a < n-1 && mat[a+1][b] == val) valid = false;
            if(b < m-1 && mat[a][b+1] == val) valid = false;
            
            if(valid){
                mat[a][b] = val;
                s.erase(idx);
                cnt++;
            }else{
                auto it = s.lower_bound(idx+2);
                if(it == s.end()) break; 
                idx = *it;
                continue;
            }
            if((m%2 == 0) && (idx/m != (idx+2)/m)){
                if((idx+1)/m != idx/m) idx += 1;
                else idx += 3;
            } else idx += 2; 
        }
    }
   
    // cout << n << " " << m << " " << k << ln;
    forn(i,0,n){ 
        forn(j,0,m) cout << mat[i][j] << " ";; cout << ln;
    }
    trace(cout << ln;);
    debug(cnt);    
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}