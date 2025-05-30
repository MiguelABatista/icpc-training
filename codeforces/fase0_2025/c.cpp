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

struct ccnot{
    ll c1, c2, t;
    ccnot(){
        c1 = 0;
        c2 = 0;
        t = 0;
    }
    ccnot(ll x, ll y, ll z){
        c1 = x;
        c2 = y;
        t = z;
    }
    ccnot(ll x, ll y){
        c1 = x;
        c2 = x;
        t = y;
    }
};

void aplica(bitset<8>& estado, ccnot op){
    bool troca = estado[op.c1] & estado[op.c2];
    estado[op.t] = troca ^ estado[op.t];
}

void aplica_tudo(bitset<8>& estado, vector<ccnot>& ops){
    for(auto op : ops){
        aplica(estado, op);
    }
}

int main(){
    _;

    ll n, m; cin >> n >> m;

    vector<ccnot> vec(m);

    forn(i,0,m){
        ll t; cin >> t;
        if(t == 1){
            ll aux1; cin >> aux1;
            ll aux2; cin >> aux2;
            vec[i] = ccnot(aux1, aux2);
        }else{
            ll aux1; cin >> aux1;
            ll aux2; cin >> aux2;
            ll aux3; cin >> aux3;
            vec[i] = ccnot(aux1, aux2, aux3);
        }
    }

    ll pot2 = (1<<n);

    vector<v64> mat(pot2, v64(pot2, 0));

    forn(estado_ll,0, pot2){
        bitset<8> estado_bs = bitset<8>(estado_ll);
        aplica_tudo(estado_bs, vec);
        ll aux = estado_bs.to_ullong();
        mat[estado_ll][aux] = 1;
    } 

    forn(i,0,pot2){
        forn(j,0,pot2){
            cout << mat[i][j];
        }
        cout << ln;
    }
    return 0;
}