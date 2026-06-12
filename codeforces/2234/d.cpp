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


struct st{
    ll sem01 = 0;
    ll sem10 = 0;
    ll sem11 = 0;
};
map<ll, st> mp;

void prep(){
    mp[1] = (st){1,1,1};
    forn(k,2,31){
        st resp = {0,0,0};
        auto& x = mp[k-1];
        resp.sem01 = x.sem01 + x.sem11;
        resp.sem10 = x.sem11 + x.sem10;
        resp.sem11 = x.sem10 + x.sem01 - 1;

        mp[k]=resp;
    }
    
    // forn(k,1,31){
    //     cout << k << ln;
    //     auto& x = mp[k];
    //     cout << x.sem01 << " " << x.sem10 << " " << x.sem11 << ln;
    // }
}

void solve(){
    ll n, k; cin >> n >> k;
    string s, r;
    cin >> s >> r;
    ll c01 = 0;
    ll c10 = 0;
    ll c11 = 0;
    forn(i,0,n){
        if(s[i] == '1' && r[i] == '0') c01++;
        if(s[i] == '0' && r[i] == '1') c10++;
        if(s[i] == '1' && r[i] == '1') c11++;
    }

    ll resp = 0;
    auto x = mp[k];
    // sem 01
    resp += x.sem01*(n-(c10+c11))*(c10+c11);
    resp += x.sem10*(n-(c01+c11))*(c01+c11);
    resp += x.sem11*(n-(c10+c01))*(c10+c01);
    cout << resp << ln;
}

int main() {
    _;
    prep();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
