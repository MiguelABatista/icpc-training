#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;


int main() {
    _;
    ll n, k; cin >> n >> k;

    vector<vll> inv(2*k+1);

    forn(i,0,n){
        ll l, r; cin >> l >> r;
        inv[l+r].push_back(r-l);
    }
    
    ll resp = 0;
    forn(i,0,2*k+1){
        ll maxsize = min(i, 2*k-i);

        vector<pll> aux;
        if(i-2 >= 0) for(auto v : inv[i-2]) if(v+2 <= maxsize) aux.push_back({v+2,0});
        for(auto v : inv[i]) if(v < maxsize) aux.push_back({v,1});
        if(i+2 <= 2*k) for(auto v : inv[i+2]) if(v+2 <= maxsize) aux.push_back({v+2, 2});
        
        if(aux.empty()) continue;
        aux.push_back({maxsize, 3});
        
        
        vll best = {0,0,0};
        sort(aux.begin(), aux.end());
        debugm(aux);
        ll curresp = 0;
        ll j = 0;

        while(j < sz(aux)-1){
            best[aux[j].second] = aux[j].first - (aux[j].second == 1 ? 0 : 2);            
            curresp += max(best[1], min(best[0], best[2]))*((aux[j+1].first - aux[j].first)/2);
            j++;
        }

        debug(i); 
        debug(maxsize);  
        debug(curresp);
        trace(cout << ln;)
        resp += curresp;
    }
     
    trace(cout << ln << ln;)
    debug(resp);
    ll num = resp;
    ll dem = (k*(k+1))/2;
    debug(num);
    debug(dem);
    ll d = gcd(num,dem);
    cout << num/d << " " << dem/d << ln;
    return 0;
}