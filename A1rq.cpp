#include "bits/stdc++.h"
using namespace std;

static long long charCmpCount = 0;
static const int ALPHA = 256;
static const int SWITCH_THRESHOLD = 74;

inline int charAt(const string& s, int d) {
    if (d < (int)s.size()) {
        charCmpCount++;
        return (unsigned char)s[d] + 1;
    }
    return 0;
}

inline int charAtCmp(const string& s, int d) {
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

    int pivot = charAtCmp(a[lo], d);
    int lt = lo, gt = hi - 1;
    int i = lo + 1;

    while (i <= gt) {
        int t = charAtCmp(a[i], d);
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

void msdRadixQuickSort(vector<string>& a, vector<string>& buf, int lo, int hi, int d) {
    if (hi - lo <= 1) return;

    if (hi - lo < SWITCH_THRESHOLD) {
        stringQuickSort(a, lo, hi, d);
        return;
    }

    vector<int> cnt(ALPHA + 2, 0);

    for (int i = lo; i < hi; i++) {
        cnt[charAt(a[i], d) + 1]++;
    }

    for (int c = 0; c < ALPHA + 1; c++) {
        cnt[c + 1] += cnt[c];
    }

    vector<int> head(ALPHA + 2);
    for (int c = 0; c < ALPHA + 2; c++) head[c] = cnt[c];

    for (int i = lo; i < hi; i++) {
        int c = charAt(a[i], d);
        buf[lo + cnt[c]++] = a[i];
    }

    for (int i = lo; i < hi; i++) {
        a[i] = buf[i];
    }

    for (int c = 1; c < ALPHA + 1; c++) {
        int l = lo + head[c];
        int r = lo + head[c + 1];
        if (r - l > 1) {
            msdRadixQuickSort(a, buf, l, r, d + 1);
        }
    }
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

    vector<string> buf(n);
    msdRadixQuickSort(a, buf, 0, n, 0);

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}
