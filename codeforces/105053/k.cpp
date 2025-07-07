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

bool is_vogal(char c){
    string s = "AEIOUY";
    for(auto aux : s) if(c == aux) return true;
    return false;
}

ll tipo(string aux){
    ll counter = 0;
    for(auto c : aux){
        if(is_vogal(c)) break;
        counter++;
    }

    return min(counter, (ll)3);
}

int main(){
    _; ll n; cin >> n;
    vector<ll> pref(n);
    vector<string> v(n);
    forn(i, 0, n){
        cin >> v[i];
        pref[i] = tipo(v[i]);
    }

    vector<vector<ll>> dp(n, vector<ll> (3, INF));

    // forn(i, 0, n) cout << pref[i] << " ";
    // cout << ln;
    
    if(pref[n-1] == 0) dp[n-1][0] = 1;
    else dp[n-1][1] = 1;

    for(ll i = n-2; i>= 0; i--){
        if(pref[i] == 0){
            dp[i][0] = min(min(dp[i+1][0], dp[i+1][1]), dp[i+1][2]) + 1;
        }
        if(pref[i] == 1){
            dp[i][1] = dp[i+1][0]+1;
            if((ll)v[i].size() > 1) dp[i][1] = min(dp[i][1], min(dp[i+1][1]+2, dp[i+1][2]+2));

            dp[i][2] = dp[i+1][1]+1;
        }
        if(pref[i] == 2){
            dp[i][1] = dp[i+1][0]+1;

            dp[i][2] = min(dp[i+1][0]+2, dp[i+1][1]+1);
            if((ll)v[i].size() > 2) dp[i][2] = min(dp[i][2], dp[i+1][2]+3);
        }
        if(pref[i] == 3){
            dp[i][1] = dp[i+1][0]+1;
            dp[i][2] = min(dp[i+1][1]+1, dp[i+1][0]+2);
        }
    }

    // forn(i, 0, n){
    //     forn(j, 0, 3){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << ln;
    // }

    ll best = min(min(dp[0][0], dp[0][1]), dp[0][2]);
    if(best >= 10000000){
        cout << "*" << ln;
        return 0;
    }

    cout << best << ln;

    return 0;
}