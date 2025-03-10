#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64; 
typedef vector<ll> v64;

#define forn(i, s, e) for(ll i = (s); i < (e); i++)
#define ln "\n"

#if defined(DEBUG) || defined(debug)
    #define _ ios_base::sync_with_stdio(false), cin.tie(NULL)
    #define debug(x) cout << __LINE__ << ": " << #x << " = " << x << ln
#else
    #define _ (void)0
    #define debug(x) (void)0
#endif

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll pergunta(char c){
    cout << "? " << c << ln;
    cout.flush();
    ll aux;
    cin >> aux;
    return aux;
}


int main(){
    _;

    ll r = pergunta('R');
    ll aux;
    ll posicao = 1;
    ll prox_salto = 2;

    while(posicao + prox_salto <= r){
        debug(posicao);
        debug(prox_salto);
        aux = pergunta('R');
        posicao += prox_salto;
        prox_salto++;
    }

    while(posicao + 1 <= r){
        debug(posicao);
        debug(prox_salto);
        aux = pergunta('L');
        aux = pergunta('R');
        posicao += 1;
        prox_salto++;
    }

    r = aux;
    // estou no ponto (0,a) e quero chegar no ponto (r/2, a-r/2)

    
    cout << posicao << ln;
    return 0;
}