#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

#define t(x) (x == '1' ? '0' : '1')
#define troca(x) (x = t(x))

const ll INF = 0x3f3f3f3f3f3f3f3fll;

void rec(string s, vector<p64>& q){
    ll n = sz(s);
    ll bigblock = 0;
    ll end = 0;
    ll currblock = 1;
    char currchar = s[0];
    ll idx = 0;
    while(idx < n-1){
        while(s[idx+1] == currchar) idx++,currblock++;
        if(currblock > bigblock){
            end = idx;
            bigblock = currblock;
        }
        idx++;
        currblock = 1;
        currchar = s[idx];
    }

    if(bigblock == 1){
        q.push_back({0,2});
        forn(i,0,3) troca(s[i]);
        bigblock = 2;
        end = 3;
    }
    ll start = end - bigblock + 1;


    if(s[end] == '1'){
        q.push_back({start, end});
        forn(i,start, end+1) troca(s[i]); 
    }


  
    while((start > 0) && (s[start-1] == '0')) start--;
    while((end < n-1) && (s[end+1] == '0')) end++;
        

    ll pa = max(0ll,start-1);
    ll pe = min(n-1,end+1);
    
    while(!(start == 0 && end == n-1)){

        while((pa > 0) && (s[pa-1] == '1')) pa--;
        while((pe < n-1) && (s[pe+1] == '1')) pe++;
        q.emplace_back(start, end);
        q.emplace_back(pa, pe);
        
        forn(i,pa,pe+1) s[i] = '0';
        while((start > 0) && (s[start-1] == '0')) start--;
        while((end < n-1) && (s[end+1] == '0')) end++;
        
        pa = start;
        pe = end;
    }
}


void solve(){
    ll n; cin >> n;
    string s, t;
    cin >> s >> t;
    vector<p64> q1, q2;

    rec(s, q1);
    rec(t, q2);

    cout << sz(q1) + sz(q2) << ln;
    for(auto p: q1) cout << p.first+1 << " " << p.second+1 << ln;
    reverse(q2.begin(), q2.end());
    for(auto p: q2) cout << p.first+1 << " " << p.second+1 << ln;

}
int main(){
    _;
    ll t; cin >> t;
    while(t--) solve(); 
    return 0;
}