#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())

int main(){
    ll t , c, k; cin >> t >> c >> k;

    cout << min(c,t*k) << "\n";
}