// @title prime table
// @description prime[i]: i-th prime number, pvis[i]: 1 if not-prime, 0 prime
// @prefix getprime prime_table
void prime_table(int table_size) {
    pvis = vector<int>(table_size);
    for (int i = 2; i < table_size; i++) {
        if (!pvis[i]) primes.pb(i);
        for (auto p : primes) {
            if (p * i >= table_size) break;
            pvis[p * i] = 1;
            if (i % p == 0) break;
        }
    }
}