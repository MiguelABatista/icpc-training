#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;

#define forn(i, s, e) for (ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG)
    #define _ 42
    #define debug(x) cout << __LINE__ << ": "<< #x << " = " << x << ln;
#else
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) 42
#endif
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll MOD = 1'000'000'007;
const ll p = 2;
const ll q = 3;
v64 potp(2001);
v64 potq(2001);

inline ll sum(ll a, ll b){
    a += b;
    return (a < MOD ? a : a - MOD);
}   

inline ll sub(ll a, ll b){
    a -= b;
    return (a >= 0 ? a : a + MOD);
}   

inline ll mult(ll a, ll b){
    return (a*b)%MOD;
}

void prep(){
    potp[0] = 1;
    potq[0] = 1;

    forn(i,1,2001){
        potp[i] = mult(potp[i-1],p);
        potq[i] = mult(potq[i-1],q);
    }
}

int main() {
    _; prep();

    ll hp, wp, hg, wg;
    cin >> hp >> wp >> hg >> wg;
    vector<vector<ll>> pat(hp, v64(wp));
    vector<vector<ll>> grid(hg, v64(wg));
    vector<vector<ll>> hashgrid(hg, v64(wg));

    forn(i,0,hp){
        forn(j,0,wp){
            char aux; cin >> aux;
            if(aux == 'x') pat[i][j] = 0;
            if(aux == 'o') pat[i][j] = 1;
        }
    }


    forn(i,0,hg){
        forn(j,0,wg){
            char aux; cin >> aux;
            if(aux == 'x') grid[i][j] = 0;
            if(aux == 'o') grid[i][j] = 1;
        }
    }

    hashgrid[0][0] = grid[0][0];

    forn(i,1,hg){ // hashgrid[i][0]
        hashgrid[i][0] = sum(mult(potp[i],grid[i][0]), hashgrid[i-1][0]);
    }

    forn(j,1,wg){ // hashgrid[0][j]
        hashgrid[0][j] = sum(mult(potq[j],grid[0][j]), hashgrid[0][j-1]);    
    }

    ll target = 0;
    forn(i,0,hp){
        forn(j,0,wp){
            target = sum(target, mult(pat[i][j], mult(potp[i], potq[j])));
        }
    }
    forn(i,1,hg){
        forn(j,1,wg){
            ll ans = sum(hashgrid[i-1][j], hashgrid[i][j-1]);
            ans = sub(ans, hashgrid[i-1][j-1]);
            ans = sum(ans, mult(grid[i][j], mult(potp[i],potq[j])));
            hashgrid[i][j] = ans;
        }
    }  

    // forn(i,0,hg){
    //     forn(j,0,wg){
    //         cout << hashgrid[i][j] << " ";
    //     }
    //     cout << ln;
    // }  

    ll cnt = 0;
    forn(i,hp-1,hg){
        forn(j,wp-1,wg){
            ll ans = hashgrid[i][j];
            if(i != hp -1){
                ans = sub(ans, hashgrid[i-hp][j]);
            }
            if(j != wp -1){
                ans = sub(ans, hashgrid[i][j-wp]);
            }
            if(i != hp -1 && j != wp -1){
                ans = sum(ans, hashgrid[i-hp][j-wp]);
            }
            // debug(i);
            // debug(j); 
            // debug(ans);
            // debug(mult(target, mult(potp[i-hp+1],potq[j-wp+1])));
            if(ans == mult(target, mult(potp[i-hp+1],potq[j-wp+1])) ){
                cnt++;
                // cout << i << " " << j << ln;
            }

        }
    }

    cout << cnt << ln;
    return 0;
}