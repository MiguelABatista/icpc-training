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

pll compare(vll &d1, vll &d2){
    ll win = 0, tot = 0;
    forn(i, 0, 6)
    forn(j, 0, 6){
        if(d1[i] != d2[j]) tot++;
        if(d1[i] > d2[j]) win++;
    }

    return {win, tot};
}

int main() {
    _;
    vector<vll> d(3, vll(6));

    forn(i, 0, 6) cin >> d[0][i];
    forn(i, 0, 6) cin >> d[1][i];
    forn(i, 0, 6) cin >> d[2][i];

    forn(i, 0, 3){
        vll w, t;
        forn(j, 0, 3){
            if(i == j) continue;
            auto [w0, t0] = compare(d[i], d[j]);
            w.push_back(w0);
            t.push_back(t0);
        }

        if(w[0] == 0 && t[0] == 0) continue;
        if(w[1] == 0 && t[1] == 0) continue;

        if(w[1]*t[0] < w[0]*t[1]){
            swap(w[1], w[0]);
            swap(t[1], t[0]);
        }

        trace(cout << w[0] << " " << t[0] << ln;)

        if(2*w[0] >= t[0]){
            cout << i+1 << ln;
            return 0;
        }
    }

    cout << "No dice" << ln;

    return 0;
}
