#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

mt19937_64 rng(steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    ld ans = 0.0;
    for (int j = 0; j < n; j++) {      
        for (int i = 0; i < j; i++) {  
            ld tot = (ld)r[i] * r[j];
            ll c = 0;
            for (int k = 1; k <= r[j]; k++) {
                c += max(0, r[i] - k);
            }
            ans += (ld)c / tot;
        }
    }

    cout << fixed << setprecision(6) << ans << "\n";
}

int main() {
    fastio;
    solve();
    
    return 0;
}