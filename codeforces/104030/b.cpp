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

const ll INF = 0x3f3f3f3f3f3f3f3fll;
void bfs (vll sources , vector<vll>& adj_list,vector<vll>& inv_adj_list , vll& cost) {
    queue<ll> q;
    for(ll s : sources) {
        q.emplace(s);
        while(!q.empty()) {
            for (ll n : adj_list[q.front()]) {
                q.push(n);
                cost[n]+=cost[q.front()];
            }
            q.pop();
        }
    }

}    
int main() {
    _; 

    ll n ; 
    cin >> n;
    vector<vector<ll>> adj_list(n,vector<ll>());
    vll dep_list(n);
    vll cost_list(n,1);
    vll sources ; 
    vll v_costs(n);
    vector<vector<ll>> inv_adj_list(n,vector<ll>());
    forn(i,0,n) {
        ll v_cost , v_dep ; 
        cin >> v_cost >> v_dep ;
        v_costs[i] = v_cost;
        if (v_dep==0) 
            sources.push_back(i); 
        forn(j,0,v_dep) {
            ll dep ;
            cin >> dep;
            adj_list[i].push_back(--dep);
            inv_adj_list[dep].push_back(i);
        }
    }
    ll hstCostLwsValue;
    ll value=0;
    forn(i,0,n) {
        if (cost_list[i]>cost_list[hstCostLwsValue]) {
            hstCostLwsValue = i;
            value = v_costs[i];
        } 
        else if (cost_list[i]==cost_list[hstCostLwsValue]) {
            if (v_costs[hstCostLwsValue]<v_costs[i])  {
                hstCostLwsValue = i ;
                value=v_costs[i];
            }
        }
    }




    return 0;
}
