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

string f(string gaba, string s){
    set<char> se;
    for(char c : gaba) se.insert(c);

    string resp(5, 'X');
    forn(i,0,5){
        if(s[i] == gaba[i]){
            resp[i] = '*';
            continue;
        }
        if(se.count(s[i])) resp[i] = '!';
    }
    return resp;
}

int main() {
    _;
    ll n; cin >> n;
    string s; cin >> s;
    n--;
    vector<string> vec(n); 
    forn(i,0,n) cin >> vec[i];

    map<string, ll> freq;
    forn(i,0,n){
        string aux = f(s,vec[i]);
        freq[aux]++;
    }
    freq[f(s,s)]++;

    ll q; cin >> q;
    while(q--){
        string r; cin >> r;
        cout << freq[r] << ln;
    }
    return 0;
}
