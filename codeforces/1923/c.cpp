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
    ll n, q; cin >> n >> q;
    v64 vec(n);
    v64 ones(n);
    v64 acc_ones(n);
    v64 acc_sum(n);

    forn(i,0,n){
        cin >> vec[i];
        if(vec[i] == 1) ones[i] = 1;
    }

    acc_sum[0] = vec[0];
    acc_ones[0] = ones[0];
    forn(i,1,n){
        acc_sum[i] = acc_sum[i-1] + vec[i];
        acc_ones[i] = acc_ones[i-1] + ones[i];
    }

    auto sum = [](ll l, ll r, v64& v){
        return v[r] - (l == 0 ? 0 : v[l-1]);
    };
 
    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        if(a == b){
            cout << "NO" << ln;
            continue;
        }
        ll x = sum(a,b, acc_ones);
        ll y = b-a+1 - x;
        debug(x);
        debug(y);
        debug(sum(a,b, acc_sum));
        if(sum(a,b, acc_sum) >= y+2*x){
            cout << "YES" << ln;
        }else{
            cout << "NO" << ln;
        }
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}