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

#define debugv(v) trace({cout << #v": "; for (auto x : v) cout<< x << " "; cout << ln;})
#define debug(x) trace(cout << __LINE__ << ": " #x " = " << x << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;

bool knapsack(vector<p64>& books, ll idx, ll c1, ll c2, set<ll>& ans, ll mini){
    ans.clear();
    v64 sums(c1+1, -1);
    sums[0] = -2;
    
    ll tot = 0;
    forn(i,0,idx){
        tot += books[i].second;
        for(ll j = c1; j >= 0; j--){
            if(j+ books[i].second > c1) continue;
            if(sums[j] == -1) continue;
            if(sums[j+ books[i].second] != -1) continue;
            sums[j+ books[i].second] = i;
        }
        if(books[i].second > c1) continue;
        if(sums[books[i].second] != -1) continue;
        sums[books[i].second] = i;
    }

    forn(i, max(tot-c2, mini), c1+1){
        if(sums[i] != -1){
            ll x = i;
            while(x > 0){
                ans.insert(sums[x]);
                x -= books[sums[x]].second;
            }
            return true;
        }

    }
    return false;
}

bool testa(vector<p64>& books, ll h, ll w, set<ll> ans, set<ll> ans2){
    for(ll x: ans2) ans.insert(x);
    ll n = sz(books);
    ll test_altura_pilha_deitada = 0;
    ll test_altura_pilha_pe = 0;
    ll test_largura_pilha_deitada = 0;
    ll test_largura_pilha_pe = 0;

    for(ll x : ans){
        test_altura_pilha_pe = max(test_altura_pilha_pe, books[x].first);
        test_largura_pilha_pe += books[x].second;
    }

    forn(x,0,n) if(ans.count(x) == 0){
        test_altura_pilha_deitada = max(test_altura_pilha_deitada, books[x].first);
        test_largura_pilha_deitada += books[x].second;
    }

    if(test_altura_pilha_pe > h) return false;
    if(test_largura_pilha_deitada > h) return false ;
    if(test_largura_pilha_pe + test_altura_pilha_deitada > w) return false;
    return true;
}

int main(){
    ll n, h, w; cin >> n >> h >> w;

    vector<pair<p64, ll>> books_input(n);
    forn(i,0,n){
        cin >> books_input[i].first.first >> books_input[i].first.second;
        books_input[i].second = i;
    }

    sort(books_input.begin(), books_input.end());
    v64 mpidx(n);
    vector<p64> books(n);

    forn(i,0,n){
        books[i] = books_input[i].first;
        mpidx[i] = books_input[i].second;
    }

    ll altura_pilha_deitada = 0;
    // ll altura_pilha_pe = 0;
    ll largura_pilha_deitada = 0;
    ll largura_pilha_pe = 0;


    ll curr_idx = n-1;
    
    set<ll> ans;
    set<ll> ans2;

    for(; curr_idx >= 0; curr_idx--){
        if(books[curr_idx].first > h){
            largura_pilha_deitada = max(largura_pilha_deitada, books[curr_idx].first);
            altura_pilha_deitada += books[curr_idx].second;
        }else{
            break;
        }
    }

    bool bom = false;
    debug(altura_pilha_deitada);
    if(altura_pilha_deitada != 0){
        ll c1 = w - largura_pilha_deitada;
        ll c2 = h - altura_pilha_deitada;
        
        if(c1 >= 0 && c2 >= 0){
            if(knapsack(books, curr_idx+1, c1, c2, ans, 1)){
                if(testa(books, h, w, ans, ans2)){
                    bom = true;
                }
            }
            
        }
    }

    ll mini = 1;
    for(; curr_idx >= 0; curr_idx--){
        if(bom) break;

        ll c1 = w - (max(largura_pilha_deitada, books[curr_idx].first) + largura_pilha_pe);
        ll c2 = h - (altura_pilha_deitada +  books[curr_idx].second);
        if(c1 < 0 || c2 < 0) continue;

        if(knapsack(books, curr_idx, c1, c2, ans, mini)){
            if(testa(books, h, w, ans, ans2)){
                bom = true;
                break;
            }
        }

        if(curr_idx == 0){            
            if(testa(books, h, w, ans, ans2)) bom = true;
            break;
        }
        
        largura_pilha_pe += books[curr_idx].second;
        mini = 0;
        ans2.insert(curr_idx);
    }


    ll test_altura_pilha_deitada = 0;
    ll test_altura_pilha_pe = 0;
    ll test_largura_pilha_deitada = 0;
    ll test_largura_pilha_pe = 0;
    for(ll x: ans2) ans.insert(x);

    if(!bom){
        cout << "impossible" << ln;
        return 0;
    }
    if (ans.empty() || (ll)ans.size() == n) { cout << "impossible\n"; return 0; }

    for(ll x : ans){
        test_altura_pilha_pe = max(test_altura_pilha_pe, books[x].first);
        test_largura_pilha_pe += books[x].second;
    }

    forn(x,0,n) if(ans.count(x) == 0){
        test_altura_pilha_deitada = max(test_altura_pilha_deitada, books[x].first);
        test_largura_pilha_deitada += books[x].second;
    }

    assert(test_altura_pilha_pe <= h);
    assert(test_largura_pilha_deitada <= h);
    assert(test_largura_pilha_pe + test_altura_pilha_deitada <= w);

    cout << "upright ";
    for(ll x : ans) cout << mpidx[x]+1 << " ";;cout << ln;
    vector<p64> aux;
    forn(x,0,n) if(ans.count(x) == 0){
        aux.emplace_back(books[x].first, x);
    }
    sort(aux.rbegin(), aux.rend());
    cout << "stacked ";
    for(auto p: aux) cout << mpidx[p.second]+1 << " ";; cout << ln;

}