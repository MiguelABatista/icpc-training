#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> p64;
typedef vector<int> v64;
typedef vector<int> v32;
typedef vector<v64> vv64;
typedef vector<p64> vp64;

#define forn(i, s, e) for(ll i = s; i < e; i++)
#define ln "\n"
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll) (x).size())
#define dbg(x) cout << #x << " = " << x << ln


void solve(){
    ll n; cin >> n;
    ll resp;
    ll a;
    v64 vec(n);
    forn(i,0,n){
        cin >> vec[i];
    }
    sort(vec.begin(),vec.end());

    resp = vec[0];
    forn(i,1,n){
        //cout << resp << ' ';
        resp = (resp+vec[i])/2;
    }
    //cout << ln;
    cout << resp << ln;
}

int main(){
    fast_cin();
    ll t; cin >> t;
    while(t){
        solve();
        t--;
    }
}