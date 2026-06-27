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

void add(string &s, ll ind, char c){
    debug("add");
    debug(s);
    debug(ind);
    debug(c);
    assert(sz(s) >= ind);
    if(sz(s) == ind) s.push_back(c);
    else s.insert(s.begin()+ind, c);
}

void fill(string s, string ddd9, set<string>& resp, ll ind){
    debug(ddd9);
    debug(s);
    debug(ind);
    trace(cout << ln;)
    if(sz(s) == 8) resp.insert(ddd9+s);
    if(sz(s) < ind) return;
    if(ind == 8){
        return;
    }

    string aux1 = s, aux2 = s;
    
    // aux1.insert(aux1.begin()+ind, '1');
    add(aux1, ind, '1');
    // aux2.insert(aux2.begin()+ind, '9');
    add(aux2, ind, '9');

    if(sz(aux1) <= 8) fill(aux1, ddd9, resp, ind+1);
    if(sz(aux2) <= 8) fill(aux2, ddd9, resp, ind+1); 
    if(sz(s) <= 8) fill(s, ddd9, resp, ind+1);
}

int main() {
    _;
    string ss; cin >> ss;
    if(sz(ss) > 11){
        cout << 0 << ln;
        return 0;
    }

    if(ss[0] != '1'){
        // ss.insert(ss.begin(), '1');
        add(ss, 0, '1');
    }
    debug(ss);
    if(sz(ss) > 11){
        cout << 0 << ln;
        return 0;
    }

    set<string> resp;

    forn(ddd,1,10){
        char c = '0'+ddd;
        string s = ss;

        if(s[1] != c){
            if(c == '1' || c == '9') add(s, 1, c);
            else continue;
        }
        if(s[2] != '9') add(s, 2, '9');
        fill(s.substr(3,sz(s)), s.substr(0,3), resp, 0);
    }

    cout << sz(resp) << ln;
    for(auto s : resp){
        cout << s << ln;
    }
    return 0;
}