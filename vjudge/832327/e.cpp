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

void print(multiset<tuple<ll,ll,ll,ll>>& s){
    for (auto [x,y,tipo, qnt] : s){
        cout << -x << " " << -y << " " << tipo << " " << qnt << ln; 
    }

    cout << "-------------\n\n";
}

int main() {
    _;
    ll n; cin >> n;
    vector<pll> vec(n);
    forn(i,0,n) cin >> vec[i].second >> vec[i].first;
    sort(vec.begin(), vec.end());

    multiset<tuple<ll,ll,ll,ll>> s; // -x -y tipo qnt 

    forn(i,0,n){
        auto [z,f] = vec[i];
        multiset<tuple<ll,ll,ll,ll>> ns; // -x -y tipo qnt 
        
        for (auto [x,y,tipo, qnt] : s){
            x *= -1;
            y *= -1;
            
            if(f == 0){ 
                ns.insert({-x,-y,tipo, qnt}); 
                continue;
            }
            
            if(tipo == 0){ // isolado
                ll aux = min(f, qnt);
                // z >= x sempre
                ns.insert({-z,-x, 1, aux});
                f -= aux;
                qnt -= aux;
                if(qnt > 0) ns.insert({-x,-x, 0, qnt});
                continue;
            }
            
            ll aux = min(f/2, qnt);
            f -= 2*aux;
            qnt -= aux;
            
            // z > x > y por construcao
            ns.insert({-z,-x, 0, aux});
            ns.insert({-z,-y, 0, aux});
            if(qnt > 0) ns.insert({-x,-y, 0, qnt});
        }
        
    }
    
    ll resp = 0;
    for (auto [x,y,tipo, qnt] : s){
        x *= -1;
        y *= -1;
        resp += x*qnt;
    }
    cout << resp << ln;
    return 0;
}
