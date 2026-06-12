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

// 10! = 3'628'800

void solve(){
    ll n, m; cin >> n >> m;
    vector<vll> vec(n, vll(m));
    vector<vll> invvec(n, vll(m));

    forn(i,0,n){
        forn(j,0,m){
            cin >> vec[i][j];
            vec[i][j]--;
        }
        forn(j,0,m) invvec[i][vec[i][j]] = j;
    }

    sort(invvec.begin(), invvec.end());

    forn(i,0,n){debugv(vec[i]);};
    trace(cout << "\n--------------\n\n";)
    forn(i,0,n){debugv(invvec[i]);};
    trace(cout << "\n--------------\n\n";)

    forn(x,0,n){
        vll& v = vec[x];
        // vll gaba(m);
        // forn(i,0,m) gaba[v[i]] = i;
        // vll invgaba(m);
        // forn(i,0,m) invgaba[gaba[i]] = i;

        vll aux(m, -1);
        ll resp = 0;
        
        debugv(v);
        // debugv(gaba);
        // debugv(invgaba);
        
        forn(i,0,m){
            aux[i] = v[i]; 
            debugv(aux);   
            auto it = lower_bound(invvec.begin(), invvec.end(), aux);
            bool f = false;
            
            if(it == invvec.end()) break;

            vll& tenta = *it;

            forn(j,0,m){
                if(aux[j] != -1 && aux[j] != tenta[j]){
                    f = true;
                    break;
                }
            }
            if(f) break;
            resp++;
        }
        cout << resp << " \n"[x==n-1];
        trace(cout << "\n--------------\n\n";)
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
