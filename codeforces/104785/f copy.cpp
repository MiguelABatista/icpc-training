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
const ll MAXN = 3'000'005;
const ll MAXLOG = 21;

vector<v64> sparse(MAXN, v64(MAXLOG, -1));
ll n, c;

void build(){
    forn(j,1,MAXLOG){
        forn(i,0,2*n){
            ll aux = sparse[i][j-1];
            sparse[i][j] = aux == -1 ? -1 : sparse[aux][j-1]; 
        }
    }
}

ll bs(ll start, ll end){
    ll cnt = MAXLOG-1;
    ll pot2 = 1ll<<cnt;
    // debug(start);
    // debug(end);

    while(pot2 > 0){
        ll aux = sparse[start][cnt];
        if(aux == -1) aux = 2*n;
        if(aux == end){
            return pot2;
        }
        if(aux < end){
            return pot2 + bs(sparse[start][cnt], end);
        }
        cnt--;
        pot2 >>= 1;
    }    
    return 1;
}

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
    uniform_int_distribution<ll> uid(l,r);
    return uid(rng);
}

int solve() {    
    
    n = 1'000'000;
    c = uniform(1,1000);
    
    v64 vec(2*n); 
    v64 acc(2*n); 

    forn(i,0,n){
        vec[i] = uniform(1,1000);
        vec[i+n] = vec[i];
    }

    // cin >> n;
    // cin >> c;
    // forn(i,0,n){
    //     cin >> vec[i];
    //     vec[i+n] = vec[i];
    // }

    acc[0] = vec[0];
    forn(i,1,2*n) acc[i] = acc[i-1] + vec[i];

    ll p1 = 0;
    ll p2 = 0;

    while(p1 < 2*n && p2 < 2*n){
        ll delta = acc[p2]- (p1 == 0 ? 0 : acc[p1-1]);
        // debug(p1);
        // debug(p2);
        // debug(delta);
        if(delta < c) {
            p2++;
            continue;
        }

        sparse[p1][0] = p2+1;
        p1++;
    }

    build();
    // forn(i,0,2*n) cout << setw(3) << i << " ";; cout << ln;
    // forn(i,0,2*n) cout << setw(3) << vec[i] << " ";; cout << ln;
    // cout << ln;
    // forn(i,0,2*n) cout << setw(3) << sparse[i][0] << " ";; cout << ln;
    // forn(i,0,2*n) cout << setw(3) << sparse[i][1] << " ";; cout << ln;
    // forn(i,0,2*n) cout << setw(3) << sparse[i][2] << " ";; cout << ln;
    // cout << ln;
    // forn(i,0,n) {
    //     cout << setw(3) << bs(i, i+n) << " ";; cout << ln;
    // }

    forn(i,0,n) cout << bs(i,i+n) - 1 << " ";; cout << ln;
    return 0;
}

int main(){
    _;
    ll i = 0;
    while(true){
        cout << i << ln;
        solve();
        i++;
    }
}