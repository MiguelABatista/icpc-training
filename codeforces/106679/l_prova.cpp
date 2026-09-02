#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define forn(i,s,e) for(ll i=s; i<e; i++)
#define sz(u) ((ll) u.size())
#define ln "\n"

#ifdef DEBUG
#define trace(u) u
#define _
#else
#define trace(u)
#define _ ios::sync_with_stdio(0); cin.tie(0)
#endif

#define debug(u) trace(cout << #u " = " << u << ln);
#define debugv(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx << " ";cout << ln);
#define debugm(v) trace(cout << #v ": " ;for(auto xx : v) cout << xx.first << ":" << xx.second << " ";cout << ln)

const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll NUMBLOCOS = 10;
const ll HEIGHT = 100;

int main(){
    _;
    vector<vector<char>> lab(HEIGHT, vector<char> (4*NUMBLOCOS, '.'));
    forn(bloco, 0, NUMBLOCOS){
        forn(h, 0, HEIGHT){
            if(h!= 1) lab[h][4*bloco + 1] = '#';
            if(h!= 0) lab[h][4*bloco + 3] = '#';
        }

        lab[1][4*bloco + 2] = '/';
        if(bloco != NUMBLOCOS-1) lab[HEIGHT - 1][4*bloco+2] = 'X';
    }

    lab[0][0] = '*';
    lab[0][4*NUMBLOCOS - 1] = 'F';
    lab[1][4*NUMBLOCOS - 2] = '\\';
    lab[HEIGHT-1][0] = 'X';

    cout << HEIGHT << " " << 4*NUMBLOCOS << ln;

    forn(i, 0, HEIGHT){
        forn(j, 0, 4*NUMBLOCOS){
            cout << lab[i][j];
        }
        cout << ln;
    }

    return 0;
}