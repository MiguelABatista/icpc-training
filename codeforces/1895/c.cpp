#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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

v64 pot10(12);

void prep(){
    pot10[0] = 1;
    forn(i,1,12) pot10[i] = pot10[i-1]*10;
}

ll get_size(ll x){
    ll resp = 1;
    ll pot = 10;
    while(pot < x){
        resp++;
        pot *= 10;
    }
    return resp;
}

ll get_sum(ll x){
    ll resp = 0;
    while(x > 0){
        resp += x%10;
        x /= 10;
    }
    return resp;
}

bool testa(ll x, ll n){
    assert(n%2 == 0);
    ll k = n/2;
    ll x1 = x/pot10[k];
    ll x2 = x%pot10[k];
    return get_sum(x1) == get_sum(x2);
}

int main() {
    _;
    prep();
    ll n; cin >> n;

    vector<map<ll, ll>> freq(6);

    forn(i,0,n){
        ll x; cin >> x;
        freq[get_size(x)][x]++;
    }

    vector<p64> tenta = {
        {1,3}, 
        {1,5}, 
        {2,4}, 
        {3,1}, 
        // {3,5},
        {4,2},
        {5,1},
        // {5,3}
    };

    ll resp = 0;

    for(auto [a,b] : tenta){
        for(auto [ka, va] : freq[a]){
            for(auto [kb, vb] : freq[b]){
                ll curr = ka*pot10[b]+kb;
                if(testa(curr, a+b)) resp += va*vb;            
            }
        }
    }

    vector<map<ll,ll>> freqsum(6);
    
    forn(i,1,6){
        for(auto [k,v]: freq[i]){
            freqsum[i][get_sum(k)] += v;
        }
    }    

    forn(i,1,6){
        for(auto [k, v] : freqsum[i]){
            resp += v*v;
        }
    }


    // 3 5 abc defgh a+b+c+d = e+f+g+h => a+b+c = e+f+g+h-d
    map<ll, ll> aux;

    for(auto [k,v] : freq[5]){
        ll val = get_sum(k%pot10[4]);
        ll temp = k/pot10[4];
        val -= temp;
        aux[val] += v;
    }
    for(auto [k,v] : freq[3]){
        resp += v*aux[get_sum(k)];
    }
    aux.clear();

    // 5 3 abcde fgh a+b+c+d = e+f+g+h => a+b+c+d-e = f+g+h

    for(auto [k,v] : freq[5]){
        ll temp = k/10;
        ll val = get_sum(temp);
        val -= k%10;
        aux[val] += v;
    }
    for(auto [k,v] : freq[3]){
        resp += v*aux[get_sum(k)];
    }
    aux.clear();
    cout << resp << ln;
    return 0;
}
