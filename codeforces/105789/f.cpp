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

struct node {
    ll lm, rm;
    ll mn;
    unique_ptr<node> lc, rc;

    node(ll l, ll r, const vector<ll>& a) : lm(l), rm(r) {
        if (lm == rm) { 
            mn = a[lm];
             return; 
        }

        ll m = (lm + rm) >> 1;
        lc = make_unique<node>(lm, m, a);
        rc = make_unique<node>(m+1, rm, a);
        pull();
    }

    static ll comb(ll a, ll b) {
        return min(a, b);
    }

    void pull() {
        mn = comb(lc->mn, rc->mn);
    }

    void upd(ll lq, ll rq, ll x, vector<pair<node*,ll>>& log) {
        if (lq > rm || lm > rq) return;
        if (lq <= lm && rm <= rq) {
            if (mn < x) {
                log.emplace_back(this, mn);
                mn = x;
            }
            return;
        }

        lc->upd(lq, rq, x, log);
        rc->upd(lq, rq, x, log);
        
        ll nxt = comb(lc->mn, rc->mn);
        
        if (mn < nxt) {
            log.emplace_back(this, mn);
            mn = nxt;
        }
    }

    ll get(ll lq, ll rq) const {
        if (lq > rm || lm > rq) return INF;
        if (lq <= lm && rm <= rq)  return mn;
        ll res = min(lc->get(lq, rq), rc->get(lq, rq));
        return max(res, mn);
    }
};

struct segtree {
    unique_ptr<node> root;
    vector<pair<node*,ll>> log;

    segtree(const v64& a) {
        root = make_unique<node>(0, (ll)a.size()-1, a);
    }

    void upd(ll l, ll r, ll x){
        root->upd(l, r, x, log);
    }

    ll get(ll l, ll r){
        return root->get(l, r);
    }

    ll version() const {
        return (ll)log.size();
    }

    void rollback(ll ver){
        while ((ll)log.size() > ver){
            auto [p, old] = log.back();
            log.pop_back();
            p->mn = old;
        }
    }
};

struct query{
    ll l, r, ans;
    query(){
        l = -1;
        r = -1;
        ans = -1;
    }
    query(ll l_, ll r_){
        l = l_;
        r = r_;
        ans = -1;
    }
};

struct time_query{
    ll l, r, h, t_in, t_out;
    time_query(ll l_, ll r_, ll h_, ll t1, ll t2){
        l = l_;
        r = r_;
        h = h_;
        t_in = t1;
        t_out = t2;
    }
};

struct time_node {
    ll lm, rm;
    unique_ptr<time_node> lc, rc;

    vector<time_query> op;

    time_node(ll lm_, ll rm_){
        lm = lm_;
        rm = rm_;
        if (lm != rm) {
            ll mid = (lm + rm) / 2;
            lc = make_unique<time_node>(lm, mid);
            rc = make_unique<time_node>(mid + 1, rm);
        }
    }

    void add_sign(ll lq, ll rq, time_query x) {
        if (rq < lm || lq > rm) return;
        // debug(lq);
        // debug(rq);
        // debug(lm);
        // debug(rm);
        if (lq <= lm && rm <= rq) {
            op.push_back(x);
            return;
        }
        lc->add_sign(lq, rq, x);
        rc->add_sign(lq, rq, x);
    }
};

void dfs(time_node& curr, segtree& seg, vector<query>& resp){
    ll ver = seg.version();

    for(auto q : curr.op){
        debug(q.l);
        debug(q.r);
        debug(q.h);
        seg.upd(q.l, q.r, q.h);
        debug(seg.get(4, 5));
        debug(seg.version());
    }

    if(curr.lm == curr.rm){
        ll idx = curr.lm;
        debug(resp[idx].l);
        debug(resp[idx].r);
        if(resp[idx].l != -1) resp[idx].ans = seg.get(resp[idx].l, resp[idx].r);
    }else {
        dfs(*curr.lc, seg, resp);
        dfs(*curr.rc, seg, resp);
    }
    
    seg.rollback(ver);
}

int main(){
    _; ll q; cin >> q;
    set<ll> s;
    map<ll, ll> translate;

    vector<time_query> intervals;
    vector<query> resp(q);

    forn(i, 0, q){
        char c; cin >> c;
        if(c == '?'){
            ll l, r; cin >> l >> r;
            l *= 2;
            r *= 2;
            s.insert(l);
            s.insert(r);
            resp[i] = query(l, r);
        }
        if(c == '+'){
            ll l, r, h; cin >> l >> r >> h;
            l *= 2;
            r *= 2;
            s.insert(l);
            s.insert(r);

            intervals.push_back(time_query(l, r, h, i, q-1));
        }
        if(c == '-'){
            ll idx; cin >> idx; idx--;
            intervals[idx].t_out = i-1;
        }
    }

    ll cnt = 0, last = -1;
    for(auto x : s){ 
        if(x > last + 1) cnt++;
        // debug(cnt);
        // debug(x);
        translate[x] = cnt++;
        last = x;
    }

    for(auto &qr : intervals){
        qr.l = translate[qr.l];
        qr.r = translate[qr.r];
    }

    for(auto &qr : resp){
        if(qr.l == -1) continue;
        qr.l = translate[qr.l];
        qr.r = translate[qr.r];
    }

    // for(auto qr : intervals){
    //     cout << qr.l << " " << qr.r << " " << qr.h << " " << qr.t_in << " " << qr.t_out << ln;
    // }

    // for(auto qr : resp){
    //     cout << qr.l << " " << qr.r << ln;
    // }

    time_node timeline(0, q-1);

    for(auto x : intervals){
        timeline.add_sign(x.t_in, x.t_out, x);
    }

    // debug(cnt);
    vector<ll> v(cnt, 0);
    segtree seg(v);

    dfs(timeline, seg, resp);

    for(auto qr : resp){
        if(qr.l == -1) continue;
        cout << qr.ans << ln;
    }

    return 0;
}