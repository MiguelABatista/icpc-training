#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAXN = 500'005;

ll parent[MAXN]; //Inicializar parent[i] = i
ll sz[MAXN];

ll find(ll x){
    ll pai = x;
    ll filho = x;
    ll aux;
    while( pai != parent[pai] ) pai = parent[pai];
    while( filho != parent[filho] ) {
        aux = parent[filho];
        parent[filho] = pai;
        filho = aux;
    }
    return pai;
}
  
void uni(ll x, ll y){
    ll rx = find(x);
    ll ry = find(y);
    if(rx == ry) return;
    if( sz[rx] < sz[ry]) swap(rx,ry);
    parent[ry] = rx;
    sz[rx] += sz[ry]; 
    return;
}

int main(){
    _;
    forn(i,0,MAXN+1) parent[i] = i;
    ll n, m;
    cin >> n >> m;
    
    return 0;
}