#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const ll INF = 0x3f3f3f3f3f3f3f3fll;


// Node: guarda info para blocos de 1s e de 0s simultaneamente.
// pref1/suf1/best1: maior prefixo/sufixo/bloco de 1s
// pref0/suf0/best0: idem para 0s
// len: tamanho do segmento
struct Node {
    ll len;
    ll pref1, suf1, best1;
    ll pref0, suf0, best0;

    // combine: junta segmento esquerdo (this) com direito (o)
    Node operator*(const Node &o) const {
        if (len == 0) return o;
        if (o.len == 0) return *this;
        Node r;
        r.len = len + o.len;
        // prefixo de 1s: se o lado esquerdo é todo 1, estende para o direito
        r.pref1 = (pref1 == len) ? len + o.pref1 : pref1;
        r.suf1  = (o.suf1 == o.len) ? o.len + suf1 : o.suf1;
        r.best1 = max({best1, o.best1, suf1 + o.pref1});
        // mesmo para 0s
        r.pref0 = (pref0 == len) ? len + o.pref0 : pref0;
        r.suf0  = (o.suf0 == o.len) ? o.len + suf0 : o.suf0;
        r.best0 = max({best0, o.best0, suf0 + o.pref0});
        return r;
    }
};

// Update: flip alterna 0<->1. Aplicar é só trocar os campos de 0 com os de 1.
struct Update {
    bool flip = false;
    Node operator()(const Node &n) const {
        if (!flip) return n;
        Node r = n;
        swap(r.pref1, r.pref0);
        swap(r.suf1,  r.suf0);
        swap(r.best1, r.best0);
        return r;
    }
    // compor updates: flip aplicado duas vezes se cancela
    Update operator+(const Update &o) const {
        return { (flip ^ o.flip) };
    }
};

template<typename T, typename U> struct segtree {
  ll s, h;
  T id;
  vector<T> val;
  U noop;
  vector<bool> dirty;
  vector<U> prop;
  segtree(ll ts, T tid = T(), U tnoop = U()) {
    id = tid, noop = tnoop;
    for (s = 1, h = 1; s < ts; ) s *= 2, h++;
    val.assign(2*s, id);
    dirty.assign(2*s, false);
    prop.assign(2*s, noop);
  }
  void set_leaves(vector<T> &lvs) {
    copy(lvs.begin(), lvs.end(), val.begin() + s);
    for (ll i = s - 1; i > 0; i--) val[i] = val[2 * i] * val[2 * i + 1];
    dirty.assign(2*s, false);
    prop.assign(2*s, noop);
  }
  void apply(ll i, U &upd) {
    val[i] = upd(val[i]);
    if(i < s) {
      prop[i] = prop[i] + upd;
      dirty[i] = true;
    }
  }
  void pull(ll i) {
    for (ll l = i/2; l; l /= 2) {
      T comb = val[2*l] * val[2*l+1];
      val[l] = prop[l](comb);
    }
  }
  void push(ll i) {
    for (ll th = h; th > 0; th--) {
      ll l = i >> th;
      if (dirty[l]) {
        apply(2*l, prop[l]);
        apply(2*l+1, prop[l]);
        prop[l] = noop;
        dirty[l] = false;
      }
    }
  }
  void update(ll i, ll j, U upd) {
    i += s, j += s;
    push(i), push(j);
    for (ll l = i, r = j; l <= r; l /= 2, r /= 2) {
      if((l&1) == 1) apply(l++, upd);
      if((r&1) == 0) apply(r--, upd);
    }
    pull(i), pull(j);
  }
  T query(ll i, ll j){
    i += s, j += s;
    push(i), push(j);
    T rl = id, rr = id;
    for(; i <= j; i /= 2, j /= 2){
      if((i&1) == 1) rl = rl * val[i++];
      if((j&1) == 0) rr = val[j--] * rr;
    }
    return rl * rr;
  }
};


int main(){
    _;

    ll n, q;
    cin >> n >> q;

    Node id = {0,0,0,0,0,0,0};
    Update noop = {false};

    vector<Node> leaves(n);
    for (ll k = 0; k < n; k++) {
        int b;
        cin >> b;
        if (b == 1) leaves[k] = {1, 1,1,1, 0,0,0};
        else        leaves[k] = {1, 0,0,0, 1,1,1};
    }

    segtree<Node, Update> st(n, id, noop);
    st.set_leaves(leaves);

    while (q--) {
        int t; ll l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (t == 1) {
            st.update(l, r, Update{true});
        } else {
            cout << st.query(l, r).best1 << "\n";
        }
    }
    return 0;
}