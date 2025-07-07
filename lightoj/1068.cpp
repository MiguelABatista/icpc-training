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

const ll MAXSIZE = 11;
const ll MAXK = 100;

v64 pow10(MAXSIZE, 1);
static ll dp[11][100][100][2];

void prep(){
    forn(i,1,MAXSIZE) pow10[i] = 10*pow10[i-1];
}

ll testcase = 1;

ll rec(ll curr, ll rem_num, ll rem_dig, ll tight, string& num, ll k){
    if(curr == 0){ 
        if((rem_num % k == 0) && (rem_dig % k == 0)) return 1;
        return 0;
    } 

    if(dp[curr][rem_num][rem_dig][tight] != -1)
        return dp[curr][rem_num][rem_dig][tight];

    ll lim;
    ll numidx = (ll)num.size() - curr;
    if(tight){
        lim = num[numidx] - '0';    
    }else{
        lim = 9;
    }
    
    ll ans = 0;
    forn(dig, 0,lim+1){
        ll new_rem_num = (rem_num + dig*pow10[curr-1])%k;
        ll new_rem_dig = (rem_dig+dig)%k;
        ll new_tight = ((tight && (dig == (ll)(num[numidx]-'0'))) ? 1 : 0);
        ans += rec(curr-1, new_rem_num, new_rem_dig, new_tight, num, k);
    }

    dp[curr][rem_num][rem_dig][tight] = ans;
    return ans;
}

void solve(){
    ll a, b, k; cin >> a >> b >> k;
    
    if(k > MAXK){
        cout << "Case " << testcase++ << ": " << 0 << ln;
        return;
    }

    memset(dp, -1, sizeof(dp));
    string str1 = to_string(a-1);
    ll cnt1 = rec(str1.size(), 0, 0, 1, str1, k);

    memset(dp, -1, sizeof(dp));
    string str2 = to_string(b);
    ll cnt2 = rec(str2.size(), 0, 0, 1, str2, k);
    
    cout << "Case " << testcase++ << ": " << cnt2 - cnt1 << ln;
}

int main(){
    _;
    prep();
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}