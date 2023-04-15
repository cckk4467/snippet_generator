// @title quick pow
// @description need to define Mod
// @prefix ksm
ll ksm(ll a,ll b) {ll res=1;a%=Mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%Mod;a=a*a%Mod;}return res;}