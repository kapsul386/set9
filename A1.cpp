/*
#include "bits/stdc++.h"
#include "StringGenerator.h"
#include "StringSortTester.h"
#include "SortAlgorithms.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N_MIN  = 100;
    const int N_MAX  = 3000;
    const int N_STEP = 100;
    const int REPEATS = 5;

    StringGenerator gen(42);
    StringSortTester tester(REPEATS);

    cout << "Подготовка эталонных массивов длины " << N_MAX << "...\n";
    vector<string> bigRandom   = gen.randomArray(N_MAX);
    vector<string> bigReversed = gen.reverseSortedArray(N_MAX);
    vector<string> bigAlmost   = gen.almostSortedArray(N_MAX);

    ofstream out("results.csv");
    out << "algorithm,array_type,n,time_ms,char_cmp\n";

    vector<pair<string, StringSortTester::SortFn>> algs = {
        {"std_quick",    sorts::standardQuickSort},
        {"std_merge",    sorts::standardMergeSort},
        {"str_quick",    sorts::stringQuickSort},
        {"str_merge",    sorts::stringMergeSort},
        {"msd_radix",    sorts::msdRadixSort},
        {"msd_radixQ",   sorts::msdRadixQuickSort},
    };

    vector<pair<string, const vector<string>*>> arrays = {
        {"random",   &bigRandom},
        {"reversed", &bigReversed},
        {"almost",   &bigAlmost},
    };

    for (int n = N_MIN; n <= N_MAX; n += N_STEP) {
        cout << "n = " << n << "...\n";
        for (auto& [arrName, srcPtr] : arrays) {
            vector<string> sub(srcPtr->begin(), srcPtr->begin() + n);
            for (auto& [algName, fn] : algs) {
                tester.runAndReport(algName, arrName, n, fn, sub, out);
            }
        }
    }

    out.close();
    cout << "Готово. Результаты записаны в results.csv\n";
    return 0;
}
*/
