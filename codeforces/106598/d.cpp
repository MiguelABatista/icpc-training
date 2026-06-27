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


int main() {
    int n; cin >> n;

    vector<vector<char>> mat(2*n+1, vector<char> (10*n, ' '));

    int i = n, j = 0;

    auto sobe = [&](int &i, int &j){
        i--;
    };
    auto desce = [&](int &i, int &j){
        i++;
    };
    auto direita = [&](int &i, int &j){
        j++;
    };
    auto esquerda = [&](int &i, int &j){
        j--;
    };

    for(int cnt = 0; cnt < n; cnt++){
        mat[i][j] = '/';
        sobe(i, j);
        direita(i, j);
    }

    assert(i == 0);

    for(int cnt = 0; cnt < n+1; cnt++){
        mat[i][j] = '_';
        direita(i, j);
    }
    desce(i, j);

    for(int cnt = 0; cnt < n; cnt++){
        mat[i][j] = '\\';
        desce(i, j);
        direita(i, j);
    }
    sobe(i, j);

    for(int cnt = 0; cnt < n+1; cnt++){
        mat[i][j] = '_';
        direita(i, j);
    }
    esquerda(i, j);
    desce(i, j);

    for(int cnt = 0; cnt < n; cnt++){
        mat[i][j] = '/';
        desce(i, j);
        esquerda(i, j);
    }
    sobe(i, j);

    for(int cnt = 0; cnt < n+1; cnt++){
        mat[i][j] = '_';
        esquerda(i, j);
    }

    for(int cnt = 0; cnt < n; cnt++){
        mat[i][j] = '\\';
        sobe(i, j);
        esquerda(i, j);
    }

    for(int cnt = 0; cnt < n; cnt++){
        mat[i][j] = '_';
        esquerda(i, j);
    }

    for(int i = 0; i < 2*n + 1; i++){
        while(mat[i].back() == ' ') mat[i].pop_back();
    }

    for(auto a : mat){
        for(auto b : a){
            cout << b;
        }cout << "\n";
    }



    return 0;
}