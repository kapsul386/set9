#include "bits/stdc++.h"
using namespace std;

static long long charCmpCount = 0;

inline int charAt(const string& s, int d) {
    if (d < (int)s.size()) {
        charCmpCount++;
        return (unsigned char)s[d];
    }
    return -1;
}

void stringQuickSort(vector<string>& a, int lo, int hi, int d) {
    if (hi - lo <= 1) return;

    int mid = lo + (hi - lo) / 2;
    if (a[lo].size() > d && a[mid].size() > d && a[hi - 1].size() > d) {
        char x = a[lo][d], y = a[mid][d], z = a[hi - 1][d];
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);
        if (a[mid][d] != y) {
            for (int i = lo; i < hi; i++) {
                if (a[i][d] == y) { swap(a[lo], a[i]); break; }
            }
        } else {
            swap(a[lo], a[mid]);
        }
    }

    int pivot = charAt(a[lo], d);
    int lt = lo, gt = hi - 1;
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < pivot) {
            swap(a[lt], a[i]);
            lt++; i++;
        } else if (t > pivot) {
            swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }

    stringQuickSort(a, lo, lt, d);
    if (pivot >= 0) stringQuickSort(a, lt, gt + 1, d + 1);
    stringQuickSort(a, gt + 1, hi, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    stringQuickSort(a, 0, n, 0);

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}
