#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll teto(ll x, ll y){
	return (x+y-1)/y;
}

int main(){
    _;

	ll k_max = 10;
	ll a_max = 10;
	ll b_max = 10;

	forn(k,2,k_max)
	forn(a,2, a_max)
	forn(b,2, b_max){
		if(k% a == 0 || k%b == 0) continue;
		if(teto(k*(b-1),b)% a == 0 || teto(k*(a-1),a)%b == 0) continue;
		ll aux1 = teto(teto(k*(a-1),a)*(b-1),b);
		ll aux2 = teto(teto(k*(b-1),b)*(a-1),a);
		if(aux1 != aux2){
			cout << a << " " << b << " " << k << ln;
		} 
	}
	
	
    return 0;
}