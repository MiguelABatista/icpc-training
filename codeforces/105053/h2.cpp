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
const ll B = 31;
const ll INVB = 838'709'685;
const ll MOD = 1'000'000'009;

string cicla(string s, ll x){
    ll n = sz(s);
    string r(sz(s), ' ');

    forn(i,0,n){
        r[i] = s[(i+x)%n];
    }
    return r;
}

string rev(string s){
    ll n = sz(s);
    string r(sz(s), ' ');

    forn(i,0,n){
        r[i] = s[n-1-i];
    }
    return r;
}
int main() {
    _;
    string s; 
    cin >> s;

    ll m = sz(s);
    ll n; cin >> n; 
    
    v64 vec(n);
    

    forn(i,0,n){
        char c;
        cin >> c;
        if(c == 'I') continue;
        ll x; cin >> x;
        if(c == 'L') vec[i] = x;
        if(c == 'R') vec[i] = m-x; 
    }

    ll resp = 0;
    v64 ssssoma(n);
    v64 somaref(n);
    forn(i,0,n){
        forn(j,i, n){
            string r = s;
            ll ref = 0;
            forn(k,i,j+1){
                if(vec[k] == 0){
                    r = rev(r);
                    ref ^= 1;
                }
                else r = cicla(r, vec[k]);
                trace(cout << i << ":" << j << " " << s << " " << r << ln);
            }
            if(r == s){
                resp++;
                if(ref) somaref[j]++;
                else ssssoma[j]++;       
            }
        }
    }

    debugv(ssssoma);
    debugv(somaref);
    cout << resp << ln;
    return 0;
}
