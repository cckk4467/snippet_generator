// @title nagative operation with mod
// @description a - b = a + neg(b) in mod, x must >=0
// @prefix neg
ll neg(ll x) {assert(x >= 0);return Mod - x % Mod;}