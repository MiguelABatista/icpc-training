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
ll w;

ll compare(ll i, ll j, vector<p64> & powers){
    ll saldo = 0;
    if(powers[i].first > powers[j].first) saldo++;
    if(powers[i].first < powers[j].first) saldo--;
    
    if(powers[i].second > powers[j].second) saldo++;
    if(powers[i].second < powers[j].second) saldo--;

    if(saldo > 0) return 1;
    if(saldo < 0) return -1;
    return 0;
}

ll simulate(vector<p64> & powers){
    ll n = powers.size();
    ll op = 0;

    ll active = n;
    v64 state(powers.size());
    while (active) {
        forn(i, 0, n) {
            if (state[i] != 0) continue;
            forn(j, i+1, n) {
                if (state[j] != 0) continue;
                ll cmp = compare(i, j, powers);
                op++;
                if (cmp == 0) continue;
                if (cmp == 1) {
                    state[j] = 2;
                } else {
                    state[i] = 2;
                    break;
                }
            }
            if (state[i] == 0) {
                state[i] = 1;
                active--;
            }
            forn(k, 0, n) {
                state[k] %= 2;
            }
        }
    }

    return op;
}

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l,r);
    return uid(rng);
}

void gen(ll n, vector<p64>& vec){    
    ll g = (2*n)/3;
    g++;
    vector<p64> vec(n);

    forn(i,0,g){
        vec[i] = {i+1, g-i};
    }

    forn(i,g,n){
        vec[i] = {i,i};
    }


    if(w < 5000){
        forn(i,0,n) vec[i].first += w;
    }else{
        forn(i,0,n) vec[i].first = w - vec[i].first;
    }
}

void print(vector<p64>& vec, ll n){
    cout << n << ln;
    forn(i,0,n){
        cout << vec[i].first << " " << vec[i].second << ln;
    }
}

int main() {
    _;
    ll n = 7;

    w = 0;

    while(n < 1001){
        vector<p64> vec(n);
        gen(n, vec);
        ll resp = simulate(vec);

        if(resp < (n*n*n)/20){
            debug(resp);
            debug((n*n*n)/20);

            print(vec, n);
            break;
        }
        cout << n << ln;
        n++;
    }

    return 0; 
}