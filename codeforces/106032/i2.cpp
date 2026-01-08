#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

#define debugv(v) trace({cout << #v": "; for (auto xa : v) cout<< xa << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll solve(ll n, ll x, v64& vec){
    ll resp = 0;
    if(x == 1){
        resp = (n*(n-1))/2;
        return resp;
    }
    v64 resto(x);

    forn(i,0,n){
        ll v = vec[i];
        if(((v*v) % x) == 0){
            resto[v%x]++;
        }
    }


    resp += (resto[0]*(resto[0]-1))/2;
    
    forn(i,1,x/2){
        resp += resto[i]*resto[x-i];
    }
    
    if(x%2 == 0){
        resp += (resto[x/2]*(resto[x/2]-1))/2;
    }else{
        resp += resto[x/2]*(resto[(x+1)/2]);
    }

    return resp;
}

int main(){
    _;
    ll n, x; cin >> n >> x;
    v64 vec(n);
    forn(i,0,n) cin >> vec[i];
    ll resp = 0;
    forn(i,0,n){
        forn(j,i+1,n){
            ll s = vec[i]+vec[j];
            ll p = vec[i]*vec[j];
            if((s%x == 0)&&(p%x == 0)) resp++;
        }
    }
    cout << resp << ln;
    return 0;
}