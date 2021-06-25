//
// Created by Lukas Huwald on 30.05.18.
//

#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include "Prelude.h"

class SuffixArray {
private:

    // for suffix array
    vc text; // original text with '$' at end (i use tab here)
    int length; // length (including '$')
    int lengthOfFirst; // length of first string if there are two
    vi rank, tempRank;
    vi sa, tempSa;
    vi c;

    // for lcp between consecutive suffixes
    vi lcp;
    vi plcp;
    vi phi;

    void countingSort(int k) {
        int maxi = std::max(300, length);
        REP(i, maxi) {
            c[i] = 0;
        }
        // compute counts
        REP(i, length) {
            c[i + k < length ? rank[i+k] : 0]++;
        }
        // accumulate counts
        for (int i = 0, sum = 0; i < maxi; ++i) {
            int t = c[i]; c[i] = sum; sum += t;
        }
        // permute
        REP(i, length) {
            tempSa[c[sa[i]+k < length ? rank[sa[i]+k] : 0]++] = sa[i];
        }
        // copy
        REP(i, length) {
            sa[i] = tempSa[i];
        }
    }

    void constructSuffixArray() {
        REP(i, length) {
            rank[i] = text[i];
            sa[i] = i;
        }
        // countingsort log times
        for (int k = 1; k < length; k <<= 1) {
            countingSort(k);
            countingSort(0);

            tempRank[sa[0]] = 0;
            int currentRank = 0;
            // update rankes
            for (int i = 1; i < length; ++i) {
                tempRank[sa[i]] =
                        (rank[sa[i]] == rank[sa[i-1]] && rank[sa[i]+k] == rank[sa[i-1]+k] ?
                         currentRank : ++currentRank);
            }
            REP(i, length) {
                rank[i] = tempRank[i];
            }
            if (rank[sa[length-1]] == length-1) { break; }
        }
    }

    void computeLCP() {
        // store index of previous suffix
        phi[sa[0]] = -1;
        for (int i = 1; i < length; ++i) {
            phi[sa[i]] = sa[i-1];
        }
        // compute plcp
        for (int i = 0, L = 0; i < length; ++i) {
            if (phi[i] == -1) {plcp[i] = 0; continue; }
            while (i + L < length && phi[i] + L < length && text[i + L] == text[phi[i] + L]) { L++; }
            plcp[i] = L;
            L = std::max(L-1, 0);
        }
        // compute lcp
        REP(i, length) {
            lcp[i] = plcp[sa[i]];
        }
    }

    std::string textSubString(int index, int len) {
        std::string res(len, '0');
        REP(i, len) {
            res[i] = text[index+i];
        }
        return res;
    }

public:
    // compute suffix array in O(n log n)
    SuffixArray(std::string textString) {
        int n = textString.size();
        text = vc(n+1);
        REP(i, n) {
            text[i] = textString[i];
        }
        text[n++] = 13;
        length = lengthOfFirst = n;
        sa = vi(length), tempSa = vi(length), rank = vi(length), tempRank = vi(length);
        c = vi(std::max(300, length));
        constructSuffixArray();
        lcp = vi(length), plcp = vi(length), phi = vi(length);
        computeLCP();
    }

    // compute suffix array from two strings for longest common substring
    SuffixArray(std::string s1, std::string s2) {
        int n = s1.size();
        int m = s2.size();
        text = vc(n+m+1);
        REP(i, n) {
            text[i] = s1[i];
        }
        text[n++] = 11;
        REP(i, m) {
            text[n+i] = s2[i];
        }
        text[n+m] = 13;
        m++;
        length = n + m;
        lengthOfFirst = n;
        sa = vi(length), tempSa = vi(length), rank = vi(length), tempRank = vi(length);
        c = vi(std::max(300, length));
        constructSuffixArray();
        lcp = vi(length), plcp = vi(length), phi = vi(length);
        computeLCP();
    }

    vi getSuffixArray() {
        vi suffixArray(length);
        REP(i,length) {
            suffixArray[i] = sa[i];
        }
        return suffixArray;
    }

    vi getLCPArray() {
        vi lcpArray(length);
        REP(i,length) {
            lcpArray[i] = lcp[i];
        }
        return lcpArray;
    }

    std::pair<std::string, int> getLongestRepeatedSubstring() {
        int maxLength = -1, index = -1, count = 0;
        REP(i, length) {
            if (lcp[i] > maxLength) {
                maxLength = lcp[i];
                index = sa[i];
                count = 2;
                while (i < length-1 && lcp[i+1] == lcp[i]) {
                    count++;
                    i++;
                }
            }
        }
        if (maxLength == -1) {
            return std::make_pair(std::string(""), -1);
        }
        std::string res = textSubString(index, maxLength);

        return std::make_pair(res, count);
    }

    // get longest common substring if initialized with two strings
    std::string getLongestCommonSubstring() {
        int maxLength = -1, index = -1;
        for (int i = 1; i < length; ++i) {
            if ((sa[i] < lengthOfFirst) != (sa[i-1] < lengthOfFirst)) {
                if (lcp[i] > maxLength) {
                    maxLength = lcp[i];
                    index = sa[i];
                }
            }
        }
        std::cout << "\n";
        if (maxLength == -1) {
            return std::string("");
        }
        return textSubString(index, maxLength);
    }

    std::vector<std::string> getLongestCommonSubstrings() {
        std::vector<std::string> res;
        int maxLength = -1;
        for (int i = 1; i < length; ++i) {
            if ((sa[i] < lengthOfFirst) != (sa[i-1] < lengthOfFirst)) {
                if (lcp[i] > maxLength) {
                    res = std::vector<std::string>();
                    maxLength = lcp[i];
                    res.push_back(textSubString(sa[i], maxLength));
                }
                else if (lcp[i] == maxLength) {
                    res.push_back(textSubString(sa[i], maxLength));
                }
            }
        }
        if (maxLength == -1) {
            res.push_back(std::string(""));
        }
        return res;
    }

};

#endif //SUFFIXARRAY_H
