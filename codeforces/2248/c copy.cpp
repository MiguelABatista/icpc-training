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

void solve(){
    ll n; cin >> n;
    vll vec(2*n);
    forn(i,0,2*n){
        cin >> vec[i];
        vec[i]--;
    }

    vector<pll> pos(n, {-1,-1});
    vector<tuple<ll,ll,ll>> aux;
    vector<bool> valid(2*n, true);

    forn(i,0,2*n){
        if(pos[vec[i]].first == -1) pos[vec[i]].first = i;
        else pos[vec[i]].second = i;
    }

    forn(i,0,n){
        aux.push_back({pos[i].second - pos[i].first + 1, pos[i].first, pos[i].second});
    }
    
    sort(aux.begin(), aux.end());
    ll resp = 0;
    for(ll i = n-1; i >= 0; i--){
        auto [l, a, b] = aux[i];
        if(!valid[a]) continue;
        if(!valid[b]) continue;
        resp += l*l;
        forn(j,a,b+1) valid[j] = 0;
    }

    forn(i,0,2*n) if(valid[i] == 1) resp++; 
    cout << resp << ln;
    trace(cout << "----------------\n\n";)
}

int main() {
    _;
    ll t; cin >> t;
    forn(i,0,t){
        solve();
    }
    return 0;
}
