#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

int main(){
    ll n; cin >> n;
    vector<ll> c(n, 0), v(n, 0), i(n);

    for(ll j = 0; j < n; j++){
        ll a, b;
        cin >> a >> b;
        c[j] = a;
        v[j] = b;
        if(j!=0) c[j] += c[j-1];
        if(j!=0) v[j] += v[j-1];
        i[j] = c[j] - v[j];
    }

    ll q; cin >> q;
    for(ll j = 0; j < q; j++){
        ll k; cin >> k;
        k--;
        if(i[k] == 0) cout << "NEUTRO";
        if(i[k] > 0) cout << "COMPRA";
        if(i[k] < 0) cout << "VENDA";
        cout << endl;
    }
}