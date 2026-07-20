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
        vector<pll> aux;
        if(i-2 >= 0) for(auto v : inv[i-2]) aux.push_back({v+2,0});
        for(auto v : inv[i]) aux.push_back({v,1});
        if(i+2 <= 2*k) for(auto v : inv[i+2]) aux.push_back({v+2, 2});
        
        ll maxsize = min(i, 2*k-i);
        if(aux.empty()) continue;
        aux.push_back({INF, 0});
        
        
        vll best = {0,0,0};
        sort(aux.begin(), aux.end());
        debugm(aux);
        ll curresp = 0;
        ll j = 0;
        while(j < sz(aux)){
            best[aux[j].second] = aux[j].first - (aux[j].second == 1 ? 0 : 2);
            
            if(aux[j+1].first > maxsize-2){
                debug(1)
                curresp += max(best[1], min(best[0], best[2]))*(((maxsize-2) - aux[j].first)/2);
                break;
            }else{
                curresp += max(best[1], min(best[0], best[2]))*((aux[j+1].first - aux[j].first)/2);
            }
            j++;
        }
        while(j < sz(aux)){
            if(aux[j].first > maxsize) break;
            if(aux[j].second == 1 && aux[j].first == maxsize){
                j++;
                continue;
            };
            
            best[aux[j].second] = aux[j].first - (aux[j].second == 1 ? 0 : 2);
            j++;
        }
        debug(max(best[1], min(best[0], best[2])));
        debug(curresp);
        curresp += max(best[1], min(best[0], best[2]));
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