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

int main() {
    _;
    ll nmax = 30;
    vll resp;

    resp.push_back(1);

    forn(n,nmax-1,nmax){
        if(n%2 == 0) continue;
        vll v;
        forn(i,1,n+1){
            forn(j,1,n+1){
                cout << setw(4) << i*j << " ";
                v.push_back(i*j);
            }
            cout << ln;
        }
        sort(v.begin(), v.end());
        cout << n << " " << v[(n*n)/2+1] << " " << v[(n*n)/2+1]/n << ln;
        resp.push_back(v[(n*n)/2+1]);
    }

    ll cnt = 1;
    ll lst = 0;
    
    forn(i,0,sz(resp)){
        cout << cnt << " " << resp[i] << " " << resp[i]/cnt << ln;
        lst = resp[i];
        cnt += 2;
    }
    return 0;
}
