// @title Manacher
// @description typical find palindrome with O(n) time complexity
// @prefix manacher
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
vector<int> manacher(string s) {
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    for_each(res.begin(), res.end(), [](auto &c) { c--; });
    return res;
}
/*  e.g. auto res = manacher("abbcb")
    i       0 1 2 3 4 5 6 7 8 9 10
    string    a   b   b   c   b
    res[i]  0 1 0 1 2 1 0 3 0 1 0
    res[i]: longeset lenth of the palindrome of i-centered substring.
    Should take the "gap" into account and reindex the string.
    (the way was shown in the example above, both between and two sides)
    But the res only count the real characters (the gaps does not count )
*/