#include <bits/stdc++.h>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];
    while(k--) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        if(c == 'Q') {
            int mx = 0;
            for(int i = l; i <= r; i++) mx = max(mx, v[i]);
            cout << mx << "\n";
        } else if(c == 'A') {
            for(int i = l; i <= r; i++) v[i]++;
        } else {
            int mx = 0;
            for(int i = 1; i <= n; i++) mx = max(mx, v[i]);
            for(int i = l; i <= r; i++) if(v[i] == mx) v[i] = 0;
        }
    }
    return 0;
}