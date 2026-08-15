#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    vll v(n), nx(n), pv(n);
    ll ini = 0;
    vector<vll> pos(n);

    forn(i, 0, n){
        cin >> v[i];
        v[i]--;
        pos[v[i]].push_back(i);

        pv[i] = i-1;
        nx[i] = i+1;
    }

    forn(i, 0, n) reverse(pos[i].begin(), pos[i].end());

    ll op = 0;
    ll minimo = 0;

    auto myerase = [&](ll i){
        ll prev = pv[i];
        ll next = nx[i];
        
        pos[v[i]].pop_back();
        if(i == ini) ini = nx[ini];

        if(prev != -1) nx[prev] = next;
        if(next != n) pv[next] = prev;
    };

    while(ini != n){
        op++;

        debugv(nx);
        debugv(pv); 
        debug(ini);

        if(nx[ini] == n) break;

        if(v[nx[ini]] == v[ini]){
            myerase(ini);
            myerase(ini);
            continue;
        }

        while(pos[minimo].empty()) minimo++; 
        
        ll del = pos[minimo].back(); 
        myerase(del);
    }

    cout << op << ln;
}

int main(){
    _; ll t; cin >> t;
    while(t--) solve();
    return 0;
}