#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ln '\n'

ll binary_search(vector<ll>& nums, ll difference) {
    ll right = nums.size() - 1;
    ll left = 0;
    ll mid = (left + mid) / 2;
    while (left <= right) {
        ll mid = (left + right) / 2;
        if (nums[mid] == difference) {
            return nums[mid];
            // auto end = find(input.begin(), input.end(), nums[left]);
            // auto start = find(input.begin(), input.end(), nums[right]);

            // ll pos_1 = (start - input.begin()) + 1;
            // ll pos_2 = (end - input.begin()) + 1;
            // if (pos_2 > pos_1) {
            //     cout << pos_1 << " " << pos_2 << ln;
            // } else {
            //     cout << pos_2 << " " << pos_1 << ln;
            // }
            // return true;;
        }

        if (nums[mid] < difference) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, x;
    cin >> n >> x;

    vector<ll> nums;
    for (ll i = 0; i < n; i++) {
        ll num;
        cin >> num;
        nums.push_back(num);
    }
    vector<ll> nums_ordered = nums;
    sort(nums_ordered.begin(), nums_ordered.end());
    bool is_found = false;
    for (auto it = nums.begin(); it != nums.end(); it++) {
        ll temp = *it;
        ll difference = x - temp;
        ll result = binary_search(nums_ordered, difference);
        if (result != -1) {
            auto it_ans = find(++it,nums.end(), result);
            if (it_ans == nums.end()) break;
            cout << (it - nums.begin()) << " " << (it_ans - nums.begin()) + 1 << ln;
            is_found = true;
            break;
        }
    }
    if (!is_found) cout << "IMPOSSIBLE" << ln;
    // if (!binary_search(nums_ordered, x, nums)) cout << "IMPOSSIBLE" << ln;
}