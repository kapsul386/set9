#include "bits/stdc++.h"
using namespace std;

static long long charCmpCount = 0;
static const int ALPHA = 256;

inline int charAt(const string& s, int d) {
    if (d < (int)s.size()) {
        charCmpCount++;
        return (unsigned char)s[d] + 1;
    }
    return 0;
}

void msdRadixSort(vector<string>& a, vector<string>& buf, int lo, int hi, int d) {
    if (hi - lo <= 1) return;

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
            msdRadixSort(a, buf, l, r, d + 1);
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
    msdRadixSort(a, buf, 0, n, 0);

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}
