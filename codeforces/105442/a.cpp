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

// 345
// 2*6
// 107

map<pair<ll,ll>, char> mp{
    {{0,1} , 'a'},
    {{0,2} , 'b'},
    {{0,3} , 'c'},
    {{0,4} , 'd'},
    {{0,5} , 'e'},
    {{0,6} , 'f'},
    {{0,7} , 'g'},
    {{1,2} , 'h'},
    {{1,3} , 'i'},
    {{4,6} , 'j'},
    {{1,4} , 'k'},
    {{1,5} , 'l'},
    {{1,6} , 'm'},
    {{1,7} , 'n'},
    {{2,3} , 'o'},
    {{2,4} , 'p'},
    {{2,5} , 'q'},
    {{2,6} , 'r'},
    {{2,7} , 's'},
    {{3,4} , 't'},
    {{3,5} , 'u'},
    {{4,7} , 'v'},
    {{5,6} , 'w'},
    {{5,7} , 'x'},
    {{3,6} , 'y'},
    {{6,7} , 'z'},
};

map<char, pair<ll,ll>> rev{
    {'a', {0,1}},
    {'b', {0,2}},
    {'c', {0,3}},
    {'d', {0,4}},
    {'e', {0,5}},
    {'f', {0,6}},
    {'g', {0,7}},
    {'h', {1,2}},
    {'i', {1,3}},
    {'j', {4,6}},
    {'k', {1,4}},
    {'l', {1,5}},
    {'m', {1,6}},
    {'n', {1,7}},
    {'o', {2,3}},
    {'p', {2,4}},
    {'q', {2,5}},
    {'r', {2,6}},
    {'s', {2,7}},
    {'t', {3,4}},
    {'u', {3,5}},
    {'v', {4,7}},
    {'w', {5,6}},
    {'x', {5,7}},
    {'y', {3,6}},
    {'z', {6,7}},
};

void desenha(ll p, vector<string>& s){
    
    if(p == 0) forn(i,1,4) s[4+i][4] = '#';
    if(p == 1) forn(i,1,4) s[4+i][4-i] = '#';
    if(p == 2) forn(i,1,4) s[4][4-i] = '#';
    if(p == 3) forn(i,1,4) s[4-i][4-i] = '#';
    if(p == 4) forn(i,1,4) s[4-i][4] = '#';
    if(p == 5) forn(i,1,4) s[4-i][4+i] = '#';
    if(p == 6) forn(i,1,4) s[4][4+i] = '#';
    if(p == 7) forn(i,1,4) s[4+i][4+i] = '#';
    
}

void solve(ll c){
    vector<string> vec(9);
    forn(i,0,9) cin >> vec[i];
    v64 pos;

    if(vec[5][4] == '#') pos.push_back(0);
    if(vec[5][3] == '#') pos.push_back(1);
    if(vec[4][3] == '#') pos.push_back(2);
    if(vec[3][3] == '#') pos.push_back(3);
    if(vec[3][4] == '#') pos.push_back(4);
    if(vec[3][5] == '#') pos.push_back(5);
    if(vec[4][5] == '#') pos.push_back(6);
    if(vec[5][5] == '#') pos.push_back(7);
    sort(pos.begin(), pos.end());

    p64 p = {pos[0], pos[1]};
    ll ch = mp[p] - 'a';
    ch = (ch+c)%26;
    p64 p2 = rev[ch+'a'];
    vector<string> resp(9, string(9,'.'));

    resp[4][4] = '*';
    desenha(p2.first, resp);
    desenha(p2.second, resp);

    forn(i,0,9){
        cout << resp[i] << ln;
    }
}
int main(){
    _;
    ll n, c; cin >> n >> c;

    forn(i,0,n) solve(c);

    return 0;
}