#include "bits/stdc++.h"
using namespace std;

static long long charCmpCount = 0;

int lcpCompare(const string& a, const string& b, int k) {
    int la = (int)a.size();
    int lb = (int)b.size();

    while (k < la && k < lb) {
        charCmpCount++;
        if (a[k] != b[k]) {
            return (unsigned char)a[k] < (unsigned char)b[k] ? -1 : 1;
        }
        k++;
    }

    if (la == lb) return 0;
    return la < lb ? -1 : 1;
}

void stringMerge(vector<string>& a, vector<int>& lcpL, vector<int>& lcpR,
                 vector<string>& buf, vector<int>& lcpBuf,
                 int l, int m, int r) {
    int i = l, j = m, k = l;

    while (i < m && j < r) {
        int lh = lcpL[i];
        int rh = lcpR[j];

        if (lh > rh) {
            buf[k] = a[i];
            lcpBuf[k] = lh;
            i++;
        } else if (lh < rh) {
            buf[k] = a[j];
            lcpBuf[k] = rh;
            j++;
        } else {
            int common = lh;
            int cmp = lcpCompare(a[i], a[j], common);
            int newLcp = common;

            int la = (int)a[i].size();
            int lb = (int)a[j].size();
            while (newLcp < la && newLcp < lb && a[i][newLcp] == a[j][newLcp]) {
                newLcp++;
            }

            if (cmp <= 0) {
                buf[k] = a[i];
                lcpBuf[k] = lh;
                i++;
                lcpR[j] = newLcp;
            } else {
                buf[k] = a[j];
                lcpBuf[k] = rh;
                j++;
                lcpL[i] = newLcp;
            }
        }
        k++;
    }

    while (i < m) {
        buf[k] = a[i];
        lcpBuf[k] = lcpL[i];
        i++; k++;
    }
    while (j < r) {
        buf[k] = a[j];
        lcpBuf[k] = lcpR[j];
        j++; k++;
    }

    for (int t = l; t < r; t++) {
        a[t] = buf[t];
        lcpL[t] = lcpBuf[t];
        lcpR[t] = lcpBuf[t];
    }
}

void stringMergeSort(vector<string>& a, vector<int>& lcpL, vector<int>& lcpR,
                     vector<string>& buf, vector<int>& lcpBuf,
                     int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    stringMergeSort(a, lcpL, lcpR, buf, lcpBuf, l, m);
    stringMergeSort(a, lcpL, lcpR, buf, lcpBuf, m, r);
    stringMerge(a, lcpL, lcpR, buf, lcpBuf, l, m, r);
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

    vector<int> lcpL(n, 0), lcpR(n, 0);
    vector<string> buf(n);
    vector<int> lcpBuf(n, 0);

    stringMergeSort(a, lcpL, lcpR, buf, lcpBuf, 0, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}
