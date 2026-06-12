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

// Implicit Treap (Sequence Treap)
//
// Maintains a sequence with split and merge operations using randomized priorities and subtree sizes.
//
// complexity: O(log N) expected per op, O(N)

struct Treap{
    ll val;
    ll prio, size, sum;
    vector<Treap*> kids;
    Treap(ll c): val(c), prio(rand()), size(1), sum(c),
        kids({NULL,NULL}){}; 
};

ll size(Treap *me){return me ? me->size : 0;}
ll sum(Treap *me){return me ? me->sum : 0;}

void rsz(Treap* me){me -> size = 
    1 + size(me->kids[0]) + size(me->kids[1]);
    me->sum = sum(me->kids[0]) + sum(me->kids[1]);
}

vector<Treap*> split(Treap *me, ll idx){
    if(!me) return {NULL,NULL};
    vector<Treap*> out;

    if(size(me->kids[0]) < idx){
        auto aux = split(me->kids[1], 
            idx - size(me->kids[0]) -1);
        me->kids[1] = aux[0];
        rsz(me);
        out = {me, aux[1]};
    }else{
        auto aux = split(me->kids[0], idx);
        me->kids[0] = aux[1];
        rsz(me);
        out = {aux[0], me};
    }
    return out;
}

Treap* merge(Treap *left, Treap *right){
    if(left == NULL) return right;
    if(right == NULL) return left; 
    
    Treap* out;
    
    if(left->prio < right->prio){
        left->kids[1] = merge(left->kids[1], right);
        rsz(left);
        out = left;
    }else{
        right->kids[0] = merge(left, right->kids[0]);
        rsz(right);
        out = right;
    }
    return out;
}


// int main() {
//     _;
//     return 0;
// }
