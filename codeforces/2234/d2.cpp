#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve(){
    ll n, k;
    cin >> n >> k;
    string s1, s2; cin >> s1 >> s2;
    ll pot = 1ll<<k;
    vll v01(pot+1); v01[pot] = 1;
    vll v10(pot+1); v10[0] = 1;
    vll v11(pot+1); v11[pot] = 1; v11[0] = 1;
    set<ll> idx;
    set<ll> idx2;
    idx.insert(0);
    idx.insert(pot);

    ll lst = -1;
    ll curr=  -1;
    while (sz(idx) < pot){        
        for(auto x: idx){
            if(lst == -1){
                lst = x; 
                continue;
            }
            curr = (lst+x)/2;
            
            v01[curr] = v01[lst]^v01[x];
            v10[curr] = v10[lst]^v10[x];
            v11[curr] = v11[lst]^v11[x];
            
            lst = x;
            idx2.insert(x);
            idx2.insert(curr);
        }
        swap(idx,idx2);
    }
    debugv(v01);
    debugv(v10);
    debugv(v11);
    vll sum(pot+1);
    forn(i,0,pot+1){
        sum[i] = v01[i]+v10[i]+v11[i];
    }
    debugv(sum);

    debugv(v01);
    forn(i,0,pot+1){
        if(v01[i]) cout << bitset<5>(i) << ln;
    }
    debugv(v10);
    forn(i,0,pot+1){
        if(v10[i]) cout << bitset<5>(i) << ln;
    }
    debugv(v11);
    forn(i,0,pot+1){
        if(v11[i]) cout << bitset<5>(i) << ln;
    }
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
