// @title get pfactors
// @description get prime factors of x
// @prefix get_pfactors getfactors factors pfactors
auto get_pfactors(ll x) {
    vector<pair<ll, int>> res;
    for (auto p : primes) {
        if (p * p > x) break;
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) x /= p, cnt++;
            res.pb(mk(p, cnt));
        }
    }
    if (x != 1) res.pb(mk(x, 1));
    return res;
}
