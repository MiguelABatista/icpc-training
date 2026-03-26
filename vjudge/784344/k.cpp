#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128_t lll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

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
const lll POT10 = (ll)1e18;

ll cnt = 0;
set<lll> resp;
vector<lll> pot2(82);

void prep(){
    pot2[0] = 1;
    forn(i,1,82) pot2[i] = 2*pot2[i-1];
}


void print(v64& vec){
    vector<string> s(9, string(9, '.'));
    forn(i,0,9) s[i][vec[i]] = '#';
    forn(i,0,9) cout << s[i] << ln;
    cout << ln;
}


void flip(v64& vec){
    forn(i,0,9) vec[i] = 8-vec[i];
}


void rot(v64& vec){
    v64 aux(9);
    forn(i,0,9) aux[vec[i]] = i;
    forn(i,0,9) vec[i] = aux[8-i];
}


lll calc(v64 vec){
    lll ans = 0;
    forn(i,0,9){
        ans += pot2[9*i+vec[i]];
    }
    return ans;
}

void test(v64 vec){
    forn(i,0,9){
        forn(j,i+1,9){
            if(j-i == abs(vec[i]-vec[j])) return;
        }
    }
    cnt++;
    lll ans = calc(vec);
    forn(i,0,4){
        rot(vec);
        ans = min(ans, calc(vec));
    }

    flip(vec);
    ans = min(ans, calc(vec));

    forn(i,0,3){
        rot(vec);
        ans = min(ans, calc(vec));
    }

    // cout << (ll)ans << ln;
    resp.insert(ans);
}

int main() {
    _;
    prep();
    v64 vec = {0,1,2,3,4,5,6,7,8};

    ll amt = 0;

    do{
        test(vec);    
        amt++;
        
    }while(next_permutation(vec.begin(), vec.end()));

    
    for(lll x: resp){
        lll pri = x/POT10;
        lll seg = x%POT10;
        cout << (ll)pri << (ll)seg << ln;
    }
    
    // cout << "CORRIGIR PRINT " << ln;
    return 0;
}


// 4759840935507574947856
// 37798540535820636391456

//GABA 4759840935507574947856
//GABA 37798540535820636391456

