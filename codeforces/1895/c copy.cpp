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


int main() {
    _;
    ll n; cin >> n;
    vector<v64> vec(6);
    vector<map<ll,ll>> freq(6);
    
    forn(i,0,n){
        ll x; cin >> x;
        vec[get_size(x)].push_back(x);
    }

    forn(i,1,6){
        for(ll x: vec[i]){
            freq[i][get_sum(x)]++;
        }
    }
    
    ll resp = 0;


    // 1 1
    // 2 2
    // 3 3
    // 4 4
    // 5 5
    forn(i,1,6){
        for(auto [k, v] : freq[i]){
            resp += v*v;
        }
    }

    // 1 3 a bcd a+b = c+d => a = c+d-b 
    map<ll, ll> aux;
    for(ll x: vec[3]){
        ll val = x%10;
        x /= 10;
        val += x%10;
        x /= 10;
        val -= x%10;
    }
    for(ll x: vec[1]){
        resp += aux[get_sum(x)];
    }
    aux.clear();
    
    // 1 5 a bcdef a+b+c = d+e+f => a = d+e+f - b - c 
    // 5 1 bcdef a a+e+f = b+c+d => a = d+e+f - b - c 
    map<ll, ll> aux;
    for(ll x: vec[3]){
        ll val = x%10;
        x /= 10;
        val += x%10;
        x /= 10;
        val -= x%10;
    }
    for(ll x: vec[1]){
        resp += aux[get_sum(x)];
    }
    // 1 5
    // 2 4
    // 3 5


    return 0;
}
