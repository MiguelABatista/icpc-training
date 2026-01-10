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

int main(){
    _;
    ll n, t, k; cin >> n >> t >> k;
    vector<pair<ll, string>> vec(n);

    forn(i,0,n) cin >> vec[i].second >> vec[i].first;

    sort(vec.rbegin(), vec.rend());

    ll sum = 0;
    vector<string> v;
    forn(i,0,k){
        sum += vec[i].first;
        v.push_back(vec[i].second);
        if(sum >= t) break;
    }

    if(sum < t){
        cout << "impossible" << ln;
        return 0;
    }

    cout << sz(v) << ln;
    forn(i,0,sz(v)) cout << v[i] << ", YOU ARE FIRED!" << ln;;
    return 0;
}