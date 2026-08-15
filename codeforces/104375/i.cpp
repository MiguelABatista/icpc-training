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
    ll  n, k; cin >> n >> k;
    string s; cin >> s;
    s = s + s;
    vll vec(2*n);
    forn(i,0,n) vec[i] = vec[i+n] = s[i]-'a';

    vll freq(26);

    ll p1 = 0;
    while(p1 < 2*n && vec[p1] == vec.back()) p1++;
    if(p1 == 2*n){
        cout << -1 << ln;
        return 0;
    }
    ll p2 = p1;
    ll best = 0;
    ll bp1 = -1;
    ll bp2 = -1;

    while(p1 < 2*n && p2 < 2*n){
        if(p1 > 0 && vec[p1] == vec[p1-1]){
            freq[vec[p1]]--;
            p1++;
            continue;
        }
        if(p2 > 0 && vec[p2] == vec[p2-1]){
            freq[vec[p2]]++;
            p2++;
            continue;
        }
        if(p2 - p1 > n){
            freq[vec[p1]]--;
            p1++;
            continue;
        }

        bool sc = false;
        forn(c,0,26) if(freq[c] > k){
            freq[vec[p1]]--;
            p1++;
            sc = true;
            break;;
        }
        if(sc) continue;

        if(best < p2-p1){
            bp1 = p1;
            bp2 = p2;
            best = p2-p1;
        }

        debug(p1);
        debug(p2);
        debugv(freq);
        freq[vec[p2]]++;
        p2++;
    }
    if(best > 0){
        cout << best << ln;
        forn(i,bp1,bp2) cout << s[i];; cout << ln;
    }else{
        cout << -1 << ln;
    }
    return 0;
}
