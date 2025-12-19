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
#define troca(x) {if(x == '0') x = '1'; else x = '0';}

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    string s; cin >> s;
    ll n = sz(s);

    ll first_zero = 0;

    while(first_zero < n-1 && s[first_zero] == '1') first_zero++;
    ll tam = n - first_zero;

    vector<pair<string, ll>> vec;

    forn(i,0,n-tam+1) if(s[i] == '1'){
        string s2 = s;
        forn(j,0,tam){
            if(s[i+j] == '1') troca(s2[n-tam+j]);
        }
        vec.push_back({s2, i});
    }
    sort(vec.rbegin(), vec.rend());

    cout << 1 << " " << n << " " << vec[0].second+1 << " " << vec[0].second+tam << ln;
    trace(
        for(auto x: vec) cout << x.first <<  " " << x.second << ln;
        cout << "---------------\n\n";
    );
}

int main(){
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}