#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void) 0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
    #define debugp(x) cout << __LINE__ << ": " << #x << " = " << x.first << " " << x.second << ln

#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
    #define debugp(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

const ll MAXN = 50'000;
const ll MAXLOGN = 20;

ll k;
ll smdc[MAXN][MAXLOGN];
p64 smin[MAXN][MAXLOGN];

void build_mdc(v64& v){
    ll sz = v.size();

    forn(i,0,sz) smdc[i][0] = v[i];
    
    for(ll j = 1; (1<<j) <= sz; j++){
        for(ll i = 0; i + (1 << j) <= sz; i++){
            smdc[i][j] = gcd(smdc[i][j-1], smdc[i + (1 << (j-1))][j-1]);
        }
    }
}

ll query_mdc(ll a, ll b){
    ll j = __builtin_clzll(1) - __builtin_clzll(b-a+1);
    return gcd(smdc[a][j], smdc[b - (1 << j) + 1][j]); 
}

void build_min(vector<p64>& v){
    ll sz = v.size();

    forn(i,0,sz) smin[i][0] = v[i];
    
    for(ll j = 1; (1<<j) <= sz; j++){
        for(ll i = 0; i + (1 << j) <= sz; i++){
            p64 p1 = smin[i][j-1];
            p64 p2 = smin[i + (1 << (j-1))][j-1];
            if(p1.first <= p2.first){
                smin[i][j] = p1;
            }else{
                smin[i][j] = p2;
            }
        }
    }
}

p64 query_min(ll a, ll b){
    ll j = __builtin_clzll(1) - __builtin_clzll(b-a+1);
    p64 p1 = smin[a][j];
    p64 p2 = smin[b - (1 << j) + 1][j]; 
    if(p1.first <= p2.first){
        return p1;
    }else{
        return p2;
    }
}

void test(ll l, ll r, vector<p64>& v){
    if(l > r) return ;
    if(l == r) return ;

    ll mdc = query_mdc(l, r-1);
    p64 p_min = query_min(l, r);

    v.push_back({mdc, p_min.first});

    test(l, p_min.second - 1, v);
    test(p_min.second + 1, r, v);
}

bool test2(vector<p64>& v, ll x){
    if(x > k) return false;
    for(auto p: v){
        if(p.first % (p.second + x) != 0) return false;
    }
    return true;
}

void solve(){
    ll n; cin >> n >> k;
    vector<p64> a(n);
    v64 diff(n-1);
    ll worst = INF;
    forn(i, 0, n){
        cin >> a[i].first;
        a[i].second = i;
        if(a[i].first < worst) worst = a[i].first;
        if(i == 0) continue;
        diff[i-1] = a[i].first - a[i-1].first;
    }

    build_mdc(diff);
    build_min(a);

    ll mdc = 0;
    forn(i, 0, n) mdc = gcd(mdc, a[i].first-worst);

    debug(mdc);
    if(mdc == 0){
        cout << k << " " << k*(k+1)/2 << ln;
        return;
    }

    vector<p64> vec;
    test(0,n-1, vec);

    ll sum = 0,count = 0;
    for(ll i = 1; i*i <= mdc; i++){
        
        if(mdc%i != 0) continue;
        if(i > worst && test2(vec, i-worst)){ 
            sum += (i-worst);
            count++;
        }
        
        if((i*i!= mdc) && (mdc/i) > worst){
            if(test2(vec, (mdc/i)-worst)){ 
                sum += (mdc/i)-worst; 
                count++;
            }
        }
    }

    cout << count << " " << sum << ln;
}

int main() { 
    _; ll t; cin >> t;
    while(t--)solve();
    return 0;
}