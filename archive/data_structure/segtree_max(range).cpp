// @title maximum segtree
// @description maximum segtree range modification supported(need to test)
// @prefix segtree_max_range segtree_min_range
template <class T, decltype(auto) Max,
          c template <class T, decltype(auto) Max> struct SegTree {
   public:
    SegTree(int l, int r, const T &&def)
        : _def(def),
          _l(l),
          _r(r),
          _max((r - l) * 4 + 3, _def),
          _lazy((r - l) * 4 + 3, _def) {}
    void insert(int l, int r, const T &x) { _insert(1, l, r, x, _l, _r); }
    const T getmax(int a, int b) { return _getmax(1, a, b, _l, _r); }

   private:
    const T _def;
    const int _l, _r;
    vector<T> _max;
    vector<T> _lazy;

    void _lazydown(int k) {
        if (_lazy[k] == _def) return;
        _lazy[k * 2] = _lazy[k];
        _lazy[k * 2 + 1] = _lazy[k];
        _max[k * 2] = Max(_max[k * 2], _lazy[k]);
        _max[k * 2 + 1] = Max(_max[k * 2 + 1], _lazy[k]);
        _lazy[k] = _def;
    }
    void _insert(int k, int a, int b, const T &x, int l, int r) {
        _lazydown(k);
        if (a <= l && r <= b) {
            if (x > _max[k]) _lazy[k] = _max[k] = x;  // modify _max softly
            // _lazy[k] = _max[k] = x;   //modify _max forcely
            return;
        }
        int mid = (l + r) >> 1;
        if (a <= mid) _insert(k * 2, a, b, x, l, mid);
        if (b > mid) _insert(k * 2 + 1, a, b, x, mid + 1, r);
        _max[k] = Max(_max[k * 2], _max[k * 2 + 1]);
    };
    const T _getmax(int k, int a, int b, int l, int r) {
        _lazydown(k);
        if (a <= l && r <= b) return _max[k];
        int mid = (l + r) >> 1;
        T lans = _def, rans = _def;
        if (a <= mid) lans = _getmax(k * 2, a, b, l, mid);
        if (b > mid) rans = _getmax(k * 2 + 1, a, b, mid + 1, r);
        return Max(lans, rans);
    };
};

auto Max = [](auto a, auto b) { return (a < b) ? a : b; };
SegTree<int, Max> seg(1, 200003, INT_MAX);