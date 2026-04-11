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
ll fat[21];

void prep(){
    fat[0] = 1;
    forn(i,1,21) fat[i] = fat[i-1]*i;
}

void solve1(ll n, ll ord, v64& valid){
    if(n == 0) return;
    ll aux = fat[n-1];
    ll k = 0;
    while(aux*(k+1) < ord){
        k++;
    }
    ll cnt = 0;
    debug(k);
    debug(ord);
    debugv(valid);
    forn(i,0,sz(valid)){
        if(!valid[i])continue;
        if(cnt == k){
            cout << i+1 << " ";
            // cout << i+1 << "###\n";
            valid[i] = 0;
            break;
        }
        cnt++;
    }
    solve1(n-1, ord-(aux*k), valid);
}

ll solve2(ll n, v64 perm){
    if(n == 0) return 0;
    ll k = perm[0];
    ll resp = 0;
    resp = fat[n-1]*k;
    forn(i,0,n) if(perm[i] > k) perm[i]--;
    perm.erase(perm.begin());
    return solve2(n-1, perm) + resp;
}

int main() {
    _;
    prep();
    ll t; cin >> t;
    while(t--){
        ll x; cin >> x;
        if(x == 1){
            ll n, k; cin >> n >> k;
            v64 valid(n,1);
            solve1(n, k, valid);
            cout << ln;
        }else{
            ll n; cin >> n;
            v64 vec(n);
            forn(i,0,n) cin >> vec[i];
            forn(i,0,n) vec[i]--;
            cout << solve2(n, vec) + 1<< ln;
        }
    }

    return 0;
}
