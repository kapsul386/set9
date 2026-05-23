#ifndef SET9_STRING_GENERATOR_H
#define SET9_STRING_GENERATOR_H

#include "bits/stdc++.h"
using namespace std;

class StringGenerator {
public:
    static const string ALPHABET;
    static const int MIN_LEN = 10;
    static const int MAX_LEN = 200;

    StringGenerator(uint32_t seed = 42)
        : rng(seed),
          lenDist(MIN_LEN, MAX_LEN),
          charDist(0, (int)ALPHABET.size() - 1) {}

    string randomString() {
        return randomString(lenDist(rng));
    }

    string randomString(int len) {
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            s.push_back(ALPHABET[charDist(rng)]);
        }
        return s;
    }

    vector<string> randomArray(int n) {
        vector<string> a;
        a.reserve(n);
        for (int i = 0; i < n; i++) {
            a.push_back(randomString());
        }
        return a;
    }

    vector<string> reverseSortedArray(int n) {
        vector<string> a = randomArray(n);
        sort(a.begin(), a.end(), greater<string>());
        return a;
    }

    vector<string> almostSortedArray(int n, int swaps = -1) {
        vector<string> a = randomArray(n);
        sort(a.begin(), a.end());

        if (swaps < 0) swaps = max(1, n / 50);

        uniform_int_distribution<int> idx(0, n - 1);
        for (int t = 0; t < swaps; t++) {
            int i = idx(rng);
            int j = idx(rng);
            swap(a[i], a[j]);
        }
        return a;
    }

    vector<string> commonPrefixArray(int n, const string& prefix) {
        vector<string> a;
        a.reserve(n);
        for (int i = 0; i < n; i++) {
            int len = lenDist(rng);
            string s = prefix;
            int tail = max(0, len - (int)prefix.size());
            for (int j = 0; j < tail; j++) {
                s.push_back(ALPHABET[charDist(rng)]);
            }
            a.push_back(s);
        }
        return a;
    }

private:
    mt19937 rng;
    uniform_int_distribution<int> lenDist;
    uniform_int_distribution<int> charDist;
};

const string StringGenerator::ALPHABET =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#%:;^&*()-.";

#endif
