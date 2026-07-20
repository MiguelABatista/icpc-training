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

map<string, ll> power = {
    {"Shadow", 6},
    {"Gale", 5},
    {"Ranger", 4},
    {"Anvil", 7},
    {"Vexia", 3},
    {"Guardian", 8},
    {"Thunderheart", 6},
    {"Frostwhisper", 2},
    {"Voidclaw", 3},
    {"Ironwood", 3},
    {"Zenith", 4},
    {"Seraphina", 1},
};

ll location(bool is_center){
    ll n;

    ll p1 = 0;

    ll num_seraphina = 0;
    ll num_zenith = 0;
    ll num_thunderheart = 0;

    cin >> n;
    forn(i, 0, n){
        string s; cin >> s;
        num_seraphina += (s == "Seraphina");
        num_zenith += (s == "Zenith");
        num_thunderheart += (s == "Thunderheart");

        p1 += power[s];
    }

    if(is_center) p1 += 5*num_zenith;
    p1 += (n-1)*num_seraphina;
    if(n == 4) p1 += 6*num_thunderheart;
    return p1;
}

int main() {
    _;
    ll win1 = 0, win2 = 0;
    ll tot1 = 0, tot2 = 0;
    
    forn(i, 0, 3){
        ll p1 = location(i == 1);
        ll p2 = location(i == 1);
        tot1 += p1;
        tot2 += p2;

        win1 += (p1 > p2);
        win2 += (p2 > p1);
    }

    if(win1 > win2) cout << "Player 1" << ln;
    else if(win1 < win2) cout << "Player 2" << ln;
    else{
        if(tot1 > tot2) cout << "Player 1" << ln;
        else if (tot2 > tot1) cout << "Player 2" << ln;
        else cout << "Tie" << ln;
    }


    return 0;
}
