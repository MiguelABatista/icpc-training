#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define sz(x) ((ll) x.size())
#define ln "\n"

#ifdef DEBUG
    #define trace(x) x
    #define _ (void)0
#else
    #define trace(x) (void)0
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
#endif

#define debugv(v) trace({cout << __LINE__ << ": " << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

// Segment Tree (Range Query + Point Update)
//
// Balanced binary tree for range queries with a customizable combine; supports point updates and range queries.
//
// complexity: O(log N) per op, O(N)

struct node {
    ll val = 0;
    
    static node comb(const node& a, const node& b) {
        return {min(a.val,b.val)};
    }
};

const node neutral = {INF};

struct tree {
    ll lm, rm;
    unique_ptr<tree> lc, rc;
    
    node val;

    tree(ll l_, ll r_, const vector<node>& v) : lm(l_), rm(r_) {
        if (lm == rm) {
            val = v[lm];
        } else {
            ll m = (lm + rm) / 2;
            lc = make_unique<tree>(lm, m, v);
            rc = make_unique<tree>(m + 1, rm, v);
            pull();
        }
    }

    void pull() {
        val = node::comb(lc->val, rc->val);
    }

    void point_set(ll idx, node x) {
        if (lm == rm) {
            val = x;
            return;
        }
        if (idx <= lc->rm) lc->point_set(idx, x);
        else rc->point_set(idx, x);
        pull();
    }

    node query(ll lq, ll rq) {
        if (rq < lm || lq > rm) return neutral;
        if (lq <= lm && rm <= rq) return val;
        return node::comb(lc->query(lq, rq), rc->query(lq, rq));
    }
};
 
ll find_p(vector<v64>& dpl, vector<v64>& dpr, ll lm, ll rm){
    // ultimo ponto tal que dpr[lm][x] <= dpl[x][rm]
    ll l = lm+1;
    ll r = rm-1;
    ll ans = l;
    trace(cout << "FIND\n");
    while(l <= r){
        ll mid = (l+r)/2;
        if(dpr[lm][mid] <= dpl[mid][rm]){
            ans = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    debug(ans);
    return ans;
}       

int main(){
    _;
    ll n; cin >> n;
    v64 s(n-1), dive(n+2),f(n+1);
    v64 dist(n+2);

    forn(i,0,n-1) cin >> s[i];
    forn(i,1,n+1) cin >> dive[i];
    forn(i,0,n+1) cin >> f[i];

    forn(i,2,n+1){
        dist[i] = dist[i-1] + s[i-2];
    }

    debugv(dist);
    debugv(dive);
    debugv(f);

    vector<v64> dpl(n+2, v64(n+2)); // dpl[l][r] = resposta pra [l,r] começando em l (considerando l, r terra)
    vector<v64> dpr(n+2, v64(n+2)); // dpr[l][r] = resposta pra [l,r] começando em r (considerando l, r terra)

    vector<vector<node>> auxl(n+2, vector<node>(n+2, neutral)); 
    vector<vector<node>> auxr(n+2, vector<node>(n+2, neutral));

    vector<tree> segl; // segl[l][i] = dive[i]+dist[i]+dpl[l,i]
    vector<tree> segr; // segr[i][r] = dive[i]-dist[i]+dpr[i,r]

    forn(i,0,n+2){
        segl.push_back(tree(0,n+1,auxl[i]));
        segr.push_back(tree(0,n+1,auxr[i]));
    }

    forn(t,0,n+2){
        forn(l,0,n+2-t){
            ll r = l+t;
            function<void(void)> ajeita = [&](void){
                dpl[r][l] = dpl[l][r];
                segl[l].point_set(r, {dpl[l][r] + dive[r] + dist[r]});
                segl[r].point_set(l, {dpl[l][r] + dive[r] + dist[r]});
                
                dpr[r][l] = dpr[l][r];
                segr[r].point_set(l, {dpr[l][r] + dive[l] + dist[l]});
                segr[l].point_set(r, {dpr[l][r] + dive[l] + dist[l]});
            };

            if(t == 0){
                dpl[l][r] = dpr[l][r] = INF;
                // ll algo = dive[l] + max((l == 0 ? 0 : f[l-1]), (l == n+1 ? 0 : f[l]));
                // dpl[l][r] = dpr[l][r] = algo;
                segl[l].point_set(r, {dpl[l][r] + dive[r] + dist[r]});
                segr[r].point_set(l, {dpr[l][r] + dive[l] + dist[l]});
                continue;
            }
            if(t == 1){
                dpl[l][r] = dpr[l][r] = f[l];
                ajeita();
                continue;
            }

            ll p = find_p(dpl, dpr, l, r);

            ll lmin = segr[p].query(l+1,p).val;
            ll rmin = segl[p+1].query(p+1,r).val;
            
            dpl[l][r] = min(lmin, rmin) - dist[l];
            dpr[l][r] = min(lmin, rmin) + dist[r];
            ajeita();
            
            debug(l);
            debug(r);
            debug(p);
            debug(lmin);
            debug(rmin);
        }
        trace(cout << "dpl: \n");
        trace(forn(i,0,n+2) {{forn(j,0,n+2) cout << setw(2) << (dpl[i][j] >= INF/2 ? -1 : dpl[i][j]) << " ";}; cout << ln;}; cout << ln;);
        trace(cout << "segl: \n");
        trace(forn(i,0,n+2) {{forn(j,0,n+2) cout << setw(2) << (segl[i].query(j,j).val >= INF/2 ? -1 : segl[i].query(j,j).val) << " ";}; cout << ln;}; cout << ln;);
        trace(cout << "dpr: \n");
        trace(forn(i,0,n+2) {{forn(j,0,n+2) cout << setw(2) << (dpr[i][j] >= INF/2 ? -1 : dpr[i][j]) << " ";}; cout << ln;}; cout << ln;);
        trace(cout << "segr: \n");
        trace(forn(i,0,n+2) {{forn(j,0,n+2) cout << setw(2) << (segr[i].query(j,j).val >= INF/2 ? -1 : segr[i].query(j,j).val) << " ";}; cout << ln;}; cout << ln;);
        trace(cout << ln;); 
    }
    
    cout << dpl[0][n-1] << ln;
    return 0;
}
  