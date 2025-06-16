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
    ll c1 = 0, c2 = 0, t = 0;
   
    ccnot(){}
   
    ccnot(ll x, ll y, ll z){
        c1 = x;
        c2 = y;
        t = z;
    }
    ccnot(ll x, ll z){
        c1 = x;
        c2 = x;
        t = z;
    }
    
};

void opera(ccnot op, ll& mask){
    if((mask&(1<<op.c1)) && (mask&(1<<op.c2))){
        mask ^= (1<<op.t);
    }
}

ll opera_tudo(vector<ccnot> ops, ll mask){
    for(auto op: ops) opera(op, mask);
    return mask;
}

int main(){
    _;
    ll n, m; cin >> n >> m;
    ll pot2 = (1<<n);
    vector<ccnot> vec(m);
    vector<v64> mat(pot2, v64(pot2, 0));

    forn(i,0,m){
        ll type; cin >> type;
        if(type == 1){
            ll c, t;
            cin >> c >> t;
            vec[i] = ccnot(c,t);
        }else{
            ll c1, c2, t;
            cin >> c1 >> c2 >> t;
            vec[i] = ccnot(c1,c2,t);
        }
    }

    forn(mask,0,pot2){
        ll output = opera_tudo(vec, mask);
        mat[mask][output] = 1;
    }

    forn(i,0,pot2){
        forn(j,0,pot2){
            cout << mat[i][j];
        }
        cout << ln;
    }
    return 0;
}