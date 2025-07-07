#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ (void)0
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll n, p, h;
v64 mult;
v64 sum;
ll att = 0;
ll totsum = 0;
ll totmult = 1;

ll sem_mult_sem_sum(){
    ll porrada = att*p;
    ll qtd;
    if(h%porrada == 0){
        qtd = h/porrada - 1;
    }else{
        qtd = h/porrada;
    }
    h -= qtd*porrada;
    return qtd;
}

ll sem_mult(){
    ll l = 0; 
    ll r = 1'000'000;
    ll mid;
    ll ans = 0;
    while(l <= r){
        mid = (l+r)/2;
        ll porrada;
        if(mid*(mid+1)/2 > INF/totsum){
            porrada = INF;
        }else{
            porrada = att*(mid*p + (mid*(mid+1)/2)*totsum);
        }
        
        if(porrada < h){
            ans = mid;
            l = mid+1;
        } else{
            r = mid-1;
        }
    }

    h -= att*(ans*p + (ans*(ans+1)/2)*totsum);
    p += ans*totsum;
    
    return ans;
}

ll com_mult(){
    ll cnt = 0;
    ll prox = (p + totsum)*totmult;

    while (true){   
        if(att*prox < h){
            cnt++;
            p = prox;
            h -= att*prox;
            prox = (p + totsum)*totmult;
        }else{
            return cnt;
        }
    }
}

int main() {
    _;
    cin >> n >> p >> h;
    bool fudeo = false;
    forn(i,0,n){
        char c;
        cin >> c;
        if(c == '!'){
            att++;
        }else if(c == '*'){
            ll x; cin >> x;
            mult.push_back(x);
            totmult *= x;
            if(totmult > 1'000'000'000){
                fudeo = true;
            }
        } else if(c == '+'){
            ll x; cin >> x;
            sum.push_back(x);
            totsum += x;
        }
    }

    sort(mult.rbegin(), mult.rend());
    sort(sum.rbegin(), sum.rend());

    if((p == 0 && totsum == 0) || att == 0){
        cout << '*' << ln;
        return 0;
    }

    ll ans = 0;

    if(!fudeo){
        if(totsum == 0 && totmult == 1){
            ll aux = sem_mult_sem_sum();
            ans += aux*n;
        }else if(totmult == 1){
            ll aux = sem_mult();
            ans += aux*n;
        }else{
            ll aux = com_mult();
            ans += aux*n;
        }
    }
        
    ll best = INF;
 
    forn(qs, 0, sum.size()+1){
        forn(qm, 0, mult.size()+1){
            forn(qa, 1, att+1){ 
                ll temp = p;
                bool sai = false;
                forn(i,0,qs){
                    temp += sum[i];
                }
                forn(i,0,qm){
                    if(temp > 1'000'000'000){
                        best = min(best, qs+qm+1);
                        sai = true;
                        continue;
                    }
                    temp *= mult[i];
                }
                if(sai) continue;
                temp *= qa;
                if(h <= temp){
                    best = min(best, qs+qm+qa);
                }
            }
        }
    }

    cout << ans + best << ln;
    return 0;
}