#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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
#define debugp(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll LOG = 30;

int main() {
    _;
    ll n, q; cin >> n >> q;
    v64 vec(n+1), acc(n+1);
    v64 prox(n, -1);

    forn(i,0,n){
        cin >> vec[i];
        acc[i] = vec[i] + (i == 0 ? 0 : acc[i-1]);
    }
    acc[n] = INF;
    vec[n] = INF;
    auto soma = [&](ll a, ll b){
        return acc[b] - (a == 0 ? 0 : acc[a-1]);
    };

    stack<p64> st;
    st.push({INF,n});  
    for(ll i = n-1; i >= 0; i--){
        while(st.top().first < vec[i]) st.pop();
        prox[i] = st.top().second;
        st.push({vec[i], i});
    }

    vector<vector<p64>> bl(LOG, vector<p64>(n));

    forn(i,0,n){
        p64 resp = {prox[i], 0};
        resp.second = (prox[i]-i)*vec[i] - soma(i, prox[i] - 1);
        bl[0][i] = resp;
    }


    forn(j,1,LOG){
        forn(i,0,n){
            ll idx = 0;
            ll sum = 0;
            ll temp = bl[j-1][i].first;
            if(temp == n){
                bl[j][i] = bl[j-1][i];
                continue;
            }
            idx = bl[j-1][temp].first;
            sum = bl[j-1][temp].second + bl[j-1][i].second;
            if(sum > INF) sum = INF;
            bl[j][i] = {idx, sum};
        }
    }

    debugv(vec);
    forn(i,0,4){debugp(bl[i]);};

    while(q--){
        ll a, b; cin >> a >> b;
        a--, b--;
        trace(cout << a << "  " << b << ln;)
        
        ll cost = 0;
        ll p = a;
        for(ll j = LOG-1; j >= 0; j--){
            if(bl[j][p].first > b) continue;
            cost += bl[j][p].second;
            p = bl[j][p].first;
        }
        debug(p);
        debug(b-p+1);
        debug(vec[p]);
        debug(soma(p, b));
        cost += (b-p+1)*vec[p] - soma(p, b);
        cout << cost << ln;
    }
    return 0;
}
