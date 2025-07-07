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

const ll sp = 315;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

struct part {
    set<ll> s;
    vector<pair<ll,ll>> mud;

    v64& v;
    ll l, r;
    ll offset = 0;

    part(v64& v_, ll l_, ll r_) : v(v_), l(l_), r(r_) {
        build();
    }

    ll mx(ll lq, ll rq) {
        if (lq <= l && rq >= r) return *s.rbegin() + offset;
        if (rq < l || lq > r) return -INF;
        
        lq = max(l, lq);
        rq = min(r, rq);
        destruct();
        build();
        return *max_element(v.begin() + lq, v.begin() + rq + 1);
    }

    void reset(ll lq, ll rq, ll val) {
        if (rq < l || lq > r) return;
        if (*s.rbegin() + offset != val) return;

        if (lq <= l && rq >= r) {
            auto it = --s.end();

            ll old_v = *it; 
            
            ll new_v = -offset;
            
            mud.emplace_back(new_v, old_v);

            s.erase(it);
            s.insert(new_v);

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
        map<ll, ll> to;

        for(auto it = mud.rbegin(); it != mud.rend(); it++){
            ll a = it->second;
            ll b = it->first;

            if(to.find(b) == to.end()) to[a] = b;
            else to[a] = to[b];

        }

        forn(i,l,r+1){
            auto it = to.find(v[i]);  
            if(it == to.end()) {
                v[i] = v[i] + offset;
                continue;
            }
            v[i] = it->second + offset;
        }

        s.clear();
        mud.clear();
        offset = 0;
    }

    void build() {
        forn(i, l, r+1) s.insert(v[i]);    
    }
    
    void print(){
        cout << l << " " << r << " : ";
        forn(i,l,r+1) cout << v[i] << " ";
        cout << ln;
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

    void print(){
        for(auto p : parts) p.print();       
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