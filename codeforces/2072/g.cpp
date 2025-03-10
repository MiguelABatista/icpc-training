#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
#define MOD 1'000'000'007

ll mult(ll a, ll b){
    return ((a%MOD)*(b%MOD))%MOD;
}

ll sum(ll a, ll b){
    return ((a%MOD)+(b%MOD))%MOD;
}

ll sub(ll a, ll b){
    return ((a%MOD) - (b%MOD) + MOD)%MOD;
}

ll pot(ll a, ll b){
    ll expo=1, prod=a;
    b = b % (MOD-1);
    a = a % MOD;

    while(b>=1){
        if(b%2 == 1) expo = mult(expo,prod);
        prod = mult(prod,prod);
        b = b/2;
    }
    
    return expo;
}

ll inv_mod(ll a){
    return pot(a, MOD-2);
}

ll rev(ll n, ll p){
    v64 num_p;
    ll curr_n = n;
    ll rev = 0;
    while(curr_n > 0){
        num_p.push_back(curr_n%p);
        curr_n /= p;    
    }
    
    ll tam = num_p.size();

    ll pot_p = 1;
    for(ll i = tam-1; i >= 0; i--){
        rev = sum(rev, mult(pot_p,num_p[i]) );
        pot_p = p*pot_p;
    }
    return rev;
}

ll inv_2 = inv_mod(2);
ll inv_6 = inv_mod(6);

ll cum_sum(ll t){
    return mult(mult(t,t+1), inv_2);
}

ll cum_sum_sq(ll t){
    return mult(mult(mult(t,t+1),2*t+1), inv_6);
}

void solve(){
    ll n; ll k;
    cin >> n >> k;
    ll resp = 0;
    
    if(n == 1){
        cout << (k-1)%MOD << ln;
        return;
    }

    if(k > n){
        resp = mult(n, (k - n));
        k = n;
    }

    ll c_sqrt_n = 1;

    while(c_sqrt_n*c_sqrt_n <= n) c_sqrt_n++;

    if( k < c_sqrt_n){
        forn(p,2,k+1){
            ll rev_n = rev(n,p);
            resp = sum(rev_n, resp);
        }
        cout << resp << ln;
        return;
    }

    forn(p,2,c_sqrt_n){
        ll rev_n = rev(n,p);
        resp = sum(rev_n, resp);
    }

    // sum from f_sqrt_n to k:
    // n*p + (1-p^2) * (n/p)

    for (int i = 1, la; i <= k; i = la + 1) {
        la = n / (n / i);
        if(i < c_sqrt_n) continue;
        if(la > k) la = k;
        //n / x yields the same value for i <= x <= la.

        ll curr_resp;
        curr_resp = mult(n, sub(cum_sum(la), cum_sum(i-1)));
        curr_resp = sum(curr_resp, mult(la-i+1, n/i));
        ll menos = mult(n/i, sub(cum_sum_sq(la), cum_sum_sq(i-1)));
        curr_resp = sub(curr_resp, menos);
        resp = sum(resp, curr_resp);
    }
    
    cout << resp << ln;
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}