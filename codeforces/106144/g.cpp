#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for (ll i=(s); i<(e); i++)
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
#define debugv(v) trace(cout << #v ": "; for(auto xx : v) cout << xx << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main(){
    _;
    ll t; cin >> t;
    while(t--){
        string  s; cin >> s;
        vll freq(26);
        vector<vll> blocos(26);

        freq[s[0]-'a']++; blocos[s[0]-'a'].push_back(1);
        forn(i,1,sz(s)){
            freq[s[i]-'a']++;
            if(s[i]==s[i-1]) blocos[s[i]-'a'][sz(blocos[s[i]-'a'])-1]++;
            else blocos[s[i]-'a'].push_back(1);
        }

        ll resp=1;

        forn(i,0,26){
            resp+=(freq[i]*freq[i]+freq[i])/2;
            for(auto u : blocos[i]) resp-=(u*u-u)/2;
        }

        cout << resp << ln;
    }
    return 0;
}