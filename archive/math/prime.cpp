// @title prime table
// @description prime[i]: i-th prime number, pvis[i]: 1 if not-prime, 0 prime
// @prefix getprime
const int table_size = 5000000;
int prime[table_size + 3], pvis[table_size + 3], tot = 0;
void prime_table() {
    for (int i = 2; i <= table_size; i++) {
        if (!pvis[i]) prime[++tot] = i;
        for (int j = 1; j <= tot; j++) {
            if (prime[j] * i > table_size) break;
            pvis[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}