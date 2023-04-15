// @title debug snippet
// @description emmmm
// @prefix dbg
void dbg_out() { cerr << endl; };
template <typename H, typename... T>
void dbg_out(H h, T... t) {
    cerr << " " << h;
    dbg_out(t...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)