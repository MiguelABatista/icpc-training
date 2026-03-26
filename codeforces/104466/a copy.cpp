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

// const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll INF = 999;
const ld ep = 0.000'000'001;

map<char, map<ll, ll>> mp;
ll n = 3001;
ll mostra = 1'000;

ll calc(ll a, char f){
    ll t, q, c;

    if(a > n) return INF;
    if(a == 0) return -1;

    auto it = mp[f].find(a);
    if(it != mp[f].end()) return it->second;

    if(f == 'c'){
        t = (ll)(a*sqrt(3) + ep);
        q = (ll)(a*sqrt(2) + ep);
        c = a-1;
    }
    if(f == 't'){
        t = a-1;
        q = (ll)(a*sqrt(3)/(2+sqrt(3)) + ep);
        c = (ll)(a/(2*sqrt(3)) + ep);
    }
    if(f == 'q'){
        t = (ll)(a*(sqrt(6)-sqrt(2)) + ep);
        q = a-1;
        c = (a-1)/2;
    }
    ll resp = max({calc(t, 't'), calc(q, 'q'), calc(c, 'c')}) + 1;
    mp[f][a] = resp;    
    return resp;
}

int main(){
    _;

    vector<v64> mat(3, v64(n));

    map<ll, char> translator = {
        {0, 't'},
        {1, 'q'},
        {2, 'c'},
    };

    forn(i,0,n){
        forn(j,0,3){
            mat[j][i] = calc(i, translator[j]);
        }
    }

    forn(j,1,2){
        cout << translator[j] << " ";    
        forn(i,1,mostra+1) cout << setw(5) << mat[j][i] << " ";; cout << ln << ln << ln;;
    }

    cout << mat[0][mostra] << ln;
    
    return 0;
}