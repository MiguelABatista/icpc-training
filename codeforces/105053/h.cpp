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

p64 get_valid(string s){
    ll n = sz(s);   
    ll curr_hash = 0;
    ll pot = 1;
    forn(i,0,n){
        curr_hash = (curr_hash+pot*(s[i]-'a'))%MOD;
        pot = (pot*B)%MOD;
    }
    pot = (pot*INVB)%MOD;
    ll orig_hash = curr_hash;
    
    ll d = 0;
    do{
        curr_hash = (curr_hash - (s[d]-'a') + MOD)%MOD;
        curr_hash = (curr_hash*INVB)%MOD;
        curr_hash = (curr_hash + pot*(s[d]-'a'))%MOD;
        d++;
    } while(orig_hash != curr_hash);
    
    reverse(s.begin(), s.end());
    curr_hash = 0;
    pot = 1;
    forn(i,0,n){
        curr_hash = (curr_hash+pot*(s[i]-'a'))%MOD;
        pot = (pot*B)%MOD;
    }
    pot = (pot*INVB)%MOD;
    
    ll r = 0;
    while(orig_hash != curr_hash && r < n){
        curr_hash = (curr_hash - (s[r]-'a') + MOD)%MOD;
        curr_hash = (curr_hash*INVB)%MOD;
        curr_hash = (curr_hash + pot*(s[r]-'a'))%MOD;
        r++;
    }
    if(r == n) return {d, INF};
    r = d - r;
    return {d,r};
}

int main() {
    _;
    string s; 
    cin >> s;
    ll m = sz(s);
    ll n; cin >> n;
    
    v64 vec(n);
    
    auto [d, r] = get_valid(s);

    forn(i,0,n){
        char c;
        cin >> c;
        if(c == 'I') continue;
        ll x; cin >> x;
        if(c == 'L') vec[i] = x;
        if(c == 'R') vec[i] = m-x; 
    }
    
    ll sgn = 1;
    forn(i, 0, n){
        if(vec[i] == 0) sgn *= -1;
        vec[i] = vec[i]*sgn;
    }

    v64 acc(n);

    forn(i,0,n) acc[i] = (d + (vec[i] + (i == 0 ? 0 : acc[i-1]))%d)%d;
    
    vector<v64> freq(2, v64(d,0));
    freq[0][0] = 1;
    ll paridade = 0;

    ll resp = 0;
    forn(i,0,n){
        if(vec[i] == 0) paridade ^= 1;

        resp += freq[paridade][acc[i]];

        if(r != INF){
            if(paridade) resp += freq[0][(acc[i] - r + d)%d];
            else resp += freq[1][(acc[i] + r + d)%d];             
        }
        freq[paridade][acc[i]]++;
    }
 
    cout << resp << ln;
    return 0;
}
