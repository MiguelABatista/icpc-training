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

// 0010011
int main() {
    _;
    ll n, k; cin >> n >> k;
    vll base, qnt;
    base.push_back(k+1);
    qnt.push_back(1);
    ll cnt = 1;
    while(base.back() < n && cnt < k){
        cnt++;
        base.push_back(k*(base.back()) + 1);
        qnt.push_back(k*qnt.back() + 1);
    }
    ll resp = 0;
    debugv(base);
    debugv(qnt);
    if(n > base.back()){
        resp = qnt.back() + n - base.back();
    }else{
        for(ll i = sz(base) - 1; i >= 0; i--){
            ll aux = n/base[i];
            resp += qnt[i]*aux;
            n %= base[i];
        }
    }

    cout << resp << ln;
    return 0;
}
