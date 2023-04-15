// @title segtree for max or min values
// @description dynamic-nodes segtree for max or min values
// @prefix segpeek
template <class T, decltype(auto) MinOrMax, ll def>
struct SegTree {
    SegTree(ll l, ll r, size_t siz)
        : val(siz, def), lson(siz), rson(siz), lm(l), rm(r) {}
    vector<T> val;
    vector<int> lson, rson;
    const ll lm, rm;
    int head = 0, cnt = 1;
    auto getNode(int &k) {
        if (!k) k = cnt++;
        return forward_as_tuple(lson[k], rson[k]);
    }
    void insert(T p, ll x) {
        assert(p >= lm && p <= rm && cnt < val.size());
        auto ins = [&](auto ins, int &k, ll l, ll r) {
            auto [ls, rs] = getNode(k);
            if (l == r) {
                val[k] = x;
                return;
            }
            ll mid = l + r >> 1;
            if (p <= mid)
                ins(ins, ls, l, mid);
            else
                ins(ins, rs, mid + 1, r);
            val[k] = MinOrMax(val[ls], val[rs]);
        };
        ins(ins, head, lm, rm);
    }
    const T getans(ll a, ll b) {
        auto res = [&](auto res, int k, ll l, ll r) {
            auto [ls, rs] = getNode(k);
            if (a <= l && r <= b) return val[k];
            ll mid = l + r >> 1;
            T lans = def, rans = def;
            if (a <= mid && ls) lans = res(res, ls, l, mid);
            if (b > mid && rs) rans = res(res, rs, mid + 1, r);
            return MinOrMax(lans, rans);
        };
        return res(res, head, lm, rm);
    }
};
//ll maxx(ll a, ll b) { return max(a, b); };
//SegTree<ll, &maxx, INT_MIN> seg1(1, 1e18, log(n)*n);