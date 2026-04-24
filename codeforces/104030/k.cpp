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
     ll n , m ;
     cin >> n >> m ;
     string b (m,'@');
     string k (m,'@');
     string a  (m,'@'); 
     forn(i,m-n,m) cin >> a[i];
     cin >> b ; 
     forn(i,m-n,m) { 
          k[i] = (b[i]-a[i]+26)%26 + 'a';
     }

     for(int i=m-n-1;i>=0;i--) {a[i]=k[i+n]; k[i]=(b[i]-a[i]+26)%26 + 'a';}
     //cout << k << ln;
     cout << a << endl;
     


     forn(i,0,n) {
          a[m-n+i] = k[i];
     }

     return 0;
}
