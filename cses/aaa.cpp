#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

static bool det_nonzero_bareiss(vector<vector<i64>> a) {
    int n = (int)a.size();
    i64 prev = 1, sign = 1;
    for (int k = 0; k < n; ++k) {
        int piv = k;
        while (piv < n && a[piv][k] == 0) ++piv;
        if (piv == n) return false;
        if (piv != k) {
            swap(a[piv], a[k]);
            sign = -sign;
        }
        i64 akk = a[k][k];
        for (int i = k + 1; i < n; ++i) {
            for (int j = k + 1; j < n; ++j) {
                i128 num = (i128)a[i][j] * akk - (i128)a[i][k] * a[k][j];
                if (prev != 1) num /= prev;
                a[i][j] = (i64)num;
            }
        }
        prev = akk;
        if (k + 1 < n) {
            for (int i = k + 1; i < n; ++i) a[i][k] = 0;
        }
    }
    i128 det = (i128)sign * (i128)a[n-1][n-1];
    return det != 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    if (n <= 0) return 0;

    const long long free_bits = 1LL * (n - 1) * (n - 1);
    if (free_bits > 60) {
        cerr << "Free bits = " << free_bits << " too large (limit 60).\n";
        return 0;
    }

    unsigned __int128 total = (free_bits == 0 ? 1 : (1ULL << free_bits));
    unsigned long long invertible = 0, singular = 0;

    for (unsigned long long mask = 0; mask < (unsigned long long)total; ++mask) {
        vector<vector<i64>> A(n, vector<i64>(n, 1));
        for (int i = 1; i < n; ++i) A[i][0] = 1;
        for (int j = 1; j < n; ++j) A[0][j] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                long long idx = 1LL * (i - 1) * (n - 1) + (j - 1);
                bool bit = (mask >> idx) & 1ULL;
                A[i][j] = bit ? 1 : -1;
            }
        }
        if (det_nonzero_bareiss(A)) ++invertible;
        else ++singular;
    }

    cout << "n = " << n << "\n";
    cout << "Fixed first row/col = +1\n";
    cout << "Total matrices: " << (unsigned long long)total << "\n";
    cout << "Invertible: " << invertible << "\n";
    cout << "Singular:   " << singular << "\n";
    return 0;
}
