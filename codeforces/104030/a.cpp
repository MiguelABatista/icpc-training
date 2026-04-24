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
       ll n; cin >> n;

       vector<float> v(n);
       forn(i,0,n) cin >> v[i];

       sort(v.begin(),v.end());

       bool explode = false;
       float worst = INF;

       forn(i,0,n){
        if(v[i]>i+1) {explode = true; break;}
        else worst = min(worst,v[i]/(i+1));
       }

       if(explode) cout << -1 << endl;
       else cout << worst << endl;

    return 0;
}
