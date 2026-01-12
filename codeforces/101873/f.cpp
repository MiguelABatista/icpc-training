#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll calc_overlap(string& a, string& b) {
    ll max_ov = 0;
    for (ll len = 1; len <= min(sz(a), sz(b)); len++) {
        if (a.substr(sz(a) - len) == b.substr(0, len)) {
            max_ov = len;
        }
    }
    return sz(b) - max_ov;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll h, w, n;
    if (!(cin >> h >> w >> n)) return 0;
    
    vector<string> raw_vs(n);
    forn(i, 0, n) cin >> raw_vs[i];

    vector<string> vs;
    vector<bool> ignored(n, false);
    forn(i, 0, n) {
        forn(j, 0, n) {
            if (i == j) continue;
            if (raw_vs[j].find(raw_vs[i]) != string::npos) {
                ignored[i] = true;
                break;
            }
        }
    }
    forn(i, 0, n) if (!ignored[i]) vs.push_back(raw_vs[i]);
    
    n = sz(vs);
    vector<v64> dist(n, v64(n));
    vector<ll> lens(n);
    
    forn(i, 0, n) {
        lens[i] = sz(vs[i]);
        forn(j, 0, n) {
            if (i == j) continue;
            dist[i][j] = calc_overlap(vs[i], vs[j]);
        }
    }

    ll lim = 1LL << n;
    vector<vector<p64>> dp(lim, vector<p64>(n, {INF, -1}));

    forn(i, 0, n) dp[1LL << i][i] = {lens[i], -1};

    forn(mask, 1, lim) {
        forn(i, 0, n) {
            if (!((mask >> i) & 1)) continue;
            if (dp[mask][i].first == INF) continue;

            forn(j, 0, n) {
                if (!((mask >> j) & 1)) {
                    ll next_mask = mask | (1LL << j);
                    ll new_cost = dp[mask][i].first + dist[i][j];
                    if (new_cost < dp[next_mask][j].first) {
                        dp[next_mask][j] = {new_cost, i};
                    }
                }
            }
        }
    }

    vector<p64> best_for_mask(lim, {INF, -1});
    forn(mask, 1, lim) {
        forn(i, 0, n) {
            if (((mask >> i) & 1) && dp[mask][i].first < best_for_mask[mask].first) {
                best_for_mask[mask] = {dp[mask][i].first, i};
            }
        }
    }

    v64 row_masks(h, 0);
    forn(i, 0, n) {
        ll best_inc = INF;
        ll best_r = -1;
        
        forn(r, 0, h) {
            ll mask = row_masks[r];
            ll new_mask = mask | (1LL << i);
            
            if (best_for_mask[new_mask].first <= w) {
                if (best_for_mask[new_mask].first < best_inc) {
                    best_inc = best_for_mask[new_mask].first;
                    best_r = r;
                }
            }
        }
        
        if (best_r == -1) {
            cout << "impossible" << ln;
            return 0;
        }
        row_masks[best_r] |= (1LL << i);
    }

    forn(r, 0, h) {
        ll mask = row_masks[r];
        if (mask == 0) {
            cout << "" << ln;
            continue;
        }
        
        v64 path;
        ll curr = best_for_mask[mask].second;
        while(curr != -1) {
            path.push_back(curr);
            ll prev = dp[mask][curr].second;
            mask ^= (1LL << curr);
            curr = prev;
        }
        reverse(path.begin(), path.end());
        
        string res = vs[path[0]];
        forn(k, 1, sz(path)) {
            ll u = path[k-1];
            ll v = path[k];
            res += vs[v].substr(lens[v] - dist[u][v]);
        }
        cout << res << ln;
    }

    return 0;
}