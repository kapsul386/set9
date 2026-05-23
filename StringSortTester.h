#ifndef SET9_STRING_SORT_TESTER_H
#define SET9_STRING_SORT_TESTER_H

#include "bits/stdc++.h"
using namespace std;

struct SortResult {
    double avgTimeMs;
    long long charCmpCount;
};

class StringSortTester {
public:
    using SortFn = function<void(vector<string>&, long long&)>;

    StringSortTester(int repeats = 5) : repeats(repeats) {}

    SortResult run(SortFn sortFn, const vector<string>& original) {
        double totalTime = 0.0;
        long long totalCmp = 0;

        for (int r = 0; r < repeats; r++) {
            vector<string> a = original;
            long long cmp = 0;

            auto t0 = chrono::high_resolution_clock::now();
            sortFn(a, cmp);
            auto t1 = chrono::high_resolution_clock::now();

            if (!is_sorted(a.begin(), a.end())) {
                cerr << "ERROR: sort produced unsorted result\n";
            }

            double ms = chrono::duration<double, milli>(t1 - t0).count();
            totalTime += ms;
            totalCmp += cmp;
        }

        return { totalTime / repeats, totalCmp / repeats };
    }

    void runAndReport(const string& algName, const string& arrType,
                      int n, SortFn sortFn, const vector<string>& data,
                      ostream& out) {
        SortResult res = run(sortFn, data);
        out << algName << ',' << arrType << ',' << n
            << ',' << fixed << setprecision(4) << res.avgTimeMs
            << ',' << res.charCmpCount << '\n';
        out.flush();
    }

private:
    int repeats;
};

#endif
