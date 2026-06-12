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

ll mext(set<ll>& s){
    ll resp = 0;
    while (!s.empty()){
        ll x = *s.begin();
        s.erase(s.begin());
        if(x == resp) resp++;
        else break;
    }
    return resp;
}

void solve(){
    ll n; cin >> n;
    n *= 2;
    vll vec(n);
    forn(i,0,n) cin >> vec[i];
    ll z1 = -1;
    ll z2 = -1;

    forn(i,0,n){
        if(vec[i] == 0){
            if(z1 != -1) z2 = i;
            else z1 = i;
        }
    }

    set<ll> s1,s2,s3;

    ll p = 0;
    while(z1 + p < n && z1-p >= 0){
        if(vec[z1+p] != vec[z1-p]) break;    
        s1.insert(vec[z1 + p]);
        p++;
    }
    
    p = 0;
    while(z2 + p < n && z2-p >= 0){
        if(vec[z2+p] != vec[z2-p]) break;    
        s2.insert(vec[z2 + p]);
        p++;
        if(z2 + p >= n || z2-p < 0) break;
    }
    debug(z1);
    debug(z2);
    ll p1 = (z1 + z2)/2;
    ll p2 = (z1 + z2+1)/2;
    debug(p1);
    debug(p2);
    while(p1 >= 0 && p2 < n){
        if(vec[p1] != vec[p2]) break;
        s3.insert(vec[p1]);
        p1--;
        p2++;
    }

    ll resp = -1;
    resp = max(resp, mext(s1));
    resp = max(resp, mext(s2));
    resp = max(resp, mext(s3));
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
