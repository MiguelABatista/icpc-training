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



void solve(){
    ll n; cin >> n;
    string s; cin >> s;
    debug(s);
    map<char, ll> m1, conv;
    vector<pair<ll,char>> auxx;
    vll vec(n), freq(3);

    m1['T'] = 0;
    m1['L'] = 0;
    m1['I'] = 0;

    forn(i,0,n) m1[s[i]]++;
    
    for(auto [k,v] : m1) auxx.push_back({v,k});
    sort(auxx.begin(), auxx.end());

    ll semnome = 0;
    for(auto [amt, c] : auxx){
        freq[semnome] = amt;
        conv[c] = semnome++;
    }
    forn(i,0,n) vec[i] = conv[s[i]];

    // freq 0 <= freq1 <= freq2
    // vec tem 0 1 e 2]
    debugv(vec);
    vll resp;
    vll toadd;
    forn(i,0,n-1){
        if(vec[i] == 1 && vec[i+1] == 2){
            toadd.push_back(i+1);
        }
        if(vec[i] == 2 && vec[i+1] == 1){
            toadd.push_back(i+1);
        }
    }    
    while (freq[0] < freq[1]){
        if(sz(toadd) == 0){
            cout << -1 << ln;
            return;
        }
        ll x = toadd.back();
        toadd.pop_back();
        vec.insert(vec.begin()+x, 0);
        resp.push_back(x);
        freq[0]++;
    }

    debugv(vec);

    bool found = freq[1] == freq[2];
    
    forn(i,0,n-1){
        if((vec[i] == 0 || vec[i] == 1) && vec[i+1] == 2){
            found = true;
            // 1 2
            ll idx = i+1;
            while (freq[1] < freq[2]){
                resp.push_back(idx++); // 1 0 2
                resp.push_back(idx++); // 1 0 1 2
                freq[1]++;
            }            
            break;
        }
        if((vec[i+1] == 0 || vec[i+1] == 1) && vec[i] == 2){
            found = true;
            // 2 1
            while (freq[1] < freq[2]){
                resp.push_back(i+1);
                resp.push_back(i+1); 
                freq[1]++;
            }
            break;
        }
    }
    if(!found){
        cout << -1 << ln;
        return;
    }
    cout << sz(resp) << ln;
    for(ll x: resp) cout << x << ln;
    cout << n << ln;
    cout << s << ln;
}

int main() {
    _;
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}
