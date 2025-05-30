#include <bits/stdc++.h>
typedef long long ll;
#define forn(i,s,e) for(ll i = (s); i < (e); i++)
using namespace std;

mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());

ll uniform(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    ll n = 10;
    cout << n << "\n";
    cout << uniform(1,100) << "\n";

    forn(i,0,n){
        cout << uniform(1,100) << " ";
    }
    cout << "\n";
}