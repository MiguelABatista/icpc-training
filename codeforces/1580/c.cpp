#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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
const ll SQRT = 315;
ll n, m;

struct train{
    ll x, y;
    ll start = -1;
    bool grande = false;
    v64& vec;
    
    train();
    train(ll x_, ll y_, v64& v_) : vec(v_) {
        x = x_;
        y = y_;
        if(x+y >= SQRT) grande = true;
    }

    void ativa(ll d){
        start = d%(x+y);

        if(grande){
            forn(i,0,m){
                if( d + x + (x+y)*i >= m) break;
                
                vec[d + x + (x+y)*i]++;
                
                if(d+(x+y)*(i+1) >= m) break;
                
                vec[d + x+y + (x+y)*(i)]--;
            }
        }
        
        if(!grande){
            vec[(d+x)%(x+y)]++;
            vec[d%(x+y)]--;
        }
    }

    ll desativa(ll d){
        if(grande){
            forn(i,0,m){
                if( start + x + (x+y)*i >= m) break;
                
                vec[start + x + (x+y)*i]--;
                
                if(start+(x+y)*(i+1) >= m) break;
                
                vec[start + (x+y)*(i+1)]++;
            }

            d -= start;
            d %= (x+y);
            if(d < x) return 0;
            return 1;
        }
        
        if(!grande){
            vec[(start+x)%(x+y)]--;
            vec[start%(x+y)]++;

            d -= start;
            d %= (x+y);
            if(d < x) return 0;
            return 1;
        }
        return INF;
    }   
};

int main(){
    _;
    cin >> n >> m;

    vector<v64> mat(SQRT);

    v64 vec_grande(m+1,0);

    vector<train> vec;

    forn(i,0,SQRT){
        mat[i].resize(i);
    }

    forn(i,0,n){
        ll x, y; cin >> x >> y;
        
        if(x+y < SQRT){
            vec.push_back(train(x,y,mat[x+y])); 
        }else{
            vec.push_back(train(x,y,vec_grande));             
        }
    }
    
    ll curr = 0;

    forn(d,0,m){
        ll op, k; cin >> op >> k;
        k--;
        
        curr += vec_grande[d];
        
        forn(i,2,SQRT){
            curr += mat[i][d%i];
        }
           
        if(op == 2) curr -= vec[k].desativa(d);
        if(op == 1) vec[k].ativa(d);

        cout << curr << ln;
    }
    return 0;
}