#ifndef SET9_SORT_ALGORITHMS_H
#define SET9_SORT_ALGORITHMS_H

#include "bits/stdc++.h"
using namespace std;

namespace sorts {

inline int charAt(const string& s, int d, long long& cmpCount) {
    if (d < (int)s.size()) {
        cmpCount++;
        return (unsigned char)s[d];
    }
    return -1;
}

inline int charAtRadix(const string& s, int d, long long& cmpCount) {
    if (d < (int)s.size()) {
        cmpCount++;
        return (unsigned char)s[d] + 1;
    }
    return 0;
}

inline int plainCompare(const string& a, const string& b, long long& cmpCount) {
    int la = (int)a.size();
    int lb = (int)b.size();
    int k = 0;
    while (k < la && k < lb) {
        cmpCount++;
        if (a[k] != b[k]) return (unsigned char)a[k] < (unsigned char)b[k] ? -1 : 1;
        k++;
    }
    if (la == lb) return 0;
    return la < lb ? -1 : 1;
}

inline int lcpCompare(const string& a, const string& b, int k, long long& cmpCount) {
    int la = (int)a.size();
    int lb = (int)b.size();
    while (k < la && k < lb) {
        cmpCount++;
        if (a[k] != b[k]) return (unsigned char)a[k] < (unsigned char)b[k] ? -1 : 1;
        k++;
    }
    if (la == lb) return 0;
    return la < lb ? -1 : 1;
}

// ---------- Стандартный QUICKSORT (на основе std::sort + кастомный компаратор) ----------
inline void standardQuickSort(vector<string>& a, long long& cmpCount) {
    sort(a.begin(), a.end(), [&](const string& x, const string& y) {
        return plainCompare(x, y, cmpCount) < 0;
    });
}

// ---------- Стандартный MERGESORT (std::stable_sort + кастомный компаратор) ----------
inline void standardMergeSort(vector<string>& a, long long& cmpCount) {
    stable_sort(a.begin(), a.end(), [&](const string& x, const string& y) {
        return plainCompare(x, y, cmpCount) < 0;
    });
}

// ---------- STRING MERGESORT с lcpCompare ----------
inline void stringMergeImpl(vector<string>& a, vector<int>& lcpL, vector<int>& lcpR,
                            vector<string>& buf, vector<int>& lcpBuf,
                            int l, int m, int r, long long& cmpCount) {
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
            int cmp = lcpCompare(a[i], a[j], common, cmpCount);
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

inline void stringMergeRec(vector<string>& a, vector<int>& lcpL, vector<int>& lcpR,
                           vector<string>& buf, vector<int>& lcpBuf,
                           int l, int r, long long& cmpCount) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    stringMergeRec(a, lcpL, lcpR, buf, lcpBuf, l, m, cmpCount);
    stringMergeRec(a, lcpL, lcpR, buf, lcpBuf, m, r, cmpCount);
    stringMergeImpl(a, lcpL, lcpR, buf, lcpBuf, l, m, r, cmpCount);
}

inline void stringMergeSort(vector<string>& a, long long& cmpCount) {
    int n = (int)a.size();
    if (n <= 1) return;
    vector<int> lcpL(n, 0), lcpR(n, 0);
    vector<string> buf(n);
    vector<int> lcpBuf(n, 0);
    stringMergeRec(a, lcpL, lcpR, buf, lcpBuf, 0, n, cmpCount);
}

// ---------- Тернарный STRING QUICKSORT ----------
inline void stringQuickRec(vector<string>& a, int lo, int hi, int d, long long& cmpCount) {
    if (hi - lo <= 1) return;

    int mid = lo + (hi - lo) / 2;
    if ((int)a[lo].size() > d && (int)a[mid].size() > d && (int)a[hi - 1].size() > d) {
        char x = a[lo][d], y = a[mid][d], z = a[hi - 1][d];
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);
        if (a[mid][d] != y) {
            for (int i = lo; i < hi; i++) {
                if ((int)a[i].size() > d && a[i][d] == y) { swap(a[lo], a[i]); break; }
            }
        } else {
            swap(a[lo], a[mid]);
        }
    }

    int pivot = charAt(a[lo], d, cmpCount);
    int lt = lo, gt = hi - 1;
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d, cmpCount);
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

    stringQuickRec(a, lo, lt, d, cmpCount);
    if (pivot >= 0) stringQuickRec(a, lt, gt + 1, d + 1, cmpCount);
    stringQuickRec(a, gt + 1, hi, d, cmpCount);
}

inline void stringQuickSort(vector<string>& a, long long& cmpCount) {
    stringQuickRec(a, 0, (int)a.size(), 0, cmpCount);
}

// ---------- MSD RADIX SORT (без переключения) ----------
static const int RADIX_ALPHA = 256;

inline void msdRadixRec(vector<string>& a, vector<string>& buf, int lo, int hi, int d, long long& cmpCount) {
    if (hi - lo <= 1) return;

    vector<int> cnt(RADIX_ALPHA + 2, 0);

    for (int i = lo; i < hi; i++) {
        cnt[charAtRadix(a[i], d, cmpCount) + 1]++;
    }
    for (int c = 0; c < RADIX_ALPHA + 1; c++) {
        cnt[c + 1] += cnt[c];
    }

    vector<int> head(RADIX_ALPHA + 2);
    for (int c = 0; c < RADIX_ALPHA + 2; c++) head[c] = cnt[c];

    for (int i = lo; i < hi; i++) {
        int c = charAtRadix(a[i], d, cmpCount);
        buf[lo + cnt[c]++] = a[i];
    }
    for (int i = lo; i < hi; i++) {
        a[i] = buf[i];
    }

    for (int c = 1; c < RADIX_ALPHA + 1; c++) {
        int l = lo + head[c];
        int r = lo + head[c + 1];
        if (r - l > 1) {
            msdRadixRec(a, buf, l, r, d + 1, cmpCount);
        }
    }
}

inline void msdRadixSort(vector<string>& a, long long& cmpCount) {
    if (a.empty()) return;
    vector<string> buf(a.size());
    msdRadixRec(a, buf, 0, (int)a.size(), 0, cmpCount);
}

// ---------- MSD RADIX SORT с переключением на тернарный QUICKSORT при |фрагмента| < 74 ----------
static const int SWITCH_THRESHOLD = 74;

inline void msdRadixQuickRec(vector<string>& a, vector<string>& buf, int lo, int hi, int d, long long& cmpCount) {
    if (hi - lo <= 1) return;

    if (hi - lo < SWITCH_THRESHOLD) {
        stringQuickRec(a, lo, hi, d, cmpCount);
        return;
    }

    vector<int> cnt(RADIX_ALPHA + 2, 0);

    for (int i = lo; i < hi; i++) {
        cnt[charAtRadix(a[i], d, cmpCount) + 1]++;
    }
    for (int c = 0; c < RADIX_ALPHA + 1; c++) {
        cnt[c + 1] += cnt[c];
    }

    vector<int> head(RADIX_ALPHA + 2);
    for (int c = 0; c < RADIX_ALPHA + 2; c++) head[c] = cnt[c];

    for (int i = lo; i < hi; i++) {
        int c = charAtRadix(a[i], d, cmpCount);
        buf[lo + cnt[c]++] = a[i];
    }
    for (int i = lo; i < hi; i++) {
        a[i] = buf[i];
    }

    for (int c = 1; c < RADIX_ALPHA + 1; c++) {
        int l = lo + head[c];
        int r = lo + head[c + 1];
        if (r - l > 1) {
            msdRadixQuickRec(a, buf, l, r, d + 1, cmpCount);
        }
    }
}

inline void msdRadixQuickSort(vector<string>& a, long long& cmpCount) {
    if (a.empty()) return;
    vector<string> buf(a.size());
    msdRadixQuickRec(a, buf, 0, (int)a.size(), 0, cmpCount);
}

} // namespace sorts

#endif
