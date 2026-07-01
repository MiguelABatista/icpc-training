#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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

// const ll INF = 0x3f3f3f3f3f3f3f3fll;

int main() {

    int n; cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    vector dp(n, vector<int> (n));

    for(int sz = 2; sz <= n; sz++){
        for(int l = 0; l+sz-1 < n; l++){
            int r = l+sz-1;
            
            int ans = 0;
            vector<int> pos(n);
            vector<int> seq;
            for(int i = 0; i < n; i++){
                if(arr[i] >= l && arr[i] <= r){
                    pos[arr[i]] = seq.size();
                    seq.push_back(0);
                }
            }

            for(int i = l; i <= r; i++){
                
                if(pos[i]-1 >= 0) ans += (seq[pos[i]-1] == 0 ? 1 : -1);
                if(pos[i]+1 < sz(seq)) ans += (seq[pos[i]+1] == 0 ? 1 : -1);
                seq[pos[i]] = 1;
                
                ll esq = 0;
                ll dir = 0;
                ll ambos = 0;
                if(pos[i]-1 >= 0) esq = seq[pos[i]-1] != seq[pos[i]];
                if(pos[i]+1 < sz(seq)) dir = seq[pos[i]+1] != seq[pos[i]];
                if(pos[i]-1 >= 0 && pos[i]+1 < sz(seq)) ambos = seq[pos[i]-1] != seq[pos[i] + 1]; 
                
                ll continha = ambos - esq - dir;
                int currans = 0;
                currans = ans + continha;

                if(i == l) dp[l][r] = max(dp[l][r], dp[l+1][r]);
                else if(i == r) dp[l][r] = max(dp[l][r], dp[l][r-1]);
                else dp[l][r] = max(dp[l][r], dp[l][i-1] + dp[i+1][r] + currans);
                
            }
        }   
    }

    forn(i,0,n){debugv(dp[i]);};
    cout << dp[0][n-1] << ln;

    return 0;
}