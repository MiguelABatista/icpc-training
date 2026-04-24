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
//     _;

    ll n,c,b; cin >> n >> c >> b;

    vector<ll> z(b);
    forn(i,0,b) cin >> z[i];

    vector<ll> v(n,0);
    ll s  = 0 ;

    ll j=z[0],p=1;
    
    while(s<c){
        if(s==c-1) break;
        if(j==z[p]-1){j++;p++;continue;}

        if(j>=n) break;
        
        v[j]=1;
		s+=2;
		j+=2;
        }
        
    

    j=z[0]-2;

    while(s<c){
        if(s==c-1) break;
        v[j]=1;
		s+=2;
		j-=2;
       
    }


    if(s==c){ 
        forn(i,0,n) cout << v[i];
             }
    else {
        v[0]=1; 
        forn(i,0,n) cout << v[i];
        } 

    cout << ln;
    return 0;
}
