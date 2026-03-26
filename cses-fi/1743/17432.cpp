#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    _;
    string s; cin >> s;
    ll n = sz(s);
    string resp = "ZZ";

    sort(s.begin(), s.end());

    do{
        bool valid = true;
        forn(i,0,n-1) if(s[i] == s[i+1]) valid = false;
        if(valid) resp = min(resp, s);
    }while(next_permutation(s.begin(), s.end()));
    
    if(resp == "ZZ"){
        cout << -1 << ln;
    }else{
        cout << resp << ln;
    }
    return 0;
}
