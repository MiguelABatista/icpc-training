#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

const ld NEG = -1e100L;

struct task {
    ll d, p, c, l, r, yl, yr;
};

ld expected_bonus(ll finish_time, task &tas) {
    if (finish_time > tas.yr) return 0.0;
    if (finish_time <= tas.yl) return (tas.l + tas.r) / 2.0;

    ll len = tas.yr - tas.yl;
    if (len == 0) return (finish_time <= tas.yl ? (tas.l + tas.r) / 2.0 : 0.0);

    ld prob = (tas.yr - finish_time) / (ld)len;
    prob = max(0.0L, min(1.0L, prob));

    return ((tas.l + tas.r) / 2.0) * prob;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll n;
    cin >> n;
    vector<task> tasks(n);
    forn(i, 0, n) {
        cin >> tasks[i].d >> tasks[i].p >> tasks[i].c >> tasks[i].l >> tasks[i].r >> tasks[i].yl >> tasks[i].yr;
    }

    ll full = 1 << n;
    vector<ld> dp(full, NEG);
    vector<ll> time(full, 0);
    dp[0] = 0;

    forn(mask, 1, full) {
        forn(i, 0, n) {
            if (!(mask & (1LL << i))) continue;

            ll prev = mask ^ (1LL << i);
            ll t = time[prev] + tasks[i].c;

            if (t > tasks[i].d) continue;

            ld base = dp[prev] + tasks[i].p;
            base += expected_bonus(t, tasks[i]);

            if (base > dp[mask]) {
                dp[mask] = base;
                time[mask] = t;
            }
        }
    }

    ld result = 0;
    forn(mask, 0, full) result = max(result, dp[mask]);
    cout << fixed << setprecision(12) << result << ln;
    return 0;
}
