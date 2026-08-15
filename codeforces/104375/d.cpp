#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i = (s); i<(e); i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

# ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln)
#define debugv(v) trace(cout << #v ": "; for (auto xx : v) cout << xx << " "; cout << ln;)
#define debugm(v) trace(cout << #v ": "; for (auto xx : v) cout << xx.first << ":" << xx.second << " "; cout << ln;)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MAX = 3'000'005;



struct Node{
    ll sum = 0, cnt = 1;
    Node operator*(const Node &o) const { return {sum+o.sum,cnt+o.cnt}; }
};

struct Update{
    ll add=0;

    Node operator()(const Node &n) const {
        return {n.sum + add * n.cnt, n.cnt};
    }

    Update operator+(const Update &o) const {
        Update res = *this;
        res.add += o.add;
        return res;
    }
};

template<typename mint, typename U> struct segtree {
    ll s,h;

    mint id;
    vector<mint> val;

    U noop;
    vector<bool> dirty;
    vector<U> prop;

    segtree(ll ts, mint tid = mint(), U tnoop = U()) {
        id = tid, noop = tnoop;
        for (s = 1, h = 1; s< ts; ) s*=2, h++;

        val.assign(2*s, id);
        dirty.assign(2*s, false);
        prop.assign(2*s, noop);
    }

    void set_leaves(vector<mint> &lvs) {
        copy(lvs.begin(), lvs.end(), val.begin()+s);

        for (ll i = s - 1; i > 0; i--) val[i] = val[2 * i] * val[2 * i + 1];
        dirty.assign(2*s, false);
        prop.assign(2*s, noop);
    }

    void apply(ll i, U &upd) {
        val[i] = upd(val[i]);
        if(i<s) {
            prop[i] = prop[i] + upd;
            dirty[i] = true;
        }
    }

    void pull(ll i) {
        for(ll l = i/2; l; l/=2) {
            mint comb = val[2*l]*val[2*l+1];
            val[l] = prop[l](comb);
        }
    }

    void push(ll i) {
        for(ll th = h; th > 0; th--) {
            ll l = i >> th;

            if(dirty[l]) {
                apply(2*l, prop[l]);
                apply(2*l+1, prop[l]);

                prop[l] = noop;
                dirty[l] = false;
            }
        }
    }

    void update(ll i, ll j, U upd) {
        i +=s, j+= s;
        push(i),push(j);

        for (ll l = i, r = j; l<=r; l/=2, r/=2) {
            if((l&1) == 1) apply(l++, upd);
            if((r&1) == 0) apply(r--, upd);
        }

        pull(i), pull(j);
    }

    mint query(ll i, ll j){
        i += s, j += s;
        push(i), push(j);

        mint rl = id, rr = id;
        for(; i<=j; i/=2, j/=2){
            if((i&1) == 1) rl = rl * val[i++];
            if((j&1) == 0) rr = val[j--] * rr;
        }
        return rl * rr; 
    }
};
int main(){
    _;
    ll n, q; cin >> n >> q;

    vll vec(n);
    vll vals;
    vector<tuple<ll,ll,ll>> queries(q);
    multiset<pll> ms;
    segtree<Node, Update> seg(MAX);
    
    forn(i,0,n){
        cin >> vec[i];
        seg.update(vec[i], vec[i], {1});
        vals.push_back(vec[i]);
    }

    forn(i,0,q){
        ll t; cin >> t;
        if(t == 1){
            ll x; cin >> n;
            queries[i] = {1,x, -1};
            vals.push_back(x);
        }else{
            ll a, b; cin >> a >> b;
            queries[i] = {2,a, b};
            vals.push_back(a);
            vals.push_back(b);
        }
    }

    sort(vals.begin(), vals.end());

    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto compress = [&](ll& x){
        x = (ll)( lower_bound(vals.begin(), vals.end(), x) - vals.begin() );
    };

    forn(i,0,n) compress(vec[i]);

    forn(i,0,q){
        auto [t, a, b] = queries[i];

        compress(a);
        if(t == 2) compress(b);
        queries[i] = {t, a, b};
    }

    ll idx = n; 
    forn(qq, 0, q){
        auto [t,a,b] = queries[qq];

        if(t == 1){
            ll k = a;
            auto it = ms.lower_bound({k,0});
            if(it == ms.end()){
                ms.insert({k,idx});
                seg.update(k,k,{1});
                idx++;
            }   
            else if(k != it->first){
                ll old_k = it->first;
                ms.erase(it);
                seg.update(old_k,old_k,{-1});
                ms.insert({k,idx});
                seg.update(k,k,{1});
                idx++;
            }
        }else{
            cout << seg.query(a, b).sum << ln;
        }
    }

    return 0;
}   

g++ -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++20 -Wno-unused-result -Wno-sign-compare -DDEBUG   d.cpp   -o d
=================================================================
==32034==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x5070000000e0 at pc 0x5eac775d43ee bp 0x7ffec50ea170 sp 0x7ffec50ea160
READ of size 8 at 0x5070000000e0 thread T0
    #0 0x5eac775d43ed in bool __gnu_cxx::__ops::_Iter_less_val::operator()<__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const>(__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const&) const /usr/include/c++/13/bits/predefined_ops.h:69
    #1 0x5eac775ceb7f in __gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > > std::__lower_bound<__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long, __gnu_cxx::__ops::_Iter_less_val>(__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, __gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const&, __gnu_cxx::__ops::_Iter_less_val) /usr/include/c++/13/bits/stl_algobase.h:1472
    #2 0x5eac775c7c06 in __gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > > std::lower_bound<__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long>(__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, __gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const&) /usr/include/c++/13/bits/stl_algobase.h:1507
    #3 0x5eac775bc9e8 in operator() /home/joao/repos/icpc-training/codeforces/104375/d.cpp:163
    #4 0x5eac775be18f in main /home/joao/repos/icpc-training/codeforces/104375/d.cpp:166
    #5 0x7c0d3922a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #6 0x7c0d3922a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #7 0x5eac775bc664 in _start (/home/joao/repos/icpc-training/codeforces/104375/d+0x3a664) (BuildId: 871c7e6485c08bf8b9a7f98c17f7f63e81c0fee3)

0x5070000000e0 is located 0 bytes after 80-byte region [0x507000000090,0x5070000000e0)
allocated by thread T0 here:
    #0 0x7c0d3a2fe548 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:95
    #1 0x5eac775e2296 in std::__new_allocator<long long>::allocate(unsigned long, void const*) /usr/include/c++/13/bits/new_allocator.h:151
    #2 0x5eac775d2ba9 in std::allocator<long long>::allocate(unsigned long) /usr/include/c++/13/bits/allocator.h:198
    #3 0x5eac775d2ba9 in std::allocator_traits<std::allocator<long long> >::allocate(std::allocator<long long>&, unsigned long) /usr/include/c++/13/bits/alloc_traits.h:482
    #4 0x5eac775d2ba9 in std::_Vector_base<long long, std::allocator<long long> >::_M_allocate(unsigned long) /usr/include/c++/13/bits/stl_vector.h:381
    #5 0x5eac775cfd31 in std::_Vector_base<long long, std::allocator<long long> >::_M_create_storage(unsigned long) /usr/include/c++/13/bits/stl_vector.h:398
    #6 0x5eac775c9708 in std::_Vector_base<long long, std::allocator<long long> >::_Vector_base(unsigned long, std::allocator<long long> const&) /usr/include/c++/13/bits/stl_vector.h:335
    #7 0x5eac775c4448 in std::vector<long long, std::allocator<long long> >::vector(unsigned long, std::allocator<long long> const&) /usr/include/c++/13/bits/stl_vector.h:557
    #8 0x5eac775bcfd0 in main /home/joao/repos/icpc-training/codeforces/104375/d.cpp:132
    #9 0x7c0d3922a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #10 0x7c0d3922a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #11 0x5eac775bc664 in _start (/home/joao/repos/icpc-training/codeforces/104375/d+0x3a664) (BuildId: 871c7e6485c08bf8b9a7f98c17f7f63e81c0fee3)

SUMMARY: AddressSanitizer: heap-buffer-overflow /usr/include/c++/13/bits/predefined_ops.h:69 in bool __gnu_cxx::__ops::_Iter_less_val::operator()<__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const>(__gnu_cxx::__normal_iterator<long long*, std::vector<long long, std::allocator<long long> > >, long long const&) const
Shadow bytes around the buggy address:
  0x506ffffffe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x506ffffffe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x506fffffff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x506fffffff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x507000000000: fa fa fa fa 00 00 00 00 00 00 00 00 04 fa fa fa
=>0x507000000080: fa fa 00 00 00 00 00 00 00 00 00 00[fa]fa fa fa
  0x507000000100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x507000000180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x507000000200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x507000000280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x507000000300: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==32034==ABORTING