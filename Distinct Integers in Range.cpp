// Problem link - https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/distinct-integers-in-range-66eca44b/
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// build segment tree
void buildSeg(int ind, int low, int high, vector<int>& v, vector<bitset<5001>>& seg) {
    // base case
    if (low == high) {
        seg[ind].set(v[low]);
        return;
    }

    // recursive calls and small calculation
    int mid = (low + high) / 2;
    buildSeg(ind * 2 + 1, low, mid, v, seg);
    buildSeg(ind * 2 + 2, mid + 1, high, v, seg);

    seg[ind] = seg[ind * 2 + 1] | seg[ind * 2 + 2];
}

// search in range
bitset<5001> searchInRange(int ind, int low, int high, int l, int r, vector<bitset<5001>>& seg) {
    // no overlapping
    if (high < l || low > r) {
        return bitset<5001>();
    }

    // complete overlapping
    if (low >= l && high <= r)
        return seg[ind];

    // partial overlapping
    int mid = (low + high) / 2;
    bitset<5001> left = searchInRange(ind * 2 + 1, low, mid, l, r, seg);
    bitset<5001> right = searchInRange(ind * 2 + 2, mid + 1, high, l, r, seg);

    return left | right;
}

int main() {
    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);

    for (auto& it : A)
        cin >> it;

    for (auto& it : B)
        cin >> it;

    vector<bitset<5001>> seg1(n * 4);
    vector<bitset<5001>> seg2(n * 4);

    buildSeg(0, 0, n - 1, A, seg1);
    buildSeg(0, 0, n - 1, B, seg2);

    int q;
    cin >> q;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        a--, b--, c--, d--;

        bitset<5001> first = searchInRange(0, 0, n - 1, a, b, seg1);
        bitset<5001> second = searchInRange(0, 0, n - 1, c, d, seg2);

        int cntDist = 0;
        for (int i = 0; i <= 5000; i++) {
            if (first[i] || second[i])
                cntDist++;
        }

        cout << cntDist << endl;
    }
    return 0;
}
