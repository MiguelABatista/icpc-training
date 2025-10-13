#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

string f(ll n){
    string s;
    while(n > 0){
        s.push_back('a'+n%26);
        n /= 26;
    }
    return s;
}

string trim(string s) {
    string ns;
    ll st = 0, nd = ((ll) s.size()) -2;
    while (s[st] == '0' && st < s.size()) st++;
    if (s.find('.') != s.npos) {
    while ((s[nd] == '0' || s[nd] == '.') && nd >= 0) nd--;

    }
    forn(i, st, nd + 1) {
        ns.push_back(s[i]);
    }
    return ns;
}

int main() {
    _;
    ll n; cin >> n;

    map<string, string> mp;
    mp[trim(".75")] = "standard";
    mp[trim("15")] = "nebuchadnezzar";
    mp[trim("12")] = "balthazar";

    string curr = "za";
    forn(i, 0, n) {
        string s; cin >> s;
        s = trim(s);
        if (mp.count(s)) {
            cout << mp[s] << ln;
        } else {
            mp[s] = curr;
            cout << curr << ln;
            
            if (curr.back() == 'z') {
                curr.push_back('a');
            } else {
                curr[((ll) curr.size()) - 1]++;
            }
        }
    }

    return 0;
}