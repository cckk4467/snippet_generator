// @title quick read
// @description very quick!
// @prefix qread
inline char rc() {
static char buf[1000000], *pn = buf, *pe = buf;
    return (pn == pe) &&
                   (pe = (pn = buf) + fread(buf, 1, 1000000, stdin), pn == pe)
               ? EOF
               : *pn++;
}
inline int read() {
    int f = 0;
    char cc = rc();
    while (cc < '0' || cc > '9') cc = rc();
    while (cc >= '0' && cc <= '9') f = f * 10 + cc - '0', cc = rc();
    return f;
}