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


mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int solve(){
    ll n; n = 3;
    ll t = (n*(n-1))/2 + 1;

    vector<pair<ll, p64>> edges;

    forn(i,0,n){
        forn(j,i+1, n){
            edges.push_back({uniform(0,1'000'000'000), {i, j}});
        }
    }
    sort(edges.begin(), edges.end());

    v64 vec(t);
    vec[0] = uniform(0,n-1);
    forn(i,1,t){
        bool bo = false;
        forn(j,0,sz(edges)){
            ll a = edges[j].second.first;
            ll b = edges[j].second.second;
            if(vec[i-1] == a){
                bo = true;
                // cout << a+1 << " " << b+1 << ln;
                vec[i] = b;
                edges.erase(edges.begin() + j);
                break;
            }
            if(vec[i-1] == b){
                bo = true;
                // cout << b+1 << " " << a+1 << ln;
                vec[i] = a;
                edges.erase(edges.begin() + j);
                break;
            }
        }
        if(!bo) return false;
    }
    vec[t-1] = (vec[0]+1)%n;
    ll p = uniform(1,t-1);
    ll q = uniform(1,t-p);

    cout << n << ln;

    cout << p << " ";
    forn(i,0,p) cout << vec[i]+1 << " ";; cout << ln;
    cout << q << " ";
    forn(i,0,q) cout << vec[t-q+i]+1 << " ";; cout << ln;

    forn(i,0,t) cout << vec[i]+1 << " ";
    cout << ln;
    return true;
}

int main(){
    while(!solve()) {
    };
}