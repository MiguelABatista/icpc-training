#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ld eps = 1e-9;
const ll MAXN = 808;

ll n, m;
vector<ld> d(MAXN);
vector<p64> ar;
vector<ld> w;

bool bellman_ford(ll a){
    forn(i, 0, n) d[i] = INF;
    d[a] = 0;

    forn(i, 0, n+1){
        forn(j, 0, m){
            if(d[ar[j].second] > eps + d[ar[j].first] + w[j]){
                if(i == n) return 1;
                d[ar[j].second] = d[ar[j].first] + w[j];
            }
        }
    }

    return 0;
}

int main(){
    _; cin >> n >> m;
    forn(i, 0, m){
        ll a, b; cin >> a >> b;
        a--; b--;
        ar.push_back({a, b});

        ld x; cin >> x;
        x = -log(x);

        debug(x); 

        w.push_back(x);
    }

    bool num_da = bellman_ford(0);

    if(num_da){
        cout << "inadmissible" << ln;
    } else {
        cout << "admissible" << ln;
    }

    trace(forn(i, 0, n){
        cout << d[i] << " ";
    }
    cout << ln;);
    
    return 0;
}