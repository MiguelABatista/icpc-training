#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, k; cin >> n >> k;
    v64 p(n);
    v64 d(n);
    forn(i,0,n) cin >> p[i];
    forn(i,0,n) cin >> d[i];


    // forn(i,0,n) cout << p[i] << " \n"[i == n-1];
    // forn(i,0,n) cout << d[i] << " \n"[i == n-1];

    v64 esq(n, -1);
    v64 dir(n, -1);
    
    forn(i,1,n){
        ll t = d[i];
        for(ll j = i-1; j >= 0; j--){
            debug(i);
            debug(j);
            debug(t);
            t = (d[i]+(p[i] - p[j]))%k;
            debug(t);
            debug("AAAAAAAAA");

            if(t == d[j]){
                esq[i] = j;
                break;
            }
        }
    }

    forn(i,0,n-1){
        ll t = d[i];
        forn(j,i+1,n){
            // debug(i);
            // debug(j);
            // debug(t);
            t = (d[i]+(p[j] - p[i]))%k;
            // debug(t);
            // debug("AAAAAAAAA");
            if(t == d[j]){
                dir[i] = j;
                break;
            }
        }
    }

    ll q; cin >> q; 

    debug(n);
    // forn(i,0,n) cout << esq[i] << " \n"[i == n-1];
    // forn(i,0,n) cout << dir[i] << " \n"[i == n-1];

    forn(i,0,q){
        ll s; cin >> s; 
        ll idx = lower_bound(p.begin(), p.end(), s) - p.begin();
        if(idx == n){
            cout << "YES" << ln;
            continue;
        }

        ll t = (p[idx]-s)%k;

        pair<ll, char> curr = {-1, 'a'};

        forn(j, idx, n){
            if(t == d[j]){
                curr = {j, 'e'};
                break;    
            }

            if(j == n-1) break;
            
            t = (t+(p[j+1] - p[j]))%k;
        }

        set<pair<ll,char>> conj;
        conj.insert(curr);

        while(true){
            ll aux = curr.first;
            char dire = curr.second;
            // debug(aux);
            if(aux == -1){
                cout << "YES" << ln;
                break;
            }

            if(dire == 'e'){
                curr = {esq[aux], 'd'};
            }else{
                curr = {dir[aux], 'e'}; 
            }

       
            if(conj.find(curr) != conj.end()){
                cout << "NO" << ln;
                break;
            }
            conj.insert(curr);
        }
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}