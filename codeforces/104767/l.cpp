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

map<string, char> rule = {{"...", '.'},{"..X", '.'},{".X.", '.'},{".XX", '.'},{"X..", '.'},{"X.X", '.'},{"XX.", '.'},{"XXX", '.'}};

void walk(string& s){
    ll n = s.size(); string new_s(n, '.');

    forn(i, 1, n-1){
        string aux = {s[i-1]}; 
        aux = aux + s[i]+ s[i+1];
        new_s[i] = rule[aux];
    }

    cout << new_s.substr(1,n-2) << ln;
    s = new_s;
}

int main(){
    _; ll r, k; cin >> r >> k;
    string s; cin >> s;
    s.push_back('.');
    s.insert(0,".");
    
    for(auto x : rule){
        if(r%2 == 1) rule[x.first] = 'X';
        r /= 2;
    }

    forn(i, 0, k) walk(s);

    return 0;
}