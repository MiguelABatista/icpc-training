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

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n; cin >> n;
    v64 vec(n);
    ll nzero = 0;
    ll sum = 0;
    
    v64 vmais(2);
    v64 vmenos(2);

    forn(i,0,n){
        cin >> vec[i];
        sum += vec[i];
        if(vec[i] != 0) nzero++;
    }
    
    if(nzero%2 == 1){
        cout << -1 << ln;
        return;
    }

    if(sum == 0){
        cout << n << ln;
        forn(i,0,n) cout << i+1 << " " << i+1 << ln;
        return;
    }

    if(sum < 0){
        forn(i,0,n) vec[i] *= -1;
        sum *= -1;
    }

    vector<p64> resp;
    
    forn(i,0,n){
        if(sum == 0){
            forn(j,i,n){
                resp.push_back({j,j});
            }
            break;
        }
        if(i == n-1){
            resp.push_back({i,i});
            break;
        }
        if(vec[i+1] == 1){
            resp.push_back({i,i+1});
            sum-= 2;
            i++;
            continue;
        }
        resp.push_back({i,i});
    }

    if(sum != 0){
        cout << -1 << ln;
        return;
    }

    cout << sz(resp) << ln;
    for(auto p: resp){
        cout << p.first+1 << " " << p.second + 1 << ln;
    }
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}