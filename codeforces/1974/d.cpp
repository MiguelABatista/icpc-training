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

map<char, ll> dict = {
    {'N' , 0},
    {'S' , 1},
    {'W' , 2},
    {'E' , 3}
};

void solve(){
    ll n; cin >> n;
    string s; cin >> s;

    vll tot(4), r(4), h(4);

    forn(i,0,n) tot[dict[s[i]]]++;


    if(abs(tot[0]-tot[1])%2 == 1 || abs(tot[2]-tot[3])%2 == 1){
        cout << "NO" << ln;
        return;
    }

    if(tot[0]%2 == 1){
        r[0]++;
        r[1]++;
        tot[0]--;
        tot[1]--;
    }
    if(tot[2]%2 == 1){
        h[2]++;
        h[3]++;
        tot[2]--;
        tot[3]--;
    }

    forn(i,0,4){
        r[i] += tot[i]/2;
        h[i] += tot[i]/2;
    }

    bool b1 = true;
    bool b2 = true;

    forn(i,0,4){
        if(r[i] > 0) b1 = false;
        if(h[i] > 0) b2 = false;
    }
    
    if(b1 || b2){
        cout << "NO" << ln;
        return;
    }

    string resp(n, '#');

    forn(i,0,n){
        ll idx = dict[s[i]];
        if(r[idx] > 0){
            resp[i] = 'R';
            r[idx]--;
        }else{
            resp[i] = 'H';
            h[idx]--;
        }
    }
    cout << resp << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
