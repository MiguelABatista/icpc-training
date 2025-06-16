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

const ll sp = 316;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct part {
    map<ll, pair<ll, v64>> mp;
    map<ll, v64> idxs;
    v64& v;
    ll l, r;
    ll offset = 0;

    part(v64& v_, ll l_, ll r_) : v(v_), l(l_), r(r_) {
        build();
    }

    ll mx(ll lq, ll rq) {
        if (lq <= l && rq >= r) return mp.rbegin()->first + offset;
        if (rq < l || lq > r) return -INF;
        
        lq = max(l, lq);
        rq = min(r, rq);
        destruct();
        build();
        return *max_element(v.begin() + lq, v.begin() + rq + 1);
    }

    void reset(ll lq, ll rq, ll val) {
        if (rq < l || lq > r) return;
        auto item = mp.rbegin()->second;
        if (mp.rbegin()->first + offset != val) return;

        if (lq <= l && rq >= r) {
            mp.erase(--mp.end());
            if (mp.find(-offset) == mp.end()) mp[-offset] = item;
            else {
                v64& a = mp[-offset].second;
                v64& b = item.second;
                if (a.size() < b.size()) swap(a, b);
                a.insert(a.end(), b.begin(), b.end());
                mp[-offset] = {mp[-offset].first + item.first, a};
            }
            return;
        }
        
        destruct();
        
        lq = max(l, lq);
        rq = min(r, rq);
        
        forn(i, lq, rq+1) {
            if (v[i] == val) v[i] = -offset;
        }

        build();
        
    }

    void add(ll lq, ll rq) {
        if (lq <= l && rq >= r) {
            offset++;
            return;
        }
        if (rq < l || lq > r) return;

        destruct();

        lq = max(l, lq);
        rq = min(r, rq);

        forn(i, lq, rq+1) {
            v[i]++;
        }
        build();
    }

    void destruct() {
        for (auto& [key, val] : mp) {
            ll new_val = key + offset;
            for (auto original_val : val.second) {
                for (auto idx : idxs[original_val]) {
                    v[idx] = new_val;
                }
            }
        }
        mp.clear();
        idxs.clear();
        offset = 0;
    }

    void build() {
        forn(i, l, r+1) {
            idxs[v[i]].push_back(i);
            auto it =  mp.find(v[i]);
            if (it != mp.end()) {
                it->second.first++;
            } else {
                mp[v[i]] = {1, {v[i]}};
            }
        }
    }
    
};

struct jogo {
    v64 v;
    vector<part> parts;

    jogo(v64& v_) : v(v_) {
        for (ll i = 0; i < (ll)v.size(); i += sp) parts.push_back(part(v, i, min(i+sp-1, (ll)v.size()-1)));
    }

    ll mx(ll lq, ll rq) {
        ll ans = -INF;
        for (auto& part: parts) {
            auto temp = part.mx(lq, rq);
            ans = max(ans, temp);
        }
        return ans;
    }

    void reset(ll lq, ll rq) {
        ll val = mx(0, (ll)v.size()-1);
        
        for (auto& part: parts) {
            part.reset(lq, rq, val);
        }
        
    }

    void add(ll lq, ll rq) {
        for (auto& part: parts) {
            part.add(lq, rq);
        }
    }
};


int main(){
    _;
    ll n, k; cin >> n >> k;
    v64 v(n);
    forn(i, 0, n) cin >> v[i];
    
    jogo game(v);
    forn(lixo, 0, k) {
        char c; cin >> c;
        ll a, b; cin >> a >> b;
        a--;b--;
        debug("-------------");
        if (c == 'Q') {
            cout << game.mx(a, b) << ln;
        } else if (c == 'A') {
            game.add(a, b);
        } else if (c == 'R') {
            game.reset(a, b);
        }

    }
    return 0;
}