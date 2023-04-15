// @title gcd
// @description great common division
// @prefix gcd
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}