#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
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

int main() {
    _; ld d; cin >> d;
    ll n; cin >> n;
    vector<line> caminho;

    pt last;
    forn(i, 0, n){
        pt a; cin >> a;
        if(i > 0){
            caminho.push_back(line(last,a));
        }
        last = a;
    }
    
    ll ind_alice = 0, ind_bob = 0;
    pt alice = caminho[0].p;
    pt bob = walk(d, caminho, alice, ind_bob);

    while(bob != caminho[n-1].q){
        dist1 = disst(alice, caminho[ind_alice].q);
        dist2
    }

    return 0;
}