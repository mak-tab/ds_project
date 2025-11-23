#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Utils {
public:
    static string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    static int levenshteinDistance(const string& s1, const string& s2) {
        string a = toLower(s1);
        string b = toLower(s2);
        
        int n = a.length();
        int m = b.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        for (int i = 0; i <= n; i++) { dp[i][0] = i; }
        for (int j = 0; j <= m; j++) { dp[0][j] = j; }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
                dp[i][j] = min({ 
                    dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + cost
                });
            }
        }
        return dp[n][m];
    }
};

#endif
