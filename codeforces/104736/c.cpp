#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

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

const ll SQRTN = 500;

void solvegrande(ll n, ll k){
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    ll resp = 0;
    for(ll l = k; l <= n; l += k){
        ll t = l/k;
        ll amt = 0;
        vll freq(k+1);

        forn(i,0,l) freq[vec[i]]++;
        
        forn(i,0,k+1) if(freq[i] == t) amt++;
        if(amt == k) resp = max(resp, l);
        forn(i,l,n){
            ll j = i-l;
            if(freq[vec[j]] == t) amt--;
            if(freq[vec[j]] == t+1) amt++;
            freq[vec[j]]--;
            freq[vec[i]]++;
            if(freq[vec[i]] == t) amt++;
            if(freq[vec[i]] == t+1) amt--;
            if(amt == k) resp = max(resp, l);
        }
    }
    cout << resp << ln;
}

void solvepequeno(ll n, ll k){
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    forn(i,0,n) vec[i]--;
    map<vll, vll> mp;    
    vll freq(k);
    mp[freq].push_back(-1);   
    forn(i,0,n){
        freq[vec[i]]++;
        bool ok = false;
        forn(j,0,k) if(freq[j] == 0) ok = true;
        if(!ok) forn(j,0,k) freq[j]--;
        mp[freq].push_back(i);
    }
    ll resp = 0;
    for(auto& [ke,v] : mp){
        debugv(ke);
        debugv(v);
        ll mi = *min_element(v.begin(), v.end());
        ll ma = *max_element(v.begin(), v.end());
        resp = max(resp, ma-mi);
    }   
    cout << resp << ln;
}

int main() {
    _;
    ll n, k; cin >> n >> k;
    if(k > SQRTN) solvegrande(n,k);
    else solvepequeno(n,k);
    return 0;
}
